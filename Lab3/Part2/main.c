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
#include "keypad.h"
#include "ADC.h"
#include "PWM.h"

//TODO: Define states of the state machine
typedef enum stateTypeEnum{
    INIT_IDLE, DE_IDLE, FORWARD, DE_FORWARD, IDLE_2, DE_IDLE_2, BACKWARD, DE_BACKWARD
} stateType;

volatile stateType state=INIT_IDLE;
//volatile char key=-1;
volatile int j=0;
volatile int check=0;
volatile int col=3;
volatile char returnedKey = -1;

// 3/2/16- so far column 1 works I think there is a code problem that doesn't let the other two columns go low when button pressed
//switch interrupts from triggering on row changes to triggering on column changes since that is what we are scanning
// ******************************************************************************************* //

int main(void)
{
    int i = 0;
    int c = 0;
    int r = 0;
    
    enableInterrupts();                   //This function is necessary to use interrupts.
    initTimer1();
    initLCD();
    initPWM();
    initADC();
    
    SYSTEMConfigPerformance(10000000);
    
    while(1){
        
        switch(state){
            case INIT_IDLE:
                break;
                
            case DE_IDLE:
                state = FORWARD;
                break;
                
            case FORWARD:
                break;
                
            case DE_FORWARD:
                state = IDLE_2;
                break;
                    
            case IDLE_2:
                break;
                
            case DE_IDLE_2:
                state = BACKWARD;
                break;
                
            case BACKWARD:
                break;
                
            case DE_BACKWARD:
                state = INIT_IDLE;
                break;
        }
    }
    return 0;
}


//interrupt to go to init state ( reset the system )
void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterupt(){
    //need swicth interrupt flag down
	//INTERRUPT_E_FLAG = DOWN;
    
	if (state == INIT_IDLE) state = DE_IDLE;
	else if (state == FORWARD) state = DE_FORWARD;
	else if (state == IDLE_2) state = DE_IDLE_2;
	else if (state == BACKWARD) state = DE_BACKWARD;
}