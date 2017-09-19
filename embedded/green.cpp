#include "Arduino.h"
#include "green.h"

green::green(int sumStep)
{
  _pin = sumStep;
}

void green::on(int STEP) {
  digitalWrite(STEP, HIGH);  
}

void green::ter(int STEP, int ENA) {
  digitalWrite(STEP, LOW);
  digitalWrite(ENA, HIGH);
}

void green::idle(int STEP, int sleep) {
  delayMicroseconds(sleep);
  digitalWrite(STEP, LOW);
  digitalWrite(STEP, HIGH);
}

