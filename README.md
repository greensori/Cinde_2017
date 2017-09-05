# stepping controller

stepping motor control setting

stepping setting table

# nema1.7 stepper 3.7:1 gear ratio ( a - b- c- d)

minimun step = 2

360step = almost 180'

idle pulse = 800 microsecond

speed range = 380 to 950

need to step to reach from 380 to 950 = 1100step

 * important dont setting delays after LOW signals on step (just when using planetary geared stepping motor

# nema1.7 stepper 1:1 gear ratio ( a - c - b - d)

minimun step = 2

110step = almost 180'

idle pulse = under 4000 microsecond

speed range = 470 to unlimited


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
