# totalstepper
stepper motor control examples

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
