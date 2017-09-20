#include "Arduino.h"
#include "green.h"

green::green(int a)
{
  temp = a;
}

void green::active(int STEP) {
  digitalWrite(STEP, HIGH);  
}

void green::Terminal(int enano, int stepno) {
  digitalWrite(enano, LOW);
  digitalWrite(stepno, HIGH);
}

void green::idle(int STEP, int sleep) {
  delayMicroseconds(sleep);
  digitalWrite(STEP, LOW);
  digitalWrite(STEP, HIGH);
}

int green::digitno(char c, int digit) {
  temp = (c - 48);
  switch (digit) {
    case 4:
      temp = (temp * 1000);
      break;
    case 3:
      temp = (temp * 100);
      break;
    case 2:
      temp = (temp * 10);
      break;    
  }
    Serial.print ("read from _");
    Serial.println (temp);
    return temp;
}
