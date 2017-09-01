// read char from python
// if vENA = 1(LOW) then stepmov() is working
// Serial sending 0 ~ 9, a ~ z
// char data latency is 0.11 ~ 0.15 sec
// function stepmov has 7 value
// setting the maximum speed and steps on start states


#define ENA     13
#define STEP    9//for step signal
#define DIR     8//for direction

int i;
char ch;
int vENA;
int vDIR;
int vstep;
int vvelo;
int vmax;
int vaccel;

void setup() {
    Serial.begin(115200);
    pinMode(ENA, OUTPUT);
    pinMode(STEP, OUTPUT);
    pinMode(DIR, OUTPUT);
    // stepper off
    digitalWrite(ENA, HIGH);
}


void loop() {
  if(Serial.available() > 0){
    ch = Serial.read();
    charconverter(ch);
    
  }
}

// arter charconverter, function must decide to select between two options
void treestepper() {
    lauchster();
    terminatestep();
    if (Serial.avilable() >) {
    } else {
    steadystep();
    }
}

a ~ t : 

//x = start, y = process, z = terminal
//w = DIR
//xyz = DIR, a~w : velocity, 1 ~ 0 : accelation
void charconverter(char conv){
    if (conv == 'z') {
      vENA = 1
    }
    else if (conv == 'y') {
      vEna = 2
     }
     else if (conv == 'x') {
     vEna = 3
     }     
    if (conv == 'a') {
      i += 400;
      Serial.println(i);
    }
    else if (conv == 'b') {
      i += 50;
      Serial.println(i);
    }
    else if (conv == 'c') {
      i += 5;
    }
}


//(start, direction, stepcount, velocity, maxcimun speed, accelalte value)
//u ~ z : lauchphase
//U ~ Z : terminal phase
void lauchstep() {
  if (vEna == 'u') {
  digitalWrite(ENA, HIGH);
  } else if (vEna == -1) {
  digitalWrite(ENA, LOW);
    
  }
}

void dirstep() {
  if (vDir == 1) {
    digitalWrite(DIR, HIGH);
  } else if (vDir == -1) {
  digitalWrite(DIR, LOW)
  }
}

void stepmov(){
    
}

void stepmov(){
  if (vEna == 1) {
    digitalWrite(ENA, LOW)
    vEna == 0
    }

    if (vDir < 0) {
    digitalWrite(DIR, LOW);
    } else if (vDir > 0) {
      digitalWrite(DIR, HIGH);
    }
    
    
  for (i = 0; i < vstep; i++) {
    digitalWrite(STEP, HIGH);
    delayMicroseconds(vvelo);
    digitalWrite(STEP, LOW);
    delayMicroseconds(vvelo);
    if (vvelo > vmax) {
      vvelo = vvelo - vaccel;
    }
  }
  if (vEna > 0) {
    digitalWrite(ENA, LOW);
  }
  else if (vEna < 0) {
    digitalWrite(ENA, HIGH);
  }    
}
