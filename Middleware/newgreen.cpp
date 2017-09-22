#include "Arduino.h"
#include "green.h"

#define limit 510

green::green((int EnaNo, int DirNo, int StepNo)
{
  _ENA = EnaNo;
  _DIR = DirNo;
  _STEP = StepNo;
  pinMode(_ENA, OUTPUT);
  digitalWrite(_ENA, HIGH);
  pinMode(_DIR, OUTPUT);
  pinMode(_STEP, OUTPUT);
}

void green::setiing(int sta) {
  if (sta == 0) {
    digitalWrite(_ENA, LOW);
    digitalWrite(_STEP, HIGH);
  } else if ( sta == 1) {
    digitalWrite(_ENA, HIGH);
    digitalWrite(_STEP, LOW);
  } else if (sta == 2) {
    digitalWrite(_DIR, HIGH);
  } else if (sta == 3) {
    digitalWrite(_DIR, LOW);
  }
}

void green::idle(int Accel) {
  if (_pulse >= limit) {
    _pulse = (_pulse - Accel);
  } else {
    _pulse = limit;
  }
  delayMicroseconds (_pulse);
  digitalWrite(_STEP, LOW);
  digitalWrite(_STEP, HIGH);
}

int green::asciino(int d, int digit) {
  switch (digit) {
    case 3:
      _digitsum = 0;
      _digitsum += (d * 1000);
      break;
    case 2:
      _digitsum += (d * 100);
      break;
    case 1:
      _digitsum += (d  * 10);
      break;
    case 0:
      _digitsum += (d);
      _pulse = _digitsum;
      return _digitsum;
  }
}

