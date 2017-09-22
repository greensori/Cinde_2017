#include "Arduino.h"
#include "green.h"

#define intmaker 48

green::green(int d)
{
  _count = d;
  _digitsum = 0;
}

void green::active(int enano, int stepno) {
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

int green::asciino(char d, int digit) {
  switch (digit) {
    case 3:
      _digitsum = 0;
      _digitsum += ((d - intmaker) * 1000);
      break;
    case 2:
      _digitsum += ((d - intmaker) * 100);
      break;
    case 1:
      _digitsum += ((d - intmaker) * 10);
      break;
    case 0:
      _digitsum += (d - intmaker);
      return _digitsum;
  }
}


void green::tester(int d, int e, int f) {
  delayMicroseconds(f);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(e, HIGH);
}

int green::regional(int d) {
  temp += d;
  return intmaker;
}
