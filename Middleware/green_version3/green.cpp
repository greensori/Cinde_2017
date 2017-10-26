#include "Arduino.h"
#include "green.h"

#define limit 510

#define intmaker 48

#define renew_pwm 2000

#define ptmAvg (_total * 0.25)

static void someting() {
  Serial.println ("calculator");
}


// analogread takes almost 100ms
// servo must takes 2000ms
// pwm, ena, dir, step, servo, potentio
green::green(int pulse, int EnaNo, int DirNo, int StepNo, int ServoNo, int PotenNo)
{
   _pwm[0] = pulse;
  _ENA = EnaNo;
  _DIR = DirNo;
  _STEP = StepNo;
  _Servo = ServoNo;
  _Potentio = PotenNo;
  _pcount = 0;
  pinMode(_ENA, OUTPUT);
  digitalWrite(_ENA, HIGH);
  pinMode(_DIR, OUTPUT);
  pinMode(_STEP, OUTPUT);
  pinMode(_Servo, OUTPUT);
}

int green::setting(int setvalue) {
  if (setvalue == 1) {
    digitalWrite(_DIR, HIGH);
  } else if (setvalue == 2) {
    digitalWrite(_DIR, LOW);
  } else if (setvalue == 3) {
    // enable stepping
    // initiating pwmremain values to 2000
    // this makes to start spepping pulse
    _pwmremain = 2000;
    digitalWrite(_ENA, LOW);
    digitalWrite(_STEP, HIGH);
    return setvalue;
  } else if ( setvalue == 4) {
    //pwm speed is setting to 1200
    digitalWrite(_ENA, HIGH);
    digitalWrite(_STEP, LOW);
    _pwm[0] = 1200;
    return setvalue;
  }
}

//this working when status changing
void green::procWork(int Accel) {
  if (_pwm[0] >= limit) {
    _pwm[0] = (_pwm[0] - Accel);
  } else {
    _pwm[0] = limit;
  }
  delayMicroseconds (_pwm[0]);
  digitalWrite(_STEP, LOW);
  digitalWrite(_STEP, HIGH);
}

//this is working when idle states
void green::idle(int Accel, int peri) {
  for (_i = 1; _i <= peri; _i++) {
    if (_pwm[0] >= limit) {
      _pwm[0] = (_pwm[0] - Accel);
    } else {
      _pwm[0] = limit;
    }
    delayMicroseconds (_pwm[0]);
    digitalWrite(_STEP, LOW);
    digitalWrite(_STEP, HIGH);
  }
}


int green::idle_new(int Accel, int pwmServo) {
  _pwmremain += 2000;
  while (_pwmremain > _pwm[0] || _pwmremain > pwmServo) {
  _pwmServo = pwmServo;
  _pwm[1] = _pwm[0];
// -------------while start -----------
    if (_pwm[0] >= pwmServo) { 
      _gap = (_pwm[0] - pwmServo); //getting _gap value
      if (_pwm[0] >= limit) {
        _pwm[0] = (_pwm[0] - Accel);
      } else {
        _pwm[0] = limit;
      } // accelation setting
      while (_pwm[1] > _gap) {
        digitalWrite(_Servo, HIGH);
        delayMicroseconds (_gap);
        digitalWrite(_Servo, LOW);
        _pwmremain -= _gap;
        _pwm[1] -= _gap;
        if (_pwm[1] <= _gap) {
          delayMicroseconds(_pwm[1]);
          _pwmremain -= _pwm[1];
          digitalWrite(_STEP, LOW);
          digitalWrite(_STEP, HIGH);      
        }
      } // while end
//-------------------- servo work end-------------
    } else if (_pwm[0] < pwmServo) { //case that servo pwm is smaller than pwm.
      _gap = (pwmServo - _pwm[0]);
      if (_pwm[0] >= limit) {
        _pwm[0] = (_pwm[0] - Accel);
      } else {
        _pwm[0] = limit;
      } // accelation setting    
      while (_pwmServo > _gap) {
        delayMicroseconds (_gap);
        digitalWrite(_STEP, LOW);
        digitalWrite(_STEP, HIGH);
        _pwmremain -= _gap;
        _pwmServo -= _gap;
        if (_pwmServo <= _gap) {
          digitalWrite(_STEP, HIGH);
          delayMicroseconds(_pwmServo);
          _pwmremain -= _pwmServo;
          digitalWrite(_STEP, LOW);      
        }
      } // while end      
    } // if end
  }// end while
}

int green::preader() {
  _potentioSensor[_pcount] = analogRead(_Potentio);
  _pcount++;
  if (_pcount == 4) {
    _total = 0;
    for (_i = 0; _i <= 3; _i++) {
      _total += (_potentioSensor[_i]);
    }
    _total = ptmAvg;
    _pcount = 0;
  }
}


int green::delayprint() {
  Serial.println ("delay test");
  someting();
  return 1000;
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
      _pwm[0] = _digitsum;
      digit = 3;
      return digit;
  }
}
