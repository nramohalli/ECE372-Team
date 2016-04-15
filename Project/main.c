// ******************************************************************************************* //
//
// File:         lab3p1.c
// Date:         3-7-2016
// Authors:      Team 213
//
// Description: 
// ******************************************************************************************* //

#include <xc.h>
#include <sys/attribs.h>
#include "lcd.h"
#include "timer.h"
#include "config.h"
#include "interrupt.h"
#include "string.h"
#include "ADC.h"
#include "PWM.h"
#include "keypad.h"

#define SW_PORT PORTDbits.RD6
#define SW_TRIS TRISDbits.TRISD6

//TODO: Define states of the state machine
typedef enum stateTypeEnum{
    IDLE_1, D_IDLE_1, TURN_RIGHT, TURN_LEFT, BACKWARD, D_BACKWARD, FORWARD, D_FORWARD,
} stateType;

void setWheelSpeed(int LeftWheel, int RightWheel);

volatile int irVoltage = 0;
volatile stateType state;
// ******************************************************************************************* //

int main(void) {
    SYSTEMConfigPerformance(10000000);
    enableInterrupts(); //This function is necessary to use interrupts.
    
    initTimer2();
    initTimer3();
    switch1();
    initPWM();
    initADC();
    initLCD();
    
    state = IDLE_1;
    
    volatile float printbuffer = 0; //maybe change to float
   // double voltPOT = 0;
    int irLeftVoltage = 0;
    int irRightVoltage = 0;
    int toleracne = 200;
    char str[16];
    
    
    while(1){
       switch(state){
            case IDLE_1:
                clearLCD();
                snprintf(str, sizeof(str), "Button to Start");
                printStringLCD(str);
                moveCursorLCD(0,0);
                setLeftForward(1);
                setRightForward(1);
                setLeftWheelSpeed(0);
                setRightWheelSpeed(0);
                break;
            case D_IDLE_1:
                clearLCD();
                delayUs(100);
                state = FORWARD;
                break;
            case FORWARD:
                setWheelSpeed(750,750);
                scanLeftIRVoltage();
                irLeftVoltage = irVoltage;
                scanRightIRVoltage();
                irRightVoltage = irVoltage;
                if (irLeftVoltage > toleracne) {
                    state = TURN_LEFT;
                }
                else if (irRightVoltage > toleracne) {
                    state = TURN_RIGHT;
                }
                break;
            case TURN_LEFT:
                setLeftWheelSpeed(0);
                scanLeftIRVoltage();
                irLeftVoltage = irVoltage;
                if (irLeftVoltage < toleracne) {
                    state = FORWARD;
                }
                break;
            case TURN_RIGHT:
                setRightWheelSpeed(0);
                scanRightIRVoltage();
                irRightVoltage = irVoltage;
                if (irRightVoltage < toleracne) {
                    state = FORWARD;
                }
                break;
        }
    }
    return 0;
}

void __ISR(_ADC_VECTOR, IPL7SRS) _ADCInterrupt(){
   IFS0bits.AD1IF = 0; //flag down
   AD1CON1bits.SAMP = 0;
   irVoltage = ADC1BUF0;
}
 
 
void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt(){
    IFS1bits.CNDIF = 0;

    if(SW_PORT == RELEASED){
       if(state == IDLE_1) {
           state = D_IDLE_1;
       }
       else if(state == FORWARD) {
           state = D_FORWARD;
       }
       else if(state == BACKWARD) {
           state = D_BACKWARD;
       }
    }
}

void setWheelSpeed(int LeftWheel, int RightWheel) {
    setLeftWheelSpeed(LeftWheel);
    setRightWheelSpeed(RightWheel);
}
