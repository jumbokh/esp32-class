# %%
import json
import numpy as np
from tensorflow.keras.preprocessing.sequence import pad_sequences
from tensorflow.keras.utils import to_categorical
import os

__version__ = '1.0.2'
# %%
class Data_reader():
    def __init__(self, path_name, mode='categorical', label_name = None):
        self.path_name = path_name
        self.mode = mode
        if label_name:
            self.label_name = label_name
        elif mode=='binary' or mode=='categorical':   
            self.label_name = [f[:(f.rfind('.'))] for f in os.listdir(path_name) if not f.startswith('.')]
            if len(self.label_name)>2 and mode=='binary':
                raise ValueError('Found more than two files, please assign parameter, label_name.')
            

    def read(self, maxlen=None, shuffle=True, random_seed=None, encoding='utf-8'):      
        train_data = []
        label_data = []

        if self.mode=='regression':
            f = open(self.path_name,encoding=encoding,errors='ignore')
            for d in f:
                try:
                    data = d.split(' ')
                    train_value = list(map(float,data[0].split(',')))
                    label_value = list(map(float,data[1].split(',')))
                    train_data.append(train_value)
                    label_data.append(label_value)
                except Exception as e:
                    print(e)
                    pass
            f.close()

            label_data = np.array(label_data)

        else:
            file_list = [f for f in os.listdir(self.path_name) if not f.startswith('.')]

            for name in file_list:
                f = open(self.path_name+os.sep+name,encoding=encoding,errors='ignore')
                label = self.label_name.index(name[:(name.rfind('.'))])
                for d in f:
                    try:
                        data = list(map(float,d.split(',')))
                        train_data.append(data)
                        label_data.append(label)
                    except Exception as e:
                        print(e)
                f.close()

            if self.mode=='categorical':
                label_data = to_categorical(label_data)
            elif self.mode=='binary':
                label_data = np.array(label_data)
            else:
                raise ValueError('invalid input of mode')

        if maxlen==None:
            train_data = np.array(train_data)  
        else:  
            train_data = pad_sequences(train_data, maxlen=maxlen, truncating='post').astype('float')

        if shuffle:
            np.random.seed(random_seed)
            shuffle_index = np.arange(len(train_data))
            np.random.shuffle(shuffle_index)
            train_data = train_data[shuffle_index]
            label_data = label_data[shuffle_index]

        return train_data, label_data

sup_activation = ['linear','relu','sigmoid','softmax']

def save(model, path):
    arch = json.loads(model.to_json())
    model_dict = {}
    hasInputLayer = False
    if arch['class_name'] == 'Sequential':
        layers = []
        o_layers = arch['config']['layers']
        for i,o_layer in enumerate(o_layers):
            layer = {}
            if i==0:
                layer['batch_input_shape'] = o_layer['config']['batch_input_shape']
            if o_layer['class_name']=='InputLayer':
                hasInputLayer = True
                layer['class_name'] = 'InputLayer'
            elif o_layer['class_name']=='Dense':
                layer['class_name'] = 'Dense'
                layer['units'] = o_layer['config']['units']
                acti_func = o_layer['config']['activation']
                if acti_func in sup_activation:
                    layer['activation'] = acti_func
                else:
                    raise ValueError('invalid class of activation:'+acti_func)

                weights = [0,0]
                layer_weights = model.layers[i-hasInputLayer].get_weights()
                weights[0] = layer_weights[0].tolist()
                if len(layer_weights)>1:
                    weights[1] = layer_weights[1].tolist()

                layer['weights'] = weights
            elif o_layer['class_name']=='Reshape':
                layer['class_name'] = 'Reshape'
                layer['target_shape'] = o_layer['config']['target_shape']
            elif o_layer['class_name']=='Conv1D':
                layer['class_name'] = 'Conv1D'
                layer['strides'] = o_layer['config']['strides'][0]
                layer['kernel_size'] = o_layer['config']['kernel_size'][0]
                layer['padding'] = o_layer['config']['padding']
                acti_func = o_layer['config']['activation']
                if acti_func in sup_activation[:3]:
                    layer['activation'] = acti_func
                else:
                    raise ValueError('invalid class of activation:'+acti_func)
                weights = [0,0]
                layer_weights = model.layers[i-hasInputLayer].get_weights()
                weights[0] = layer_weights[0].reshape((-1,layer_weights[0].shape[-1])).tolist()
                if len(layer_weights)>1:
                    weights[1] = layer_weights[1].tolist()

                layer['weights'] = weights
            elif o_layer['class_name']=='MaxPooling1D':
                layer['class_name'] = 'MaxPooling1D'
                layer['pool_size'] = o_layer['config']['pool_size'][0]
                layer['strides'] = o_layer['config']['strides'][0]
            elif o_layer['class_name']=='AveragePooling1D':
                layer['class_name'] = 'AveragePooling1D'
                layer['pool_size'] = o_layer['config']['pool_size'][0]
                layer['strides'] = o_layer['config']['strides'][0]
            elif o_layer['class_name']=='GlobalMaxPooling1D':
                layer['class_name'] = 'GlobalMaxPooling1D'
            elif o_layer['class_name']=='GlobalAveragePooling1D':
                layer['class_name'] = 'GlobalAveragePooling1D'
            elif o_layer['class_name']=='Flatten':
                layer['class_name'] = 'Flatten'
            else:
                raise ValueError('invalid class of layer:'+o_layer['class_name'])
            layers.append(layer)

        model_dict['layers'] = layers

        f = open(path,'w')
        f.write(json.dumps(model_dict))
        f.close()
    else:
        raise ValueError('Unable to save non-sequential model:'+arch['class_name'])