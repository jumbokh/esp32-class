### 聲音實驗 
#### 材料清單
<pre>
1. ESP32s * 1
2. 麵包板
3. 聲音感測模組 * 1
4. 按鈕 * 2
5. LED * 1
6. 220歐姆電阻 * 1
7. 小型喇叭
8. 杜邦線
9. 2N2222 NPN 電晶體
</pre>
#### Lab 1. 聲音感測器訊號
![佈線](https://github.com/jumbokh/esp32-class/blob/master/lab-voice/lab-voice_bb.jpg)
* 執行 thonny
* 點選thonny檢視選單中的繪圖選項
![graph](https://github.com/jumbokh/esp32-class/blob/master/lab-voice/thonny-menu.png)
* 測試收音： [程式碼](https://github.com/jumbokh/esp32-class/blob/master/lab-voice/testMIC.py)
##
* ![測試結果](https://github.com/jumbokh/esp32-class/blob/master/lab-voice/mictest.png)
##
#### Lab 2. 以喇叭發出聲音
* 將小喇叭接到 14腳
* 將按鈕接到 12腳
* 執行程式 [src](https://github.com/jumbokh/esp32-class/blob/master/lab-voice/recordplay.py)
* 按下按鈕代表開始紀錄聲音, 直到放開按鈕或是資料大於1200筆
##
* ![測試視窗](https://github.com/jumbokh/esp32-class/blob/master/lab-voice/recordtrest.png)
##
#### Lab 3. 以電晶體當開關
* NPN 電晶體： [NPN digikey](https://www.digikey.tw/zh/articles/transistor-basics)
* ![NPN](https://github.com/jumbokh/esp32-class/blob/master/lab-voice/transistor.jpeg)
* ![2N2222](https://github.com/jumbokh/esp32-class/blob/master/lab-voice/2n2222.gif)
* ![佈線](https://github.com/jumbokh/esp32-class/blob/master/lab-voice/lab-vocalctl_bb.jpg)
* 開關測試： [程式](https://github.com/jumbokh/esp32-class/blob/master/lab-voice/led.py)
##
* ![npn](https://github.com/jumbokh/esp32-class/blob/master/lab-voice/Lab-npn.jpg)
#### Lab 4. 實作 智慧聲控燈
* 蒐集資料: 蒐集三種口令： "打開" "關閉" "其他" 各 100 筆 提供訓練模型使用
*          檔案： on.txt off.txt others.txt
* [程式](https://github.com/jumbokh/esp32-class/blob/master/lab-voice/getvoice.py)
##
#### Lab 5. 使用 colab 訓練模型
* 開啟程式 [voice_model.ipynb](https://github.com/jumbokh/esp32-class/blob/master/lab-voice/voice_model.ipynb)
* 連接主機
* 建立 voice_data 目錄
* 上傳蒐集的資料 on.txt off.txt others.txt 至 voice_data之下,  及轉換資料 keras_lite_convertor.py 至根目錄 / 
* 以卷積神經網路訓練, loss function: 使用多元分類的 categorical_crossentropy
* 紀錄 mean 及 std, 下載 voice_model.json
##
#### Lab 6. 智慧聲控燈
* [程式](https://github.com/jumbokh/esp32-class/blob/master/lab-voice/LAB22.py)
* 記得修改 mean 及 std, 還有上傳 voice_model.json 至 micropython 系統
* 
