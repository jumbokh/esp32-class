#include "pitches.h"		       //將pitches.h檔include進來
int melody[]={
NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4};
int Durations[]={2,2,2,2,2,2,4,2,2,2,2,2,2,4};			//設定音長陣列
int sp = 8;
void setup(){      
	for(int thisNote=0 ; thisNote < 14 ; thisNote++){   
		int Duration=150*Durations[thisNote];    
		tone(sp,melody[thisNote],Duration);			
		delay(Duration*1.30); 	         //增加0，3倍的延遲時間
		noTone(sp);
	}
}
void loop(){
}

