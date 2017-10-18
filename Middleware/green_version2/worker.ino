#include "green.h"

green stepper1(11, 12, 13, 1200);
green stepper2(4, 5, 6, 1100);

char ch;
int accel;
int count;

void setup() {
  Serial.begin(115200);
}

void loop() {
  if (Serial.available()) {
    if (count == 4) {count = stepper1.setting(3);}
    ch = Serial.read();
    if (ch >=  48 && ch <= 57) {
      stepper1.procWork(accel); 
      count = stepper1.asciino(ch, count);
    } else {
      stepper1.idle(accel, 4);
    }
  } else {
    count = stepper1.setting(4); //operation end
    Serial.println (count);
    delay(1000);
  }
}

