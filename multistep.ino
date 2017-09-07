//controlling 3 stepping motor controller
//must setting new (int totalswitch)
//char totalswitch = a ~ c (1 stepping) d, e, f(1-2), (2-3), (1-3) g(1-2-3)
//stepset() -> setting pulse -> end
//before stepping operateion ending, must send serial signals
//step = pulse * 2

#define ENA1    5
#define DIR1    6
#define STEP1   7
#define ENA2    8
#define DIR2    9
#define STEP2   10
#define ENA3    11
#define DIR3    12
#define STEP3   13

#define limitrpm 870

char ch;
int count;
//steps, rpm, max, acc
int totalswitch;
//setting 3stepping motors (steps, pulse, maxpulse, acc)
//int vstep[3];
int vpulse[3];
int vlimit[3];
int vacc[3];
int vdir[3];
int signal;


void setup() {
    Serial.begin(115200);
    pinMode(ENA1, OUTPUT);
    pinMode(STEP1, OUTPUT);
    pinMode(DIR1, OUTPUT);
    pinMode(ENA2, OUTPUT);
    pinMode(STEP2, OUTPUT);
    pinMode(DIR2, OUTPUT);
    pinMode(ENA3, OUTPUT);
    pinMode(STEP3, OUTPUT);
    pinMode(DIR3, OUTPUT);
    //stepper off
    digitalWrite(ENA1, HIGH);
    digitalWrite(DIR1, HIGH);
    digitalWrite(ENA2, HIGH);
    digitalWrite(DIR2, HIGH);
    digitalWrite(ENA3, HIGH);
    digitalWrite(DIR3, HIGH);
    }


void loop() {
  if (Serial.available() > 0) {
    ch = Serial.read();
    if (48 <= ch && ch <= 57) {
      stepset();
    } else {
      digitalWrite(ENA1, LOW);
      digitalWrite(ENA2, LOW);
      digitalWrite(ENA3, LOW);
      charconverter();
      stepmov();
    }
  // else { analog.read(potentiometer)) <- calculating status
}}

//to give a total switch values
void charconverter() {
  switch (ch) {
      case 'q':
          step[0] = 50;
      case 'w':
          step[0] = 100;
  }
           signal = (step[0] / 2)
}

//
void stepset() {
  switch (ch) {
    case '['
}

void  stepmov() {    
  if (vstep[0] <= 1) {
    vstep[0] = 2;
  }
   for (count = 0; count < vstep[0]; count++) {
    digitalWrite(STEP, HIGH);
    delayMicroseconds(vstep[1]);
    digitalWrite(STEP, LOW);
    pulseset();
  }
    for(count = 0; count < vstep[0];
  Serial.println(vstep[1]);
  digitalWrite(ENA1, HIGH);
  digitalWrite(ENA2, HIGH);
  digitalWrite(ENA3, HIGH);
}

void pulseset() {
    for (i = 0; i < step[0]; i++)
    if (vstep[1] >= vstep[2]) {
        vstep[1] = vstep[1] - vstep[3];
    } else {
        vstep[1] = vstep[2];
    }
}
