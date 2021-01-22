## 機器學習
* [Machine Learning](https://github.com/jumbokh/class1091/tree/master/ML)
## 訓練神經網路的流程
#### 以預測台灣房租為例
##
### 實驗目的: 利用神經網路的回歸模型來預測 "台北市中山區" 房租。
#### 房屋參數: "591" 房仲網所得到的資訊,包含:
* 坪數
* 樓層
* 是否可以開伙
* 是否可以養寵物
* 價格
##
### [程式: House_price_predict.ipynb](https://github.com/jumbokh/esp32-class/blob/master/Lab-Regression/House_price_predict.ipynb)
#### Step 1: upload 程式, 在 colab 中 選擇 File-> Upload notebook
#### Step 2: 上傳房屋資料、第三方模組
* [house.txt](https://github.com/jumbokh/esp32-class/blob/master/Lab-Regression/house.txt)
* [keras_lite_convertor.py](https://github.com/jumbokh/esp32-class/blob/master/Lab-Regression/keras_lite_convertor.py)
#### 訓練集、驗證集、測試集
<pre>
# 取資料中的 90% 當作訓練集
split_num = int(len(data)*0.9) 
train_data = data[:split_num]        # 訓練用資料
train_label = label[:split_num]      # 訓練用標籤 
</pre>
##
#### 資料正規化
<pre>
# 正規化
mean = train_data.mean()             # 訓練資料的平均數
data -= mean                         # data 減掉平均值
std = train_data.std()               # 訓練資料的標準差
data /= std                          # data 除以平均值
</pre>
##
#### 標籤正規化
<pre>
new_label = label/max(label)         # 將 label範圍落在 0~1 (label正規化)
</pre>
##
#### 資料視覺化: 比較圖、誤差分佈圖
![比較圖](https://github.com/jumbokh/esp32-class/blob/master/Lab-Regression/diff-a.png)
![誤差圖](https://github.com/jumbokh/esp32-class/blob/master/Lab-Regression/error-a.png)
