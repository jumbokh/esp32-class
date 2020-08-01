#include <IRremote.h>          // 引用 IRRemote 函式庫
const int Recv_Pin = 2;       // 紅外線接收器OUTPUT訊號接在pin2
IRrecv irrecv(Recv_Pin);      // 定義 IRrecv 物件來接收紅外線訊號
decode_results results;          // 解碼結果將放在 result 變數裏
void setup()
{
Serial.begin(9600);          // 開啟 Serial port, 通訊速率為 9600 bps
irrecv.enableIRIn();          // 啟動紅外線解碼
}
void loop()
{
if(irrecv.decode(&results)) {         // 解碼成功，收到一組紅外線訊號
//印到Serialport
Serial.print("irCode:");
Serial.print(results.value,HEX);     //紅外線編碼
Serial.print(",bits:");
Serial.println(results.bits);         //紅外線編碼位元數
irrecv.resume();                  //繼續接收下一組紅外線訊號
}
}

