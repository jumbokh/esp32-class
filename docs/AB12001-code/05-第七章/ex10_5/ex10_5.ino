int sp=8;
int i;
int j;
int notes[8]={262,294,329,349,392,440,493,523};
void setup(){
for(i=0;i<8;i++){
tone(sp,notes[i],300);
delay(300);
noTone(sp);
delay(50);}
}
void loop()
{}

