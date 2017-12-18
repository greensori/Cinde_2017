#include "Arduino.h"
#include "cinde.h"

#define intmaker 48

#define delaycoef (rest - 100)

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

void cinde::stepwork(int number) {
  digitalWrite(number, LOW);
  digitalWrite(number, HIGH);
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
/*this is changing pwm values seperate stepping
ascii values must always return digit values
and when we changing curent stepping numbers then digit must be 3
making (int _digit)
if _digit values is changed then this module initiating digiit values to 3
this module return pwm values at digit 0 case.
*/
/* complete
Serial.print ("_workingStep : ");
Serial.println (_workingStep);
Serial.print ("input step : ");
Serial.println (stepping);
*/
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


void cinde::tester() {
  
}
