#include <xc.h>
#include "PWM.h"
#include "math.h"

//#define input1 TRISDbits.TRISD1  //probs change these later 
//#define input2 TRISDbits.TRISD5
//#define input3 
//#define input4

void initPWM() {
    
    OC2CON = 0; // Turn off OC1 while doing setup.
    
    RPD1Rbits.RPD1R = 0;   // map RD1 to OC2
    RPB14Rbits.RPB14R = 0;  // map B14 to 0
    
    OC2CONbits.OCTSEL = 1;      // Uses Timer3
    OC2RS = 0; // Initialize secondary Compare Register
    OC2R = 0; // Initialize primary Compare Register
    OC2CONbits.OCM = 6;     // PWM Fault Pin Disabled
    OC2CONbits.ON = 1;      // Output Compare Enabled
    
    //==========================================================
    
    OC4CON = 0; // Turn off OC1 while doing setup.
    
    RPD3Rbits.RPD3R = 0;   // map RD0 to OC4
    RPF0Rbits.RPF0R = 0;    // map RF0 to 0
    
    OC4CONbits.OCTSEL = 1;      // Uses Timer3
    OC4RS = 0; // Initialize secondary Compare Register
    OC4R = 0; // Initialize primary Compare Register
    OC4CONbits.OCM = 6;     // PWM Fault Pin Disabled
    OC4CONbits.ON = 1;      // Output Compare Enabled
    
    
}

void printVoltage(int adcVal){
    
    int voltage;
    int v1;
    int v2;
    int v3;
    int v4;
    char str[6];
    
    voltage = adcVal * 5 / 1024;
    v1 = floor(    voltage);
    v2 = floor(   (voltage *   10) % 10  );
    v3 = floor(  ((voltage *  100) % 100 ) % 10  );
    v4 = floor( (((voltage * 1000) % 1000) % 100) % 10 );
            
    sprintf(str,"%d.%d%d%d", v1, v2, v3, v4);
    clearLCD();
    printStringLCD(str);
    
}

void setLeftWheelSpeed(int val) {
    OC2RS = val;
}
void setLeftForward(int true) {
    if (true == 1) { //set forward
        RPD1Rbits.RPD1R = 0;     // map RP1 to OC2
        RPB14Rbits.RPB14R = 11;  // map B14 to 0
    }
    else {
        RPD1Rbits.RPD1R = 11;     // map RP1 to OC2
        RPB14Rbits.RPB14R = 0;  // map B14 to 0
    }
}
void setRightWheelSpeed(int val){
    OC4RS = val;
}
void setRightForward(int true) {
    if (true == 1) { //set forward
        RPD3Rbits.RPD3R = 0;     // map RD0 to OC4
        RPF0Rbits.RPF0R = 11;    // map RF0 to 0
    }
    else {
        RPD3Rbits.RPD3R = 11;     // map RD0 to OC4
        RPF0Rbits.RPF0R = 0;    // map RF0 to 0
    }
}

