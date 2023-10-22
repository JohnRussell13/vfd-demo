#include <math.h>

#define BUFF_SIZE 50
#define BUFF_MASK BUFF_SIZE - 1
#define S_TO_MS 1000
#define S_TO_US 1000000

// python generated buffer -- PROGMEM
const uint8_t BUFFER [] = { 10, 11, 12, 14, 15, 16, 17, 18, 18, 19, 20, 20, 20, 20, 20, 20, 19, 18, 18, 17, 16, 15, 14, 12, 11, 10, 9, 8, 6, 5, 4, 3, 2, 2, 1, 0, 0, 0, 0, 0, 0, 1, 2, 2, 3, 4, 5, 6, 8, 9 };


uint8_t i = 0;
uint8_t freq = 1;
uint8_t PWM_PER = (int) ( (float) S_TO_MS / BUFF_SIZE );

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(BUFFER[i]); // delayMicroseconds()
  digitalWrite(LED_BUILTIN, LOW);
  delay(PWM_PER - BUFFER[i]);

  i = (i+1) % BUFF_SIZE;
}
