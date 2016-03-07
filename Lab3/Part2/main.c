// ******************************************************************************************* //
//
// File:         lab1p2.c
// Date:         12-30-2014
// Authors:      Garrett Vanhoy
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

//TODO: Define states of the state machine
typedef enum stateTypeEnum{
	IDLE_B, D_IDLE_B, FORWARD, D_FORWARD, IDLE_F, D_IDLE_F, BACKWARD, D_BACKWORD, 
} stateType;

volatile stateType state=WAIT4PRESS;
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
	initSW();
	initADC();
	initPDM();
    
    SYSTEMConfigPerformance(10000000);
    
    while(1){
        
        switch(state){
			case IDLE_B:
                break;
                
			case D_IDLE_B:
				break;
                
			case FORWARD:
				break;
                
			case D_FORWARD:
				break;
                
			case IDLE_F:
				break;

			case D_IDLE_F:
				break;

			case BACKWARD:
				break;

			case D_BACKWORD:
				break;
        }
        
    }
    
    return 0;
}


//interrupt to go to init state ( reset the system )
void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterupt(){
    //need the switch interupt
	//INTERRUPT_E_FLAG = DOWN;

	if (state == IDLE_B) { state == D_IDLE_B; }
	else if (state == FORWARD) { state == D_FORWARD; }
	else if (state == IDLE_F) { state == D_IDLE_F; }
	else if (state == BACKWORD) { state == D_BACKWORD; }
}