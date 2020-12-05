// https://github.com/lbernstone/Tone32
#include <Tone32.h>

#define BUZZER_PIN 13
#define BUZZER_CHANNEL 0
// The melody array 
int melody[] = {
  NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4, 
  NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4};

// The note duration, 8 = 8th note, 4 = quarter note, etc.
int durations[] = {
  2, 2, 2, 2, 2, 2, 4,2, 2, 2, 2, 2, 2, 4 
};
int songLength = sizeof(melody)/sizeof(melody[0]);
void setup() {}

void loop() {
   for (int thisNote = 0; thisNote < songLength; thisNote++){
    // determine the duration of the notes that the computer understands
    // divide 1000 by the value, so the first note lasts for 1000/8 milliseconds
    int duration = 1000/ durations[thisNote];
    tone(BUZZER_PIN, melody[thisNote], duration, BUZZER_CHANNEL);
    // pause between notes
    int pause = duration * 1.3;
    delay(pause);
    // stop the tone
    noTone(BUZZER_PIN, BUZZER_CHANNEL);
  }
}
