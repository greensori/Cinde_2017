//controlling 3 stepping motor controller
//must setting new (int totalswitch)
//char totalswitch = a ~ c (1 stepping) d, e, f(1-2), (2-3), (1-3) g(1-2-3)
//stepset() -> setting pulse -> end
//before stepping operateion ending, must send serial signals
//step = pulse * 2


#define pulselimit 2000
#define limitrpm 870

const int ENA[3] = {5, 8, 11};
const int DIR[3] = {6, 9, 12};
const int STEP[3] = {7, 10, 11};

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
int pulsegap[3];
//saving remain pulse
int steploop[2];
//setting 3stepping motors (steps, pulse, maxpulse, acc)
int vpulse[3] = {1000, 1000, 1000};
int vstep[3];
int vacc[3] = {0, 0, 0};
int vlimit[3] = {870, 870, 870};
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

void loop() {
  vstep[0] = 200;
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
        vpulse[stepno] = 800;
        break;
      case 98:
        vpulse[stepno] = 1000;
        break;
      case 99:
        vpulse[stepno] = 2000;
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


void pulseset() {
    if (vpulse[stepno] >= vlimit[stepno]) {
        vpulse[stepno] = vpulse[stepno] - vacc[stepno];
    } else {
        vpulse[stepno] = vlimit[stepno];
    } // if end
} //proc end

//!33[91]93
void stepmove() {
  if (worker == 0) {
    Serial.println ("switch 1on");
    digitalWrite(ENA[worker], LOW);
      for (count = 0; count < vstep[0]; count++) {
        digitalWrite(STEP[worker], HIGH);
        delayMicroseconds(vpulse[0]);
        digitalWrite(STEP[worker], LOW);
        pulseset();
        }
        Serial.println(vpulse[stepno]);
        digitalWrite(STEP[worker], HIGH);
      } else if (worker == 1) {
      digitalWrite(ENA[worker], LOW);
      for (count = 0; count < vstep[0]; count++) {
        digitalWrite(STEP[worker], HIGH);
        delayMicroseconds(vpulse[worker]);
        digitalWrite(STEP[worker], LOW);
        pulseset();
        }
        Serial.println(vpulse[stepno]);
        digitalWrite(ENA[worker], HIGH);
     } else if (worker == 2) {
        digitalWrite(ENA[worker], LOW);
        for (count = 0; count < vstep[0]; count++) {
          digitalWrite(STEP[worker], HIGH);
          delayMicroseconds(vpulse[worker]);
          digitalWrite(STEP[worker], LOW);
          pulseset();
          }
          Serial.println(vpulse[stepno]);
          digitalWrite(ENA[2], HIGH);
      } else if (worker == 3) {
        Serial.println ("double");
        digitalWrite(ENA[1], LOW);
        digitalWrite(ENA[2], LOW);
        for (count = 0; count < vstep[0]; count++) {
          digitalWrite(STEP[1], HIGH);
          digitalWrite(STEP[2], HIGH);
          delayMicroseconds(vpulse[2]);
          digitalWrite(STEP[1], LOW);          
          digitalWrite(STEP[2], LOW);
          pulseset();
          }
          Serial.println(vpulse[stepno]);
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
    digitalWrite(STEP[0], HIGH):
    digitalWrite(STEP[1], HIGH):
    while (rx > 0) {
      if (pulse[0] >= pulse[1]) {
      dvacal(0, 1);
    } else if (pulse[0] < pulse[1]) {
      dvacal(1, 0);
    }} // while, if end
  } else if (worker == 4) {
    digitalWrite(ENA[0], LOW);
    digitalWrite(ENA[2], LOW);
    digitalWrite(STEP[0], HIGH):
    digitalWrite(STEP[2], HIGH):      
    while (rx > 0) {
      if (pulse[0] >= pulse[2]) {
      dvacal(0, 2);
    } else if (pulse[0] < pulse[2]) {
      dvacal(2, 0);
    }}
  } else if (worker == 5) {
    while (rx > 0) {
      if (pulse[0] >= pulse[2]) {
      dvacal(0, 2);
    } else if (pulse[0] < pulse[2]) {
      dvacal(2, 0);
    }}    
  }
}



//before this proc there will be existing if (pulse[a] >= pulse[b]
void dvacal(int a, int b) {
      if (pulsegap[b] > 0) {
        delayMicroseconds(pulsegab[b]);
        pulsegap[b] = 0;
      } else if (pulsegap[a] > pulse[b]) {
        pulsegap[a] = (pulsegap[a] - pulse[b]);
        pulsegap[a] -= pulse[b]
        steptimer -= pulse[b];
        rx -= pulse[b]
        delayMicroseconds(pulse[b]);
        digitalWrite(STEP[b], LOW);
        digitalWrite(STEP[b], HIGH);
      } else if (pulsegap[a] < pulse[b]) {
        pulsegap[b] = pulse[b] - pulsegap[a]
        rx -= pulsegap[b]
        delayMicroseconds (pulsegap[b]);
        digitalWrite(STEP[a], LOW);
        digitalWrite(STEP[a], HIGH);
      } else if (pulsegap[a] == pulse[b]) {
        rx -= pulse[b]
        pulsegap[a] = pulse[a] - pulse[b];
        delayMicroseconds(pulsegap[b]);
        digitalWrite(STEP[a], LOW);
        digitalWrite(STEP[b], LOW);
        digitalWrite(STEP[a], HIGH);
        digitalWrite(STEP[b], HIGH);
      }
}

void tristep() {
  
}

void trical() {
  
}
