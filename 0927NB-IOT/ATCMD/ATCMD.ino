//  BC26 reset pin
#define BC26resetPIN 14       //  IO14(HS2_CLK)
#define BC26powerPIN 15       //  IO15(HS2_CMD)

#define BC26PowerOn  "ON"
#define BC26PowerOff "OFF"
#define BC26Reset    "RESET"


//------- --------- --------- --------- --------- --------- 
//  data for transfer
//  轉傳資料
//------- --------- --------- --------- --------- --------- 
String Xfer = "";

void setup() {
  // put your setup code here, to run once:

  //----- --------- --------- --------- --------- ---------
  //  setup baud rate of serial ports
  //  設定序列埠的鮑率
  //----- --------- --------- --------- --------- ---------
  Serial.begin(115200);       //  baud rate for Arduino Serial Monitor, 設定序列埠監控視窗的鮑率
  Serial2.begin(115200);      //  baud rate for BC26, 設定 BC26 的鮑率

  //----- --------- --------- --------- --------- ---------
  //  show title in Arduino Serial Monitor
  //  在 Arduino 序列埠監控視窗中顯示標題
  //----- --------- --------- --------- --------- ---------
  Serial.println("//------- --------- --------- --------- --------- --------//");
  Serial.println("//  BC26 Terminal Console");
  Serial.println("//------- --------- --------- --------- --------- --------//");

  //----- --------- --------- --------- --------- ---------
  //  setup Input/Output of pins
  //  設定腳位輸出入
  //----- --------- --------- --------- --------- ---------
  pinMode(BC26powerPIN, OUTPUT);        //  set power enable pin of BC26 output, 設定 BC26 電源控制腳位為輸出腳位
  pinMode(BC26resetPIN, OUTPUT);        //  set reset pin of BC26 output, 設定 BC26 重置腳位為輸出腳位

  //----- --------- --------- --------- --------- ---------
  //  power enable BC26
  //  開啟 BC26 的電源
  //----- --------- --------- --------- --------- ---------
  digitalWrite(BC26powerPIN, LOW);      //  PowerEN low, 關閉 BC26 的電源
  delay(100);
  digitalWrite(BC26powerPIN, HIGH);     //  PowerEN high, 開啟 BC26 的電源

  //----- --------- --------- --------- --------- ---------
  //  reset BC26
  //  重置 BC26
  //----- --------- --------- --------- --------- ---------
  digitalWrite(BC26resetPIN, HIGH);
  delay(100);
  digitalWrite(BC26resetPIN, LOW);

}

//======= ========= ========= ========= ========= ========= ========= ========= 
//  loop function, put your main code here, to run repeatedly
//  loop 函數，將設定的程式碼置於此函數當中，僅執行一次
//======= ========= ========= ========= ========= ========= ========= ========= 
void loop() {
  // put your main code here, to run repeatedly:

  //----- --------- --------- --------- --------- ---------
  //  check if there is an available byte from BC26 to read,
  //  檢查是否有來自 BC26 的資料需要讀取
  //----- --------- --------- --------- --------- ---------
  while (Serial2.available())
  {
    char c = Serial2.read();  //  read byte from serial port of BC26, 從 BC26 的序列埠讀取一個位元組
    if (c == '\n') {break;}   //  Exit the loop when charactor '\n' is detected, 收到字元'\n'時結束 while 迴圈
    Xfer += c;                //  add charactor c into string Xfer, 將讀到的字元 c 加進字串 Xfer
  }

  //----- --------- --------- --------- --------- ---------
  //  transfer data read from BC26 to Arduino Serial Monitor
  //  將從 BC26 讀取到的資料轉傳到 Arduino 序列埠監控視窗
  //----- --------- --------- --------- --------- ---------
  if (Xfer.length() > 0)
  {
    Xfer.trim();
    Serial.println(Xfer);
  }
  Xfer = "";
  
  //----- --------- --------- --------- --------- ---------
  //  check if there is an available byte input from Arduino Serial Monitor to read,
  //  檢查是否有來自 Arduino 序列埠監控視窗輸入的資料需要讀取
  //----- --------- --------- --------- --------- ---------
  while (Serial.available())
  {
    char c = Serial.read();   //  read byte from serial port of Arduino Serial Monitor, 從 Arduino 序列埠監控視窗的序列埠讀取一個位元組
    if (c == '\n') {break;}   //  Exit the loop when charactor '\n' is detected, 收到字元'\n'時結束 while 迴圈
    Xfer += c;                //  add charactor c into string Xfer, 將讀到的字元 c 加進字串 Xfer
  }

  //----- --------- --------- --------- --------- ---------
  //  transfer data read from Arduino Serial Monitor to BC26
  //  將從 Arduino 序列埠監控視窗讀取到的輸入資料轉傳到 BC26
  //----- --------- --------- --------- --------- ---------
  if (Xfer.length() > 0)
  {
    Xfer.trim();

    String command = Xfer;
    command.toUpperCase();

    //  check if input command to reset BC26, 檢查是否輸入 BC26 重置命令
    if (command == BC26Reset)
    {
      Serial.println(command);
      //  reset BC26, 重置 BC26
      digitalWrite(BC26resetPIN, HIGH);
      delay(100);
      digitalWrite(BC26resetPIN, LOW);
    }
    //  check if input command to power on BC26, 檢查是否輸入開啟 BC26 電源的命令
    else if (command == BC26PowerOn)
    {
      Serial.println(command);
      //  power on BC26, 開啟 BC26 的電源
      digitalWrite(BC26powerPIN, HIGH);
    }
    //  check if input command to power off BC26, 檢查是否輸入關閉 BC26 電源的命令
    else if (command == BC26PowerOff)
    {
      Serial.println(command);
      //  power off BC26, 關閉 BC26 的電源
      digitalWrite(BC26powerPIN, LOW);
    }
    else
    {
      //  transfer input data from Arduino Serial Monitor to BC26, 將 Arduino 序列埠輸入的資料轉送到 BC26
      Serial2.println(Xfer);
    }
  }
  Xfer = "";
}
