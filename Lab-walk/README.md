### 雲端步頻紀錄儀
##
### MPU6050 六軸加速規測試
* 燒錄韌體 [firmware](https://github.com/jumbokh/esp32-class/blob/master/Lab-walk/firmware/esp32-20200512-v1.12-195-gb16990425.bin)
* 佈線
* ![pinout](https://github.com/jumbokh/esp32-class/blob/master/Lab-walk/images/ESP32s-Walk_bb.jpg)
## 完成品
* ![real](https://github.com/jumbokh/esp32-class/blob/master/Lab-walk/images/13310540459294.jpg)
##
* Lab-1 MPU6050 測試 [src](https://github.com/jumbokh/esp32-class/blob/master/Lab-walk/LAB08.py)
* Lab-2 Button test  [src](https://github.com/jumbokh/esp32-class/blob/master/Lab-walk/LAB09.py)
* Lab-3 資料蒐集 [src](https://github.com/jumbokh/esp32-class/blob/master/Lab-walk/LAB10.py)
    * A. walk data -- save data to walk.txt
    * B. others data -- save data to others.txt
* Lab-4 以 Google Colab 訓練方才儲存的資料 [src](https://github.com/jumbokh/esp32-class/blob/master/Lab-walk/uploads/walk_model.ipynb)
    * A. 連結主機並開啟檔案檢視, 新增目錄: walk_data
    * B. 上傳： walk.txt 及 others.txt 至 walk_data 目錄下
    * C. 上傳： [keras_lite_convertor.py](https://github.com/jumbokh/esp32-class/blob/master/Lab-walk/uploads/keras_lite_convertor.py)
    * D. 訓練
    * E. 下載訓練完的權重檔： walk_model.json
    * F. 請複製Colab上的 mean 及 std
    * <pre>
        如：
           mean = 849.1830065359477, 
           std = 16766.660464036682
      </pre>
* Lab-5 上傳 walk_model.json 至 micropython, 並測試 [src](https://github.com/jumbokh/esp32-class/blob/master/Lab-walk/LAB11.py)    
#### 記得修改 mean 及 std
##
### 雲端部份
#### 註冊 [iot.cht.com.tw](https://iot.cht.com.tw/iot/login?others=)
* ![cht iot](https://github.com/jumbokh/esp32-class/blob/master/Lab-walk/images/cht-iot.png)
##
