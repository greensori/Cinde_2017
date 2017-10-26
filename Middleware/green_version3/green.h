#ifndef green_h
#define green_h

#include "Arduino.h"



class green
{
  private:
    int _digitsum; //to getting a pulse information from pc
    int _pwm[2]; //saving stepping pulse, 0(original) 1(changable)
    int _pwmremain; //for saving remain pwm
    int _gap; // saving pwm differences between servo and stepping
    int _ENA;
    int _DIR;
    int _STEP;
    int _Servo; //servo motor pi value
    int _pwmServo; //savings servo angle status
    int _Potentio; // potentio pin no
    int _potentioSensor[4]; // savings recent potetiometer value
    int _pcount; //count for recording seprate values on potentio~[4]
    int _total; //to getting potentiometer average
    int _d; 
    int _lv; //receiving present status
    int _i; //using temporary
  public:
    green(int pulse, int EnaNo, int DirNo, int StepNo, int ServoNo, int PotenNo);
    int setting(int setvalue); //on.off stepping or, changing direction
    void procWork(int Accel); // while Serialread is working, this proc will working
    void idle(int Accel, int peri); //idle state working
    int idle_new(int Accel, int pwmServo);
    int asciino(char c1, int digit); //getting information from pc, making pwm
    int preader(); //read information from potentiometer
    int potentioavg(int poten);
    int servowork(int pwmServo);
    int delayprint();
};

#endif
