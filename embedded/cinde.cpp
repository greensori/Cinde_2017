#include "Arduino.h"
#include "cinde.h"

#define tempuse 48

#define delaycoef (rest - 100)

cinde::cinde(int maxAnalog)
{
  _maxAnalog = maxAnalog;
  _count = 0;
}

void cinde::stepoff(int number, int ena) {
  digitalWrite(number, LOW);
  digitalWrite(ena, LOW);
}

void cinde::stepwork(int number) {
  digitalWrite(number, LOW);
  digitalWrite(number, HIGH);
}

int cinde::analogReader(int rest, int Analog) {
  Serial.print ("_A");
  Serial.println (analogRead(Analog));
  return delaycoef;
}

int cinde::asciichanger(char c) {
  if (c
}
