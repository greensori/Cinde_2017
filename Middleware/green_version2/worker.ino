#include "green.h"

green stepper1(11, 12, 13, 1200);
green stepper2(4, 5, 6, 1100);

#define dirmaker 34

char ch;
int accel;
int result_dir;
int count;

void setup() {
  Serial.begin(115200);
}


//43.44.45 = + , -
//35.36 = # $

void loop() {
  if (Serial.available()) {
    if (count == 4) {count = stepper1.setting(3);}
    ch = Serial.read();
    if (ch == 35 || ch == 36) {
      result_dir = (ch - dirmaker);
      stepper1.setting(result_dir);
      stepper1.procWork(accel);
    } else if (ch >=  48 && ch <= 57) {
      stepper1.procWork(accel); 
      count = stepper1.asciino(ch, count);
    } else {
      stepper1.idle(accel, 4);
    }
  } else {
    count = stepper1.setting(4); //operation end
  }
}

