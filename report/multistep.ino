//controlling 3 stepping motor controller
//must setting new (int totalswitch)
//char totalswitch = a ~ c (1 stepping) d, e, f(1-2), (2-3), (1-3) g(1-2-3)
//stepset() -> setting pulse -> end
//before stepping operateion ending, must send serial signals
//step = pulse * 2


#define pulselimit 2000
#define limitrpm 870
#define sumStep 3

const int ENA[sumStep] = {5, 8, 11};
const int DIR[sumStep] = {6, 9, 12};
const int STEP[sumStep] = {7, 10, 11};

// reading from python
char ch;
// using temporaly like for
int count;
int i;
//stepping number
int stepno;
//how many stepping works
int worker;
//rx storage remain pulse  timer
//if (rx < 0) then there is no working
int rx = 2000;
//saving remain pulse
int steploop[2];
//setting 3stepping motors (steps, pulse, maxpulse, acc)
int stepPulse[sumStep] = {1000, 1000, 1000};
int stepCount[sumStep];
int stepAccel[sumStep] = {0, 0, 0};
int accelLimit[sumStep] = {870, 870, 870};
int remainPulse[sumStep];
//using in dvacalculator

int result;
int dvapulse;
//saves remain stepping pulse [stepno, pulse]
int delaystep[2];
//
int steptimer;

void setup() {
    Serial.begin(115200);
    for (i= 0; i < 3; i++) {
       pinMode(ENA[i], OUTPUT);
       digitalWrite(ENA[i], HIGH);
       pinMode(DIR[i], OUTPUT);     
       pinMode(STEP[i], OUTPUT);
    }
}

//charconverter. reang serial information from pc
//stepmov ->  dvastep() -> stepcal()
//if there is remain steps then working remain proc

void loop() {
  stepCount[0] = 200;
  if (Serial.available() > 0) {
    ch = Serial.read();
    charconverter();
    if (worker >= 0) {
      steptimer = pulselimit;
      stepmove(); 
    }
  }
}

// # $ % = initiate setting stepping
// 0~7 accelation setting
// 89 setting dirextion
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
      Serial.print ("setiing accelaration");
      switch (ch) {
        case 48:
          stepAccel[stepno] = 0;
          break;
        case 49:
          stepAccel[stepno] = 1;
          break;
        case 50:
          stepAccel[stepno] = 2;
          break;
        case 51:
          stepAccel[stepno] = 3;
          break;
        case 52:
          stepAccel[stepno] = -1;
          break;
        case 53:
          stepAccel[stepno] = -2;
          break;
        case 54:
          stepAccel[stepno] = -3;
          break;
        case 55:
          stepAccel[stepno] = (stepAccel[stepno] * 2);
          break;
        case 56:
          digitalWrite(DIR[stepno], HIGH);
          break;
        case 57:
          digitalWrite(DIR[stepno], LOW);
          break;
      } //end switch
    } else if (97<= ch && ch <= 122) {
      Serial.println ("setting pulse");
    switch (ch) {
      case 97:
        stepPulse[stepno] = 800;
        break;
      case 98:
        stepPulse[stepno] = 1000;
        break;
      case 99:
        stepPulse[stepno] = 2000;
        break;
      default:
        break;            
     } //end switch
    } else if (65 <= ch && ch <= 90) {
      Serial.println ("which wtepping will be on");
      switch (ch) {
        case 65:
          worker = 0;
          break;
        case 66:
          worker = 1;
          break;
        case 67:
          worker = 2;
          break;
        case 68:
          worker = 3;
          break;
        case 69:
          worker = 4;
          break;
        default:
          break;
      } // switch end
  } //end if
} // end proc

void remainstep() {
  
}

void pulseset() {
    if (stepPulse[stepno] >= accelLimit[stepno]) {
        stepPulse[stepno] = stepPulse[stepno] - stepAccel[stepno];
    } else {
        stepPulse[stepno] = accelLimit[stepno];
    } // if end
} //proc end



void stepmove() {
  if (worker == 0) {
    Serial.println ("switch 1on");
    digitalWrite(ENA[worker], LOW);
      for (count = 0; count < stepCount[0]; count++) {
        digitalWrite(STEP[worker], HIGH);
        delayMicroseconds(stepPulse[0]);
        digitalWrite(STEP[worker], LOW);
        pulseset();
        }
        Serial.println(stepPulse[stepno]);
        digitalWrite(STEP[worker], HIGH);
      } else if (worker == 1) {
      digitalWrite(ENA[worker], LOW);
      for (count = 0; count < stepCount[0]; count++) {
        digitalWrite(STEP[worker], HIGH);
        delayMicroseconds(stepPulse[worker]);
        digitalWrite(STEP[worker], LOW);
        pulseset();
        }
        Serial.println(stepPulse[stepno]);
        digitalWrite(ENA[worker], HIGH);
     } else if (worker == 2) {
        digitalWrite(ENA[worker], LOW);
        for (count = 0; count < stepCount[0]; count++) {
          digitalWrite(STEP[worker], HIGH);
          delayMicroseconds(stepPulse[worker]);
          digitalWrite(STEP[worker], LOW);
          pulseset();
          }
          Serial.println(stepPulse[stepno]);
          digitalWrite(ENA[2], HIGH);
      } else if (worker == 3) {
        Serial.println ("double");
        digitalWrite(ENA[1], LOW);
        digitalWrite(ENA[2], LOW);
        for (count = 0; count < stepCount[0]; count++) {
          digitalWrite(STEP[1], HIGH);
          digitalWrite(STEP[2], HIGH);
          delayMicroseconds(stepPulse[2]);
          digitalWrite(STEP[1], LOW);          
          digitalWrite(STEP[2], LOW);
          pulseset();
          }
          Serial.println(stepPulse[stepno]);
          digitalWrite(ENA[2], HIGH);          
          digitalWrite(ENA[3], HIGH);          
      }//end if
      worker = -1;
} // end proc

//moving 2 stepping 
void dvastep() {  
  // if rx goes under zero then end working  
  if (worker == 3) {
    digitalWrite(ENA[0], LOW);
    digitalWrite(ENA[1], LOW);
    digitalWrite(STEP[0], HIGH);
    digitalWrite(STEP[1], HIGH);
    while (rx > 0) {
      if (stepPulse[0] >= stepPulse[1]) {
      dvacal(0, 1);
    } else if (stepPulse[0] < stepPulse[1]) {
      dvacal(1, 0);
    }} // while, if end
  } else if (worker == 4) {
    digitalWrite(ENA[0], LOW);
    digitalWrite(ENA[2], LOW);
    digitalWrite(STEP[0], HIGH);
    digitalWrite(STEP[2], HIGH);      
    while (rx > 0) {
      if (stepPulse[0] >= stepPulse[2]) {
      dvacal(0, 2);
    } else if (stepPulse[0] < stepPulse[2]) {
      dvacal(2, 0);
    }}
  } else if (worker == 5) {
    while (rx > 0) {
      if (stepPulse[0] >= stepPulse[2]) {
      dvacal(0, 2);
    } else if (stepPulse[0] < stepPulse[2]) {
      dvacal(2, 0);
    }}    
  }
}



//before this proc there will be existing if (pulse[a] >= pulse[b]
void dvacal(int a, int b) {
      if (remainPulse[b] > 0) {
        delayMicroseconds(remainPulse[b]);
        remainPulse[b] = 0;
      } else if (remainPulse[a] > stepPulse[b]) {
        remainPulse[a] = (remainPulse[a] - stepPulse[b]);
        remainPulse[a] -= stepPulse[b];
        steptimer -= stepPulse[b];
        rx -= stepPulse[b];
        delayMicroseconds(stepPulse[b]);
        digitalWrite(STEP[b], LOW);
        digitalWrite(STEP[b], HIGH);
      } else if (remainPulse[a] < stepPulse[b]) {
        remainPulse[b] = stepPulse[b] - remainPulse[a];
        rx -= remainPulse[b];
        delayMicroseconds (remainPulse[b]);
        digitalWrite(STEP[a], LOW);
        digitalWrite(STEP[a], HIGH);
      } else if (remainPulse[a] == stepPulse[b]) {
        rx -= stepPulse[b];
        remainPulse[a] = stepPulse[a] - stepPulse[b];
        delayMicroseconds(remainPulse[b]);
        digitalWrite(STEP[a], LOW);
        digitalWrite(STEP[b], LOW);
        digitalWrite(STEP[a], HIGH);
        digitalWrite(STEP[b], HIGH);
      }
}


