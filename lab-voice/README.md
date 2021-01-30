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
</pre>
#### Lab 1. 聲音感測器訊號
![佈線](https://github.com/jumbokh/esp32-class/blob/master/lab-voice/lab-voice_bb.jpg)
* 執行 thonny
* 點選thonny檢視選單中的繪圖選項
![graph](https://github.com/jumbokh/esp32-class/blob/master/lab-voice/thonny-menu.png)
* 測試收音： [程式碼](https://github.com/jumbokh/esp32-class/blob/master/lab-voice/testMIC.py)
##
#### Lab 2. 以喇叭發出聲音
* 將小喇叭接到 14腳
* 將按鈕接到 12腳
* 執行程式 [src](https://github.com/jumbokh/esp32-class/blob/master/lab-voice/recordplay.py)
* 按下按鈕代表開始紀錄聲音, 直到放開按鈕或是資料大於1200筆