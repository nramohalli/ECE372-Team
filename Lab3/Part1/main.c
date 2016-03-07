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
   WAIT4PRESS, WAIT, WAIT4RELEASE, COL0, COL1, COL2
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
    
    SYSTEMConfigPerformance(10000000);
    
    while(1){
        
        switch(state){
            case WAIT4PRESS:
                //INTERRUPT_E_PINS = _ON;
                delayUs(1000);
                KEYPAD_LAT_COL0 = ODC_CLOSED;
                KEYPAD_LAT_COL1 = ODC_CLOSED;
                KEYPAD_LAT_COL2 = ODC_CLOSED;
                break;
                
            case WAIT:
                KEYPAD_LAT_COL0 = ODC_OPEN;
                KEYPAD_LAT_COL1 = ODC_OPEN;
                KEYPAD_LAT_COL2 = ODC_OPEN;
                state = COL0;
                break;
                
            case WAIT4RELEASE:
                INTERRUPT_E_PINS = _ON;
                break;
                
            case COL0:
                KEYPAD_LAT_COL1 = ODC_OPEN;
                KEYPAD_LAT_COL2 = ODC_OPEN;
                KEYPAD_LAT_COL0 = ODC_CLOSED;
                delayUs(1000);
                //********************************
                returnedKey = scanKeypad(0);
                if (returnedKey != '!'){
                delayUs(1000);
                    printCharLCD(returnedKey);
                    delayUs(1000);
                    c = c + 1;
                    if (c != 16) moveCursorLCD(1,0);
                    else if (c == 16 && r == 0) {
                        c = 0;
                        r = 2;
                        moveCursorLCD(0,r);
                    }
                    else if (c == 16 && r == 2) {
                        c = 0;
                        r = 0;
                        moveCursorLCD(0,r);
                    }
                    state = WAIT4RELEASE;
                }
                else state = COL1;
                break;
                
            case COL1:
                KEYPAD_LAT_COL0 = ODC_OPEN;
                KEYPAD_LAT_COL2 = ODC_OPEN;
                KEYPAD_LAT_COL1 = ODC_CLOSED;
                delayUs(1000);
                //********************************
                returnedKey = scanKeypad(1);
                if (returnedKey != '!'){
                delayUs(1000);
                    printCharLCD(returnedKey);
                    delayUs(1000);
                    c = c + 1;
                    if (c != 16) moveCursorLCD(1,0);
                    else if (c == 16 && r == 0) {
                        c = 0;
                        r = 2;
                        moveCursorLCD(0,r);
                    }
                    else if (c == 16 && r == 2) {
                        c = 0;
                        r = 0;
                        moveCursorLCD(0,r);
                    }
                    state = WAIT4RELEASE;
                }
                else state = COL2;
                break;
                
            case COL2:
                KEYPAD_LAT_COL0 = ODC_OPEN;
                KEYPAD_LAT_COL1 = ODC_OPEN;
                KEYPAD_LAT_COL2 = ODC_CLOSED;
                delayUs(1000);
                //********************************
                returnedKey = scanKeypad(2);
                if (returnedKey != '!'){
                delayUs(1000);
                    printCharLCD(returnedKey);
                    delayUs(1000);
                    c = c + 1;
                    if (c != 16) moveCursorLCD(1,0);
                    else if (c == 16 && r == 0) {
                        c = 0;
                        r = 2;
                        moveCursorLCD(0,r);
                    }
                    else if (c == 16 && r == 2) {
                        c = 0;
                        r = 0;
                        moveCursorLCD(0,r);
                    }
                    state = WAIT4RELEASE;
                }
                //********************************
                state = WAIT4RELEASE;
                break;
        }
        
    }
    
    return 0;
}


//interrupt to go to init state ( reset the system )
void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterupt(){
    
	INTERRUPT_E_FLAG = DOWN;
    int i = 0;
    
	if (state == WAIT4RELEASE){ ; }
	if (state == WAIT4RELEASE){ ; }
	if (state == WAIT4RELEASE){ ; }
	if (state == WAIT4RELEASE){ ; }
}