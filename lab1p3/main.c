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
#include "led.h"

//TODO: Define states of the state machine
typedef enum stateTypeEnum{
    INIT, DEINIT, WAIT, DEWAIT, LCDRUN, COUNT, DECOUNT, LCDSTOP
} stateType;


// ******************************************************************************************* //

int main(void)
{
    enableInterrupts();                   //This function is necessary to use interrupts.

    //TODO: Write each initialization function
    initLEDs();
    initTimer2();
    
    //init state var
    stateType state = INIT;
    
    SYSTEMConfigPerformance(10000000);
    while(1)
    {
        //fsm
        switch(state){
            case INIT:
                state = DEINIT;
                break;
            case DEINIT:
                
                //wait x amount of time
                
                state = WAIT;
                break;
            case WAIT:
                LEDRUN = OFF;
                LEDSTOP = ON;
                LCDMESS = LCDSTOPPED;
                state = DEWAIT;
                break;
            case DEWAIT:
                
                //wait x amount of time
                
                state = LCDRUN;
                break;
            case LCDRUN:
                LEDRUN = ON;
                LEDSTOP = OFF;
                LCDMESS = LCDRUNNING;
                state = COUNT;
                break;
            case COUNT:
                break;
            case DECOUNT:
                
                //wait x amount of time
                
                state = LCDSTOP;
                break;
            case LCDSTOP:
                LEDRUN = OFF;
                LEDSTOP = ON;
                LCDMESS = LCDSTOPPED;
                state = WAIT;
                break;       
        }           
    }
    
    return 0;
}


//interrupt to go to init state ( reset the system )
void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterupt(){
    int dummyVariable = PORTD;
    
    IFS1bits.CNDIF = 0; 
    
    if(state == WAIT) state = DEWAIT;
    else if(state == COUNT) state = DECOUNT;
}