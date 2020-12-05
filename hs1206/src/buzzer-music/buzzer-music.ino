//A-ha!
//by GeneralSpud

// For this to work, we need the pitches library
#include "EasyBuzzer.h"
const int pin=13;
unsigned int frequency = 1000;  
unsigned int onDuration = 50;
unsigned int offDuration = 100;
unsigned int beeps = 2;
unsigned int pauseDuration = 500;
unsigned int cycles = 10;

#include "pitches.h"

// Two things need to be created: the array for the notes of the melody (in order)
// and the duration of each (think of it like sheet music in two parts)

// BOTH ARRAYS MUST BE THE SAME SIZE!

// The melody array 
int melody[] = {
  NOTE_FS5, NOTE_FS5, NOTE_D5, NOTE_B4, NOTE_B4, NOTE_E5, 
  NOTE_E5, NOTE_E5, NOTE_GS5, NOTE_GS5, NOTE_A5, NOTE_B5, 
  NOTE_A5, NOTE_A5, NOTE_A5, NOTE_E5, NOTE_D5, NOTE_FS5, 
  NOTE_FS5, NOTE_FS5, NOTE_E5, NOTE_E5, NOTE_FS5, NOTE_E5
};

// The note duration, 8 = 8th note, 4 = quarter note, etc.
int durations[] = {
  8, 8, 8, 4, 4, 4, 
  4, 5, 8, 8, 8, 8, 
  8, 8, 8, 4, 4, 4, 
  4, 5, 8, 8, 8, 8
};

void done() {
  Serial.print("Done!");
}

// determine the length of the arrays to use in the loop iteration
int songLength = sizeof(melody)/sizeof(melody[0]);
void setup() {
  Serial.begin(115200);
  EasyBuzzer.setPin(pin);
 /* Start a beeping sequence. */
  
}

void loop() {
  // Iterate through both arrays
  // Notice how the iteration variable thisNote is created in the parenthesis
  // The for loop stops when it is equal to the size of the melody array
  for (int thisNote = 0; thisNote < songLength; thisNote++){
    frequency=melody[thisNote];
    int duration = 1000/durations[thisNote];
    onDuration=duration;
    beeps=1;
    int pauseDuration = duration * 1.3;
    EasyBuzzer.beep(
    frequency,    // Frequency in hertz(HZ). 
    onDuration,   // On Duration in milliseconds(ms).
    offDuration,  // Off Duration in milliseconds(ms).
    beeps,      // The number of beeps per cycle.
    pauseDuration,  // Pause duration.
    cycles,     // The number of cycle.
    done      // [Optional] Callback. A function to call when the sequence ends.
  );
  EasyBuzzer.update();
  }
}
