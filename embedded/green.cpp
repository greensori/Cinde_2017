#include "Arduino.h"
#include "green.h"

green::green(int a)
{
  temp = a;
}

void green::active(int enano, int stepno) {
  Serial.print ("serial pin___");
  Serial.println (enano);
  digitalWrite(enano, LOW);
  digitalWrite(stepno, HIGH);
}

void green::Terminal(int enano, int stepno) {
  digitalWrite(enano, HIGH);
  digitalWrite(stepno, LOW);
}

void green::idle(int d, int e, int f) {
  if ( f == 1) {
    digitalWrite(e, HIGH);
  } else if ( f == 2) {
    digitalWrite(e, LOW);
  }
  digitalWrite(d, LOW);
  digitalWrite(d, HIGH);
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


void green::tester(int d, int e, int f) {
  delayMicroseconds(f);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(e, HIGH);
}
