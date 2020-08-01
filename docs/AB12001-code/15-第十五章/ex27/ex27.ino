int ledpin1=3; 				// LED1接在D3腳
int ledpin2=4; 				// LED1接在D4腳
int BluetoothData; 			// 藍芽接收資料暫存器
void setup() {					  
  Serial.begin(38400);
  pinMode(ledpin1,OUTPUT);
  pinMode(ledpin2,OUTPUT);
  digitalWrite(ledpin1,HIGH);            //設定LED1 OFF
  digitalWrite(ledpin2,HIGH);            //設定LED2 OFF
}
void loop() {					  
   if (Serial.available()){               //如果有串列資料進來
    BluetoothData=Serial.read();          //讀取串列資料
    if(BluetoothData=='1'){  		 //如果讀到的資料是"1"
      digitalWrite(ledpin1,LOW);         //LED1 亮
      Serial.println("LED1 IS ON ! ");
    }
    if (BluetoothData=='2'){  		 //如果讀到的資料是"2"             
      digitalWrite(ledpin1,HIGH);        //LED1 暗
      Serial.println("LED1 IS Off ! ");
    }
    if(BluetoothData=='3'){  		//如果讀到的資料是"3" 
      digitalWrite(ledpin2,LOW);        //LED2 亮
      Serial.println("LED2 IS ON ! ");
    }
    if (BluetoothData=='4'){  		//如果讀到的資料是"4" 
      digitalWrite(ledpin2,HIGH);       //LED2 暗
      Serial.println("LED2 IS Off ! ");
    }    
 }
 delay(100);
}


