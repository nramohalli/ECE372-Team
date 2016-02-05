/* 
 * File:   main.c
 * Author: gvanhoy
 * Description: lab 0.
 * Created on August 27, 2015, 10:14 AM
 */

#include <xc.h>
#include <sys/attribs.h>
#include "timer.h"
#include "led.h"
#include "interrupt.h"
#include "config.h"
#include "switch.h"

#define OUTPUT 0
#define INPUT 1

//TODO: Define states of the state machine
typedef enum stateTypeEnum{
    REDLED, WAITRED, YELLOWLED, WAITYELLOW, GREENLED, WAITGREEN
} stateType;

//TODO: Use volatile variables that change within interrupts
volatile stateType state = REDLED;

int main() {
    SYSTEMConfigPerformance(10000000);    //Configures low-level system parameters for 10 MHz clock
    enableInterrupts();                   //This function is necessary to use interrupts.

    //TODO: Write each initialization function
    initLEDs();
    initTimer1();
    initSwitch();
    
    while(1){
        //TODO: Implement a state machine to create the desired functionality
        switch (state) {
            case REDLED:
                state = WAITRED;
                turnOnLED(1);
                break;
            case WAITRED:
                break;
            case YELLOWLED:
                state = WAITYELLOW;
                turnOnLED(2);
                break;
            case WAITYELLOW:
                break;
            case GREENLED:
                state = WAITGREEN;
                turnOnLED(3);
                break;
            case WAITGREEN:
                break;
        }
    }
    
    return 0;
}

//TODO: Add interrupt service routines that manage the change of states
//for particular events as needed
//void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterupt(){
//    int dummyVariable = PORTD;
    
//    IFS1bits.CNDIF = 0; 
//    if(state == WAITRED) state = YELLOWLED;
//    else if(state == WAITYELLOW) state = GREENLED;
//    else if(state == WAITGREEN) state = REDLED;
//}

void __ISR(_TIMER_1_VECTOR, IPL7SRS) _T1Interupt() { 
    TIMERFLAG = 0; 
    
    if(state == WAITRED) state = YELLOWLED;
    else if(state == WAITYELLOW) state = GREENLED;
    else if(state == WAITGREEN) state = REDLED;
}

