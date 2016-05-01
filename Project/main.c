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
    IDLE, D_IDLE, FORWARD, ON_LINE, OFF_LINE_CORRECTION, TURN_RIGHT, TURN_LEFT, WAIT_FOR_MIDDLE, BACKWARD,
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
    
    state = IDLE;
    
    int irMiddleVoltage = 0;
    int irLeftVoltage = 0;
    int irRightVoltage = 0;
    int irBackVoltage = 0;
    int toleranceMid = 100;
    int toleranceLeft = 450;
    int toleranceRight = 95;
    int LeftSawLast = 0;
    
    char str[16];
    int upperSpeed = 900;
    int lowerSpeed = 0;
    
    void setLeftSawLast() {
        scanLeftIRVoltage();
        irLeftVoltage = irVoltage;
        scanRightIRVoltage();
        irRightVoltage = irVoltage;
        if (irRightVoltage > toleranceRight) {
           LeftSawLast = 0;
        }
        else if (irLeftVoltage > toleranceLeft) {
            LeftSawLast = 1;
        }
    }
    
    while(1){
        switch(state){
            case IDLE:
                clearLCD();
                snprintf(str, sizeof(str), "Button to Start");
                printStringLCD(str);
                moveCursorLCD(0,0);
                setLeftForward(1);
                setRightForward(1);
                setLeftWheelSpeed(0);
                setRightWheelSpeed(0);
                break;
            case D_IDLE:
                clearLCD();
                delayUs(100);
                state = FORWARD;
                break;
            case FORWARD: // middle sensor is on black line
                setWheelSpeed(upperSpeed,upperSpeed);
                state = ON_LINE;
                break;
            case ON_LINE:
                scanMiddleIRVoltage();
                irMiddleVoltage = irVoltage;
                scanLeftIRVoltage();
                irLeftVoltage = irVoltage;
                scanRightIRVoltage();
                irRightVoltage = irVoltage;
                
                if (irMiddleVoltage < toleranceMid) { 
                    state = TURN_LEFT;
                }
                if (irRightVoltage > toleranceRight) {
                    state = TURN_RIGHT;
                }
                if (irLeftVoltage > toleranceLeft) {
                    state = TURN_LEFT;
                }
                if (irRightVoltage > toleranceRight && irLeftVoltage > toleranceLeft &&
                        irMiddleVoltage > toleranceMid) {
                    state = TURN_LEFT;
                }
                break;
            case OFF_LINE_CORRECTION: // middle sensor is off black line and looking for direction to correct
                setWheelSpeed(upperSpeed,upperSpeed*3/4);
                scanLeftIRVoltage();
                irLeftVoltage = irVoltage;
                scanRightIRVoltage();
                irRightVoltage = irVoltage;
                if (irRightVoltage > toleranceRight) {
                    state = TURN_RIGHT;
                }
                else if (irLeftVoltage > toleranceLeft) {
                    state = TURN_LEFT;
                }
                break;
            case TURN_LEFT: // left sensor on black line
                setWheelSpeed(upperSpeed,lowerSpeed);
                state = WAIT_FOR_MIDDLE;
                break;
            case TURN_RIGHT: // right sensor on black line
                setWheelSpeed(lowerSpeed,upperSpeed);
                state = WAIT_FOR_MIDDLE;
                break;
            case WAIT_FOR_MIDDLE:
                scanMiddleIRVoltage();
                irMiddleVoltage = irVoltage;
                if (irMiddleVoltage > toleranceMid) {
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
       if(state == IDLE) {
           state = D_IDLE;
       }
       else {
           state == IDLE;
       }
    }
}

void setWheelSpeed(int LeftWheel, int RightWheel) {
    setLeftWheelSpeed(LeftWheel);
    setRightWheelSpeed(RightWheel);
}

