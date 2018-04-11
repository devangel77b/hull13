# hull13
### D Evangelista

This is the mbed / nucleo code for USNA Sailbot Hull 13 mod 2, part of the USNA Sailbot Program. It is being developed for ES401/404 (Systems Engineering Capstone). 


## Rudder
The rudder consists of a balanced design NACA foil. The rudder stock passes through a tube penetrating the whole hull. On the topside, there is a 1:1 linkage to a Hitec HS5646WP servo installed in a slot cut into the deck. The gap between the servo and hull is sealed with RTV and forms part of the watertight boundary (sic). 

The rudder code here defines a `Rudder` class. The default class constructor is called by specifying the pin to which the rudder PWM line is connected.  There are two methods of interest, `void Rudder.write(float deg)` and `float Rudder.read()`.

## Main sail
The main sail is a Miller-Williamson type wing sail. It is actuated by a Hitec D845WP servo via a 1:1 linkage. The servo is installed in a slot cut into the deck in a manner similar to the rudder servo. The main sail code here works similarly to the rudder code. 

## Running tests
The `TESTS` directory contains test cases for unit testing, acceptance and dockside testing, integrated system tests, etc. To run these tests, rename or move the `main.cpp` file temporarily. Then continue as follows. 
```
mbed test --compile-list
mbed test --compile -n tests-rudder-range
mbed test --compile -n tests-rudder-calibration_check
```

## Acknowledgements
The original Hull 13 was designed by Prof Paul Miller and USNA NAOE midshipmen in EN447/448 in 2017. The original Hull 13 control sysem was done by Mr. Matt Hamlet. MIDN 1/c Lackey, Stoermer, and Zhou updated the design in 2018. 
