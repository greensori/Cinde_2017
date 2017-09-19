//controlling 3 stepping motor controller
//must setting new (int totalswitch)
//char totalswitch = a ~ c (1 stepping) d, e, f(1-2), (2-3), (1-3) g(1-2-3)
//stepset() -> setting pulse -> end
//before stepping operateion ending, must send serial signals
//step = pulse * 2

#define pulseTimer 4000
#define limitrpm 570
#define sumStep 3

const int ENA[sumStep] = {5, 8, 11};
const int DIR[sumStep] = {6, 9, 12};
const int STEP[sumStep] = {7, 10, 13};
const int accelLimit[sumStep] = {570, 570, 570};

// reading from controller(py)
char ch;
//stepping control guide
//setting int and charconverter does not changed
int stepPulse[sumStep];
//manually settign the amount of pulse count(##maybe do not using anymore
int stepCount[sumStep];
//accelation value of stepping motor
int stepAccel[sumStep];
//if this value wil be > 0 then working before charconverter
int remainPulse[sumStep];
//this two values have total/seperate stepping structure
int equalPulse[sumStep];
int worker[sumStep];
//stepping number, using in charconverter
int stepno;
// using temporaly like for
int count;
int countA;
int i;
//how many stepping works, set in the charconverter
//worker will be setting 0 in stepmov
//terminalStep storage remain pulse  timer
//if (terminalStep < 0) then there is no working
int terminalStep;
//saving remain pulse
int steploop[2];
//setting 3stepping motors (steps, pulse, maxpulse, acc)
//using in dvacalculator

int result;

//using nuMeta
int maxPulse[2];
int minPulse[2];
int tmpWorker;

//starting tag
int proclv;

void setup() {
    Serial.begin(115200);
    for (i= 0; i < sumStep; i++) {
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
  if (Serial.available() > 0) {
    ch = Serial.read();
    charconverter();
    if (proclv == 1) {
      proclv = 0;
      initPulse();
      terminalStep = pulseTimer;
      while (terminalStep > 0) {
        nuMeta();
        stepidle();
      }
      /*
      while (sumremain() > 0) {
        nuMeta();
        terStep();
      }
      */
      newStart();
      Serial.println ("working end----------------------");
    } // if proclv end 
  } // Serial read
} // loop end

// pin ENA and STEP value to LOW (on)
void initPulse() {
  Serial.println ("iniPulse start----------------------");
  if (worker[0] == sumStep) {
    for (i = 0; i < sumStep; i++) {
      digitalWrite(ENA[i], LOW);
      digitalWrite(STEP[i], HIGH);
      Serial.print ("pin enable_");
      Serial.println (i);
    }
  } else if (worker[0] > 0) {
    for (i = 1; i <= worker[0]; i++) {
      count = worker[i];
      digitalWrite(ENA[count], LOW);
      digitalWrite(STEP[count], HIGH);
      Serial.print ("pin enable_");
      Serial.println (count);
    }// for end
  }//if end
}// proc end


void newStart() {
  for (i = 0; i < sumStep; i++) {
    equalPulse[i] = 0;
    worker[i] = 0;
  }
}

// # $ % = initiate setting stepping
// 0~7 accelation setting
// 89 setting dirextion
// using stepno, worker
void charconverter() {
    if (35 <= ch && ch <= 37) {
      switch (ch) {
        case 35:
          stepno = 0;
          Serial.println ("setting stepping 0");
          break;
        case 36:
          stepno = 1;
          Serial.println ("setting stepping 1");   
          break;
        case 37:
          stepno = 2;
          Serial.println ("setting stepping 2");          
          break;
      }
    } else if (48<= ch && ch <= 57) {
      Serial.println ("setiing accelaration");
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
          Serial.println ("setting dir high");
          break;
        case 57:
          digitalWrite(DIR[stepno], LOW);
          Serial.println ("setting dir low");
          break;
      } //end switch
    } else if (97<= ch && ch <= 122) {
      Serial.print ("setting pulse_");
      Serial.println (stepno);
    switch (ch) {
      case 97:
        stepPulse[stepno] = 800;
        remainPulse[stepno] = 800;
        break;
      case 98:
        stepPulse[stepno] = 1000;
        remainPulse[stepno] = 1000;
        break;
      case 99:
        stepPulse[stepno] = 2090;
        remainPulse[stepno] = 2090;
        break;
      default:
        break;            
     } //end switch
    } else if (65 <= ch && ch <= 90) {
      Serial.print ("Stepping on_");
      switch (ch) {
        case 65:
          activestep(0);
          Serial.println ("stepper 0 operate");
          Serial.println (worker[0]);
          Serial.println (worker[1]);
          break;
        case 66:
          activestep(1);
          Serial.println("stepper 1 operate");
          Serial.println(worker[0]);
          Serial.println(worker[1]);
          break;
        case 67:
          activestep(2);
          Serial.println("stepper 2 operate");
          Serial.println (worker[0]);
          Serial.println (worker[1]);
          break;
        case 68:
          proclv = 1;
          break;
        default:
          break;
      } // switch end
  } //end if
} // end proc

//to getting a active state stepping
//end of stepmov worker will be initiating
//complete
void activestep(int a){
  worker[0] += 1;
  if (worker[0] < sumStep) {
    count = worker[0];
    worker[count] = a;
  } else if (worker[0] >= sumStep) {
    worker[0] = 3;
  } //end if
} //end proc

//complete
void accelset() {
    if (stepPulse[stepno] >= accelLimit[stepno]) {
        stepPulse[stepno] = stepPulse[stepno] - stepAccel[stepno];
    } else {
        stepPulse[stepno] = accelLimit[stepno];
    } // if end
} //proc end


void stepidle() {
  Serial.print ("working_stepping ---------------------");
  Serial.println (minPulse[1]);
  count = minPulse[1];
  delayMicroseconds(minPulse[0]);
  if (equalPulse[0] == 3) { // #if
    for (i = 0; i < sumStep; i++) { // ## for
      digitalWrite(STEP[i], LOW);
      digitalWrite(STEP[i], HIGH);
    } // ##for end
  } else if (equalPulse[0] > 1) {
     for (i = 1; i <= equalPulse[0]; i++) { // ##for
       count = equalPulse[i];
       digitalWrite(STEP[count], LOW);
       digitalWrite(STEP[count], HIGH);
     } // ## for end
  }// #if end
  digitalWrite(STEP[count], LOW);
  //delay(3000); // add delay in here
  if (worker[0] == sumStep) { // #if 
    for (i = 0; i < sumStep; i++ ) { // ## for
      remainPulse[i] -= minPulse[0];
      if (remainPulse[i] <= 0 && terminalStep > 0) { // ###if
        remainPulse[i] = stepPulse[i];
      } //### if end
    } // ## for end
  } else if (worker[0] > 0) {
    for ( i = 1; i <= worker[0]; i++) { // ## for
      tmpWorker = worker[i];
      remainPulse[tmpWorker] -= minPulse[0];
      if (remainPulse[tmpWorker] <= 0 && terminalStep > 0) { // ###if
        remainPulse[tmpWorker] = stepPulse[tmpWorker];
      } //### if end
    } // ##for end
  }// #if end
  terminalStep -= minPulse[0];
  Serial.print ("pulse_");
  Serial.println (minPulse[0]);
  Serial.print ("remain_");
  Serial.println (terminalStep);
  digitalWrite(STEP[count], HIGH);
} // proc end


void terStep() {
  Serial.print ("working_stepping ---------------------");
  Serial.println (minPulse[1]);
  count = minPulse[1];
  delayMicroseconds(minPulse[0]);
  digitalWrite(STEP[count], LOW);
  //delay(3000); // add delay in here
  if (worker[0] == sumStep) { // #if 
    for (i = 0; i < sumStep; i++ ) { // ## for
      remainPulse[i] -= minPulse[0];
    } // ## for end
  } else if (worker[0] > 0) {
    for ( i = 1; i <= worker[0]; i++) { // ## for
      tmpWorker = worker[i];
      remainPulse[tmpWorker] -= minPulse[0];
    } // ##for end
  }// #if end
  Serial.print ("pulse_");
  Serial.println (minPulse[0]);
  Serial.print ("remain_");
  Serial.println (terminalStep);
  digitalWrite(STEP[count], HIGH);
  Serial.println ("terminal phase --------------------------");
} //proc end

void nuMeta() {
  if (worker[0] == sumStep){ //# if_ when worker[0] value has same as sumstep
    Serial.println ("start all stepping working");
    //starting stepno 0
    minPulse[0] = remainPulse[0];
    minPulse[1] = 0;
    equalPulse[0] = 1;
    equalPulse[1] = 0;    
    for ( i = 1; i < sumStep; i++) { //## for getting smaller value
      if (minPulse[0] > remainPulse[i]) {// ### if
        minPulse[0] = remainPulse[i];
        minPulse[1] = i;
      } else if (minPulse[0] == remainPulse[i]) {
        equalPulse[0] += 1;
        if (equalPulse[0] < sumStep) { // ####if
          countA = equalPulse[0];
          equalPulse[countA] = i;
        } else if (equalPulse[0] >= sumStep) {
          equalPulse[0] = sumStep;
        } //####if end
      } //### if end
    } //## for end
  } else if (worker[0] > 0) { //working when worker[0] is lower than sumstep
    count = worker[1];
    minPulse[0] = remainPulse[count];
    minPulse[1] = count;
    equalPulse[0] = 1;
    equalPulse[1] = count;
    for (i = 2; i <= worker[0]; i++) { //## for
      count = worker[i];
      if (minPulse[0] > remainPulse[count]) { //### if
        minPulse[0] = remainPulse[count];
        minPulse[1] = count;
        equalPulse[0] = 1;
        equalPulse[1] = count;
      } else if (minPulse[0] == remainPulse[count]) {
        equalPulse[0] += 1;
        if (equalPulse[0] < sumStep) { //// #### if
          countA = equalPulse[0];          
          equalPulse[countA] = count;
        } else if (equalPulse[0] >= sumStep) {
          equalPulse[0] = sumStep;
        } //#### if end
      } // ### if end
    } // ## for end
  } // #if end
} // proc end


int sumremain() { 
  count = 0;
  countA = 0;
  if (worker[0] == sumStep) { //#if
    for ( i = 0; i < sumStep; i++) { // ## for
      if (remainPulse[i] > 0) { // ### if
        count += remainPulse[i];
      } // ### if end
    } // ## for end
    Serial.print ("result________________");
    Serial.println (count);
    return count;
  } else if (worker[0] > 0) {
    for (i = 1; i < sumStep; i++) { // ## for
      countA = worker[i];
      if (remainPulse[countA] > 0) { // ### if 
       count += remainPulse[countA];
      } // ### if end
    } // ## for end
    Serial.print ("result________________");
    Serial.println (count);
    return count;
  } // #if end
} //proc end
