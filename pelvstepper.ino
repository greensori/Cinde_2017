
#define ENA     13
#define STEP    9//for step signal
#define DIR     8//for direction

char ch;
int count;
int i;
//steps, rpm, max, acc
int vstep[4] = {110, 900, 470, 0};



void setup() {
    Serial.begin(115200);
    pinMode(ENA, OUTPUT);
    pinMode(STEP, OUTPUT);
    pinMode(DIR, OUTPUT);
    //stepper off
    digitalWrite(ENA, HIGH);
    digitalWrite(DIR, HIGH);
    }


void loop() {
  if (Serial.available() > 0) {
    ch = Serial.read();
    if (48 <= ch && ch <= 57) {
      stepset();
    } else {
      digitalWrite(ENA, LOW);
      charconverter();
      stepmov();
  }
}}

void charconverter() {
  if (ch == 'a') {
    vstep[0] = 110;
    vstep[1] = 1500;
    vstep[2] = 470;
  } else if (ch == 'A') {
    vstep[0] = 110;
    vstep[1] = 1500;
    vstep[2] = 470;
  } else if (ch == 'b') {
    vstep[0] = 20;
  } else if (ch == 'c') {
    vstep[0] = 1;
    vstep[1] = 5000;
  } else if (ch == 'd') {
    
  }
}

void stepset() {
  if (ch == '0') {
    digitalWrite(DIR, LOW);
    vstep[3] = 0;
  } else if(ch == '1') {
    digitalWrite(DIR, LOW);
    vstep[3] = 1;
  } else if ( ch == '2') {
    digitalWrite(DIR, LOW);
    vstep[3] = 2;
  } else if (ch == '3') {
    digitalWrite(DIR, LOW);
    vstep[3] = 3;
  } else if (ch == '4') {
    digitalWrite(DIR, LOW);
    vstep[3] = 4;
  } else if (ch == '5') {
    digitalWrite(DIR, HIGH);
    vstep[3] = 0;
  } else if (ch == '6') {
    digitalWrite(DIR, HIGH);
    vstep[3] = -1;
  } else if (ch == '7') {
    digitalWrite(DIR, HIGH);
    vstep[3] = -2;
  } else if (ch == '8') {
    digitalWrite(DIR, HIGH);
    vstep[3] = -3;
  } else if (ch == '9') {
    digitalWrite(DIR, HIGH);
    vstep[3] = -4;
  }    
}

void  stepmov() {    
  for (i = 0; i < vstep[0]; i++) {
    digitalWrite(STEP, HIGH);
    delayMicroseconds(vstep[1]);
    digitalWrite(STEP, LOW);
    delayMicroseconds(vstep[1]);
    if (vstep[1] >= vstep[2]) {
      vstep[1] = vstep[1] - vstep[3];
    } else {
      vstep[1] = 470;
    }
  }
  Serial.println (vstep[1]);
  digitalWrite(ENA, HIGH);
}
