//******************************************************************************************* //
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
#include "led.h"

#define DELAY_TIME 100

//TODO: Define states of the state machine
typedef enum stateTypeEnum{
    
} stateType;


// ******************************************************************************************* //

int main(void)
{
    enableInterrupts();                   //This function is necessary to use interrupts.

	initLEDs();
	initTimer1();
	initTimer2();
	initSW();
	initLCD();
    
    //init state var
    stateType state = INIT;
    
    SYSTEMConfigPerformance(10000000);
    while(1)
    {      }
    
    return 0;
}


//interrupt to go to init state ( reset the system )
void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterupt(){
    int dummyVariable = PORTD;
    
    IFS1bits.CNDIF = 0; 
    
// debounce
    delayUs(DELAY_TIME);
// add letter to lcd
}
    
    