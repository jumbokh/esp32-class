int IN1=11; 				// IN1接在D11腳
int IN2=12; 				// IN2接在D12腳
int BluetoothData; 			// 藍芽接收資料暫存器
void setup() {					  
  Serial.begin(38400);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  digitalWrite(IN1,LOW);            //設定IN1 LOW
  digitalWrite(IN2,LOW);            //設定IN2 LOW
}
void loop() {					  
  if (Serial.available()){                //如果有串列資料進來
    BluetoothData=Serial.read();      //讀取串列資料
    if(BluetoothData=='1'){  		 //如果讀到的資料是"1"
      digitalWrite(IN1,HIGH);         //風扇正轉
      digitalWrite(IN2,LOW);         //風扇正轉
      Serial.println("FAN IS FOR ! ");
    }
    if (BluetoothData=='0'){  		 //如果讀到的資料是"2"
      digitalWrite(IN1,LOW);         //風扇停止
      digitalWrite(IN2,LOW);         //風扇停止
      Serial.println("FAN IS STOP ! ");
    }
    if(BluetoothData=='2'){  		//如果讀到的資料是"3" 
      digitalWrite(IN1,LOW);        //風扇反轉
      digitalWrite(IN2,HIGH);         //風扇反轉
      Serial.println("FAN IS REV ! ");
    }
  }
 delay(100);
}

