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
    IDLE_1, D_IDLE_1, IDLE_2, D_IDLE_2, BACKWARD, D_BACKWARD, FORWARD, D_FORWARD,
} stateType;

volatile int potVoltage = 0;
volatile stateType state;
volatile float voltage;
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
    char str[16];
    
    while(1){
//           clearLCD();
//           snprintf(str, sizeof(str), "%0.2f", (float)potVoltage/1023.0*5.0);
//           printStringLCD(str);
//           moveCursorLCD(0,0);
       switch(state){
           voltage = potVoltage*1.0;
            case IDLE_1:
                setLeftForward(1);
                setRightForward(1);
                setLeftWheelSpeed(0);
                setRightWheelSpeed(0);
                break;
           case D_IDLE_1:
                delayUs(100);
                state = FORWARD;
                break;
            case FORWARD:
                CalculatedSpeed();
                AD1CON1bits.SAMP = 1;
                break;
            case D_FORWARD:
                delayUs(100);
                state = IDLE_2;
                break;
            case IDLE_2:
                setLeftWheelSpeed(0);
                setRightWheelSpeed(0);
                break;
            case D_IDLE_2:
                delayUs(100);
                state = BACKWARD;
                break;
            case BACKWARD:
                setLeftForward(0);
                setRightForward(0);
                CalculatedSpeed();
                AD1CON1bits.SAMP = 1;
                break; 
            case D_BACKWARD:
                delayUs(100);
                state = IDLE_1;
                break;
        }
    }
    return 0;
}

void __ISR(_ADC_VECTOR, IPL7SRS) _ADCInterrupt(){
   IFS0bits.AD1IF = 0; //flag down
   AD1CON1bits.SAMP = 0;
   potVoltage = ADC1BUF0;
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
       else if(state == IDLE_2) {
           state = D_IDLE_2;
       }
       else if(state == BACKWARD) {
           state = D_BACKWARD;
       }
    }
}

void CalculatedSpeed() {
    if(potVoltage > 512){
       setLeftWheelSpeed(1023);
       setRightWheelSpeed(2048 - potVoltage * 2);
   }
   else if (potVoltage == 512){
       setLeftWheelSpeed(1023);
       setRightWheelSpeed(1023);
   }
   else{
       setLeftWheelSpeed(potVoltage * 2);
       setRightWheelSpeed(1023);
   }
}
