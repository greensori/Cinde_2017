#include "Arduino.h"
#include "cinde.h"

#define delaycoef (rest - 100)

enum { 
  intmaker = 48,
  pwmLimit = 570
};

cinde::cinde(int sumstep)
{
  _maxAnalog = sumstep;
  _count = 0;
  _workingStep = -1;
}

/*
 * savings specific stepping infotmation to this
 */
void cinde::stepstatus(int ena, int dir, int stepno) {
  _stepinfo[0] = ena;
  _stepinfo[1] = dir;
  _stepinfo[2] = stepno;
  digitalWrite(_stepinfo[0], LOW);
  digitalWrite(_stepinfo[2], HIGH);
}


/*
 * must already savings stepper information at the stepstatus
 */
void cinde::statuschanger(int count) {
  if (count == 0) {
    digitalWrite(_stepinfo[2], LOW);
    digitalWrite(_stepinfo[0], HIGH);
  } else if (count == 1) {
    digitalWrite(_stepinfo[1], LOW);
  } else if (count == 2) {
    digitalWrite(_stepinfo[1], HIGH);
  }
}

int cinde::stepwork(int stepno, int Pwm, int Acc) {
  /*
  Serial.print ("stepwork :");
  Serial.println (stepno);
  */
  /*accelation parts****************
  */
  if (Pwm >= pwmLimit) {
    Pwm = (Pwm - Acc);
  } else if (Pwm < pwmLimit) {
    Pwm = pwmLimit;
  }
  digitalWrite(stepno, LOW);
  digitalWrite(stepno, HIGH);
  return Pwm;
}

int cinde::analogReader(int rest, int Analog) {
/*this is reducing microdelaytims, becuase analog read using almost
100microsecodns
receving remain delaytimemr using (int rest)
delaycoef return (int rest - 100)
*/
  Serial.print ("_A");
  Serial.println (analogRead(Analog));
  return delaycoef;
}

int cinde::asciino(char c1, int stepping) {
  if (_workingStep != stepping) {
    //Serial.println ("setting _working step");
    _digit = 3;
    _workingStep = stepping;
  }
  _d = (c1 - intmaker); 
  switch (_digit) {
    case 3:
      _digitsum = 0;
      _digitsum += (_d * 1000);
      _digit --;
      if (_digitsum == 0) {
        return 900;
      } else {
      return _digitsum;    
      }
    case 2:
      _digitsum += (_d * 100);
      _digit --;
      return _digitsum;
    case 1:
      _digitsum += (_d  * 10);
      _digit --;
      return _digitsum;
    case 0:
      _digitsum += (_d);
      _digit = 3;
      return _digitsum;
  }
}

/*
 * devided value receiving present devided steps value
 * it returns present devided staeps
 */
int cinde::drv8825Microstep(float devided, int m0, int m1, int m2) {
  if (devided == 1) {
    digitalWrite(m0, LOW);
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
  } else if (devided == 2) {
    digitalWrite(m0, HIGH);
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);    
  } else if (devided == 4){
    digitalWrite(m0, LOW);
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);    
  } else if (devided == 8) {
    digitalWrite(m0, HIGH);
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);    
  } else if (devided == 16) {
    digitalWrite(m0, LOW);
    digitalWrite(m1, LOW);
    digitalWrite(m2, HIGH);    
  } else if (devided == 32) {
    digitalWrite(m0, HIGH);
    digitalWrite(m1, LOW);
    digitalWrite(m2, HIGH);    
  }
  return devided;
}


void cinde::tester() {
}
