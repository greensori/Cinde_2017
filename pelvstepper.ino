
#define ENA     13
#define STEP    9//for step signal
#define DIR     8//for direction

char ch;
int count;
int i;
//steps, rpm, max, acc
int vstep[4];



void setup() {
    Serial.begin(115200);
    pinMode(ENA, OUTPUT);
    pinMode(STEP, OUTPUT);
    pinMode(DIR, OUTPUT);
    //stepper off
    digitalWrite(ENA, HIGH);
}


void loop() {
  if (Serial.available() > 0) {
    digitalWrite(ENA, LOW);
    ch = Serial.read();
    charconverter();
    stepmov();
  } else {    
  }
}

void charconverter() {
  if (ch == 'a') {
  vstep[0] = 300;
  vstep[1] = 800;
  vstep[2] = 500;
  vstep[3] = -1;
  }
  if 
}


void  stepmov() {
    Serial.println("stepgo");
    if (97<= ch && ch <= 122) {
     digitalWrite(DIR, LOW);
     Serial.println ("negativemov");
    } else if (65 <= ch && ch<=90) {
      digitalWrite(DIR, HIGH);
    }
    
  for (i = 0; i < vstep[0]; i++) {
    digitalWrite(STEP, HIGH);
    delayMicroseconds(vstep[1]);
    digitalWrite(STEP, LOW);
    delayMicroseconds(vstep[1]);
    if (vstep[1] > vstep[2]) {
      vstep[1] = vstep[1] - vstep[3];
    }
  }
  digitalWrite(ENA, HIGH);
}
