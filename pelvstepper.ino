
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
  }
}

void charconverter() {
  if (ch == 'a') {
    vstep[0] = 110;
    vstep[1] = 1500;
    vstep[2] = 470;
    vstep[3] = 1;
  } else if (ch == 'A') {
    vstep[0] = 110;
    vstep[1] = 1500;
    vstep[2] = 470;
    vstep[3] = -1; 
  } else if (ch == 'b') {
    vstep[0] = 20;
  } else if (ch == 'c') {
    vstep[0] = 2;
    vstep[1] = 5000;
  } else if (ch == 'd') {
    
  }
}


void  stepmov() {
    if (97<= ch && ch <= 122) {
     digitalWrite(DIR, LOW);
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
  Serial.println (vstep[1]);
  digitalWrite(ENA, HIGH);
}
