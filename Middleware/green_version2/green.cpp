#include "Arduino.h"
#include "green.h"

#define limit 510

#define intmaker 48

green::green(int pulse, int EnaNo, int DirNo, int StepNo)
{
   _pwm = pulse;
  _ENA = EnaNo;
  _DIR = DirNo;
  _STEP = StepNo;
  pinMode(_ENA, OUTPUT);
  digitalWrite(_ENA, HIGH);
  pinMode(_DIR, OUTPUT);
  pinMode(_STEP, OUTPUT);
}

int green::setting(int setvalue) {
  if (setvalue == 1) {
    digitalWrite(_DIR, HIGH);
  } else if (setvalue == 2) {
    digitalWrite(_DIR, LOW);
  } else if (setvalue == 3) {
    digitalWrite(_ENA, LOW);
    digitalWrite(_STEP, HIGH);
    return setvalue;
  } else if ( setvalue == 4) {
    digitalWrite(_ENA, HIGH);
    digitalWrite(_STEP, LOW);
    _pulse = 1200;
    return setvalue;
  }
}

//this working when status changing
void green::procWork(int Accel) {
  if (_pwm >= limit) {
    _pwm = (_pwm - Accel);
  } else {
    _pwm = limit;
  }
  delayMicroseconds (_pwm);
  digitalWrite(_STEP, LOW);
  digitalWrite(_STEP, HIGH);
}

//this is working when idle states
void green::idle(int Accel, int peri) {
  for (_i = 1; _i <= peri; _i++) {
    if (_pwm >= limit) {
      _pwm = (_pulse - Accel);
    } else {
      _pwm = limit;
    }
    delayMicroseconds (_pwm);
    digitalWrite(_STEP, LOW);
    digitalWrite(_STEP, HIGH);
  }
}

int green::asciino(char c1, int digit) {
  _d = (c1 - intmaker);
  switch (digit) {
    case 3:
      _digitsum = 0;
      _digitsum += (_d * 1000);
      digit --;
      return digit;
    case 2:
      _digitsum += (_d * 100);
      digit --;
      return digit;
    case 1:
      _digitsum += (_d  * 10);
      digit --;
      return digit;
    case 0:
      _digitsum += (_d);
      _pulse = _digitsum;
      digit = 3;
      return digit;
  }
}
