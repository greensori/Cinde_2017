//controlling 3 stepping motor controller
//must setting new (int totalswitch)
//char totalswitch = a ~ c (1 stepping) d, e, f(1-2), (2-3), (1-3) g(1-2-3)
//stepset() -> setting pulse -> end
//before stepping operateion ending, must send serial signals
//step = pulse * 2



#define ENA1    5
#define STEP1   7
#define ENA2    8
#define STEP2   10
#define ENA3    11
#define STEP3   13

#define limitrpm 870
const int dir[3] = {6, 9, 12};

char ch;
int count;
int i;
int stepno;
int goswitch;
//setting 3stepping motors (steps, pulse, maxpulse, acc)
int vpulse[3] = {1000, 1000, 1000};
int vstep[3];
int vacc[3] = {0, 0, 0};
int vlimit[3] = {870, 870, 870};

void setup() {
    Serial.begin(115200);
    pinMode(ENA1, OUTPUT);
    pinMode(ENA2, OUTPUT);
    pinMode(ENA3, OUTPUT);
    pinMode(STEP1, OUTPUT);
    pinMode(STEP2, OUTPUT);
    pinMode(STEP3, OUTPUT);
    for (i= 0; i < 3; i++) {
       pinMode(dir[i], OUTPUT);
    }
    //stepper off
    digitalWrite(ENA1, HIGH);
    digitalWrite(ENA2, HIGH);
    digitalWrite(ENA3, HIGH);
}

void loop() {
  if (Serial.available() > 0) {
    ch = Serial.read();
    charconverter();
    if (goswitch > 0) {
      stepmove(); 
    } 
    }
}


void charconverter() {
    if (35 <= ch && ch <= 37) {
      switch (ch) {
        case 35:
          stepno = 0;
          Serial.println ("setting stepping 1");
          break;
        case 36:
          stepno = 1;
          Serial.println ("setting stepping 2");   
          break;
        case 37:
          stepno = 2;
          Serial.println ("setting stepping 3");          
          break;
      }
    } else if (48<= ch && ch <= 57) {
      switch (ch) {
        case 48:
          vacc[stepno] = 0;
          break;
        case 49:
          vacc[stepno] = 1;
          break;
        case 50:
          vacc[stepno] = 2;
          break;
        case 51:
          vacc[stepno] = 3;
          break;
        case 52:
          vacc[stepno] = -1;
          break;
        case 53:
          vacc[stepno] = -2;
          break;
        case 54:
          vacc[stepno] = -3;
          break;
        case 55:
          vacc[stepno] = (vacc[stepno] * 2);
          break;
        case 56:
          digitalWrite(dir[stepno], HIGH);
          break;
        case 57:
          digitalWrite(dir[stepno], LOW);
          break;
      } //end switch
    } else if (97<= ch && ch <= 122) {
    switch (ch) {
      case 97:
        vpulse[stepno] = 800;
        break;
      case 98:
        vpulse[spepno] = 700;
        break;
      default:
        break;
            
     } //end switch
  } //end if
} // end proc


//!33[91]93
void stepmove() {
  if (goswitch == 1) {
    digitalWrite(ENA1, LOW);
      for (count = 0; count < vstep[0]; count++) {
        digitalWrite(STEP1, HIGH);
        delayMicroseconds(vpulse[0]);
        digitalWrite(STEP1, LOW);
        pulseset();
        }
    Serial.println(vpulse[stepno]);
    digitalWrite(ENA1, HIGH);
  }
} // end proc

void pulseset() {
    if (vpulse[stepno] >= vlimit[stepno]) {
        vpulse[stepno] = vpulse[stepno] - vacc[stepno];
    } else {
        vpulse[stepno] = vlimit[stepno];
}
