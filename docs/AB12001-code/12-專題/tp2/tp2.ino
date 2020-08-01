#define IN1 10 					// 馬達控制信號輸入端
#define IN2 11					 // 馬達控制信號輸入端
#define KEY1 2 					// 按鍵 1
#define KEY2 3					// 按鍵 2
#define KEY3 4 					// 按鍵 3
#define KEY4 5 					// 按鍵 4
#define LED1 6 					// LED1
#define LED2 7 					// LED2
char mode=0; 					// 工作模式, 預設為0

void setup() {
	pinMode(IN1, OUTPUT); 		// 初始化馬達控制腳為輸出
	pinMode(IN2, OUTPUT);
	pinMode(KEY1, INPUT); 		// 初始化按鍵腳位為輸入
	pinMode(KEY2, INPUT);
	pinMode(KEY3, INPUT);
	pinMode(KEY4, INPUT);
	pinMode(LED1,OUTPUT);
	pinMode(LED2, OUTPUT);
    digitalWrite(LED1,HIGH);
    digitalWrite(LED2,HIGH);
}
void loop() {
	if (digitalRead(KEY1)==0 && mode!=1 && mode!=3) {    	
		mode=1; 								// 設定模式為1
		digitalWrite(IN1,HIGH); 					// 風扇正轉( 送風)
		digitalWrite(IN2,LOW);
		digitalWrite(LED1,LOW); 				//LED1 亮
	}
	else if (digitalRead(KEY2)==0 && mode!=2) {  //按鍵按下且模式不是2
		mode=2; 							// 設定模式為2
		digitalWrite(IN1,LOW); 				// 風扇停止
		digitalWrite(IN2,LOW);
		digitalWrite(LED1,HIGH);				//LED1 暗
		digitalWrite(LED2,HIGH); 				//LED2 暗
	}
	else if (digitalRead(KEY3)==0 && mode!=3 && mode!=1) {  
		mode=3;							// 設定模式為3
		digitalWrite(IN1,LOW);				// 風扇反轉( 吸風)
		digitalWrite(IN2,HIGH);
		digitalWrite(LED2,LOW); 			//LED2 亮
	}
	else if (digitalRead(KEY4)==0 && mode!=4) {  //按鍵按下且模式不是4
		mode=4;							// 設定模式為4
		digitalWrite(IN1,HIGH);				// 風扇急停(緊急按鈕)
		digitalWrite(IN2,HIGH);
		digitalWrite(LED1,HIGH);				//LED1 暗
		digitalWrite(LED2,HIGH); 				//LED2 暗
	}
} 

