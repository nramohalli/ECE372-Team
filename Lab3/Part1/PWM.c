#include <xc.h>
#include "PWM.h"

void initPWM() {
    
     RPD1Rbits.RPD1R = 0b1011; // map OC2 to RD1
    OC2CON = 0x0000; // Turn off OC1 while doing setup.
    OC2R = 0x0000; // Initialize primary Compare Register
    OC2RS = 0x0000; // Initialize secondary Compare Register
    OC2CON = 0x0006; // Configure for PWM mode
    OC2CONSET = 0x8000; // Enable OC1
}

void HBridge() {
    input1 = 0; // use as speed
    input2 = 0; // use as direction
    input3 = 0; // unassigned
    input4 = 0; // unassigned
}

void setMotorSpeed() {
    OC2 = input1; // need to change OC2 to assign data the correct register
}

void setMotorDirection() {
    OC4 = input1; // need to change OC2 to assign data the correct register
}