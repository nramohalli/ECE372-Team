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


#define SW_PORT PORTDbits.RD6
#define SW_TRIS TRISDbits.TRISD6
#define LT 0 //defining line threshold as 0 since that is the sensor input 

//TODO: Define states of the state machine
typedef enum stateTypeEnum{
    IDLE_1, D_IDLE_1,RIGHT, D_RIGHT, LEFT, D_LEFT,  
            FORWARD, D_FORWARD,TURN_AROUND
} stateType;

volatile int front_in = 1000;
volatile int right_in = 1000;
volatile int left_in = 1000;
volatile int back_in = 1000;
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
    
    initADC1();
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
           
            case IDLE_1:
                setLeftForward(1);
                setRightForward(1);
                setLeftWheelSpeed(0);
                setRightWheelSpeed(0);
                
                state=D_IDLE_1;
                break;
                
           case D_IDLE_1:
               delayUs(100);
               if(front_in==LT) state=FORWARD;
               else if(right_in==LT && left_in!=LT)state=RIGHT;
               else if(left_in==LT && right_in!=LT) state=LEFT;
               else if(back_in==LT && front_in!=LT && right_in!=LT && left_in!=LT)
               {state=TURN_AROUND;  }
               else state=IDLE_1;
                break;
               
           case FORWARD:
               forward();
               state=D_FORWARD;
               break;
               
           case D_FORWARD:
               delayUs(100);
               state=FORWARD;
               break;
               
           case RIGHT:
               right_turn();
               state=D_RIGHT;
               break;
               
           case D_RIGHT:
                delayUs(100);
               state=RIGHT;
               break;
               
           case LEFT:
               left_turn();
               state=D_LEFT;
               break;
               
           case D_LEFT:
               delayUs(100);
               state=LEFT;
               break;
               
           case TURN_AROUND:
               IFS1bits.CNDIF = 1;
               break;
              
        }
    }
    return 0;
}

void __ISR(_ADC_VECTOR, IPL6SRS) _ADCInterrupt(){
   IFS0bits.AD1IF = 0; //flag down
   AD1CON1bits.SAMP = 0;
   front_in = ADC1BUF0;
   right_in=; //need you to figure out which ADCs these correspond too
   left_in=;
   back_in=;
   state=D_IDLE_1;
  }
 
 
void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt(){
    IFS1bits.CNDIF = 0;

    while(front_in!=LT)
    {
        right_turn();
    }
    state=IDLE_1;
}


