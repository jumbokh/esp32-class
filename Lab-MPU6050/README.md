### MPU6050 Web 展示
#### 請參考： [ESP32 Web Server with MPU-6050 Accelerometer and Gyroscope (3D object representation)](https://randomnerdtutorials.com/esp32-mpu-6050-web-server/)
#### 必須先設定 ESP32 spiff 檔案系統工具： [Uploading Files using the Filesystem Uploader](https://randomnerdtutorials.com/install-esp32-filesystem-uploader-arduino-ide/)
![ESP32+MPU6050](https://github.com/jumbokh/esp32-class/blob/master/Lab-walk/images/ESP32s-Walk_bb.jpg)
#### Step 1. 下載 [Arduino IDE 上傳工具](https://github.com/me-no-dev/arduino-esp32fs-plugin/releases/)
#### Step 2. 轉到Arduino IDE目錄，然後打開“工具”文件夾。
#### Step 3. 將下載的.zip文件夾解壓縮到Tools文件夾。您應該具有類似的文件夾結構：
<pre>
<home_dir> / Arduino- <version> / tools / ESP32FS / tool / esp32fs.jar
</pre>
![Arduino dir](https://github.com/jumbokh/esp32-class/blob/master/images/esptool.jpg)
#### Step 4. 最後，重新啟動Arduino IDE。

要檢查插件是否已成功安裝，請打開Arduino IDE。選擇您的ESP32開發板，轉到“工具”，然後檢查是否具有“ ESP32 Sketch Data Upload ”選項。
![Arduino IDE](https://github.com/jumbokh/esp32-class/blob/master/images/toolmenu.png)
##
#### 檔案傳送步驟
#### Step 1. 創建一個Arduino草稿並保存。出於演示目的，您可以保存一個空的草圖。
#### Step 2. 然後，打開草稿文件夾。您可以轉到草稿>顯示草稿文件夾。保存草稿的文件夾應打開。
![Sketch folder](https://github.com/jumbokh/esp32-class/blob/master/images/showfolder.png)
#### Step 3. 在該文件夾內，創建一個名為data的新文件夾。
#### Step 4. 在data 文件夾中，您應將要保存的文件放入ESP32文件系統中。例如，創建一個.txt文件，其中包含一些名為test_example的文本。
![add Text](https://github.com/jumbokh/esp32-class/blob/master/images/addtext.png)
#### Step 5. 然後，要上傳文件，請在Arduino IDE中，轉到Tools  > ESP32 Sketch Data Upload。
![upload](https://github.com/jumbokh/esp32-class/blob/master/images/upload.jpg)
#### 當您看到“ SPIFFS Image Uploaded ”消息時，文件已成功上傳到ESP32文件系統。
##
#### 檔案架構
![data](https://github.com/jumbokh/esp32-class/blob/master/Lab-walk/images/MPU6050-Web-Server-Project-Folder-Structure-SPIFFS.png)
##
#### [程式碼](https://github.com/jumbokh/esp32-class/blob/master/Lab-MPU6050/ESP32_MPU_6050_Web_Server/ESP32_MPU_6050_Web_Server.ino)
#### [data](https://github.com/jumbokh/esp32-class/tree/master/Lab-MPU6050/ESP32_MPU_6050_Web_Server/data)
#### Output
![web display](https://github.com/jumbokh/esp32-class/blob/master/Lab-walk/images/MPU6050-web.png)
##
