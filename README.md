
# green controller

stepping setting table

# asccii

//43.44.45 = + , - , setting accelation

//35.36 = # $ , setting direction 

// A ~ = 65 ~

// 1 ~ = 48 ~

// a ~ = 97 ~

# nema1.7 stepper 3.7:1 gear ratio ( a - b- c- d)

minimun step = 2

360step = almost 180'

idle pulse = 800 microsecond

speed range = 380 to 950

need to step to reach from 380 to 950 = 1100step

 * important dont setting delays after LOW signals on step (just when using planetary geared stepping motor

# nema1.7 stepper 1:1 gear ratio ( a - c - b - d)

(b - a1, g -b1, y - a2, r - 2b)

minimun step = 2

110step = almost 180'

idle pulse = under 4000 microsecond

speed range = 470 to unlimited


# MG995 servo ( orange - analog, red - 5v, brown - ground)

working every 20mili seconds

working between 900 micros (0 deg) and 2100 micros (180 deg) 

operation voltage : 3.5- 8.4

// 0 ~ 9 setting acc value



// need to setting velosity = a~ t
// uvwxyz
// stepmoving devide into total 3parts
// uvw : starting phase (pinenable, set initspeed 2000, 1500, 1000, s.accelaration 1; 3; 5;))
// xyz : terminal phase (pindisable, set endaccelation 5, 3, 2)
// stepper action must end in 0.1secons
// serialaction - autoaction - serialaction

Serial.read ; uvw
pinenable, set initial speed, set accelration
atfter getting last speed value
set initail speed, set random acceleration(port3)

when working proc2, another 


# Serial writing latency

* 1byte data (eg. char) = 0.0125 ~ 0.0111 second

* integer data = 1.12 ~ 1.2 second (Serial.parseInt)

# structure

ard.write - average sleep(time - stime), serial.read
 
ard.write(2byte) - proc - serial.read - ard.write(byte)

calculating average inteval times between two ard.write times

between writing times, must receiving ard.read()

# plan

to install potentiometer on neck position and install gy-91 in top of the head

ordering potentiometer

to calculating idle status values

gy91 will installing center position of frame

python will getting every potentiometer value and alwways makes frame to idle status

1. dueboard will controlling two legs occupy 9digital pins)

2. another due board will getting all information about values from sensors( 8analog pins for 4 gy-91 modules)

3. us sensors will be installing ribon

4. need two camera module and transmitter(must checking atmosphere)


# ordering

1. potientiometer

2. jumping cables

3. bearing pins

4. frame
