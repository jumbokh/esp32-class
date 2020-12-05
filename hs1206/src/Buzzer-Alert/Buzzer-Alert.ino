// https://github.com/lbernstone/Tone32
#include <Tone32.h>

#define BUZZER_PIN 13
#define BUZZER_CHANNEL 0

void setup() {}

void loop() {
   
    int duration = 1000/ 4;
    tone(BUZZER_PIN, 500, duration, BUZZER_CHANNEL);
    
    delay(duration);
    // stop the tone
    noTone(BUZZER_PIN, BUZZER_CHANNEL);
    tone(BUZZER_PIN, 1000, duration, BUZZER_CHANNEL);
    // pause between notes
    
    delay(duration);
    // stop the tone
    noTone(BUZZER_PIN, BUZZER_CHANNEL);
 
}
