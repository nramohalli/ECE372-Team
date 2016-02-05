/* 
 * File:   led.c
 * Author: gvanhoy
 *
 * Created on August 27, 2015, 3:15 PM
 */

#include <xc.h>
#include "led.h"

void initLEDs() {
    //TODO: Initialize LEDs
    TRISDbits.TRISD0 = OUTPUT;
    TRISDbits.TRISD1 = OUTPUT;
    TRISDbits.TRISD2 = OUTPUT;
    
}

void turnOnLED(int led){
    
    //TODO: You may choose to write this function
    // as a matter of convenience
    if(led == 1){
        RedLED = ON; 
        YellowLED = OFF; 
        GreenLED = OFF;
    }
    else if(led == 2){ 
        RedLED = OFF; 
        YellowLED = ON; 
        GreenLED = OFF;        
    } 
    else{ 
        RedLED = OFF; 
        YellowLED = OFF; 
        GreenLED = ON; 
    }
}