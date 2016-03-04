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
    INIT, ENCOL1, ENCOL2, ENCOL3, DEBOUNCE, PRESS
} stateType;

volatile int state;
volatile char key;
volatile int j=0;
volatile int i=0;

// 3/2/16- so far column 1 works I think there is a code problem that doesn't let the other two columns go low when button pressed
//switch interrupts from triggering on row changes to triggering on column changes since that is what we are scanning
// ******************************************************************************************* //

int main(void)
{
    enableInterrupts();                   //This function is necessary to use interrupts.
    initTimer2();
    initLCD();
    initKeypad();
    
    SYSTEMConfigPerformance(10000000);
    
    while(1)
    {
       
        
        //enable each column, keep looping until until a key is pressed
        switch(state){
            case 1: 
                KEYPAD_LAT_COL0 = KON;  // If this was E pin...it might have triggered E CN
                KEYPAD_LAT_COL1 = KOFF;
                KEYPAD_LAT_COL2 = KOFF;
                delayUs(1);
                state=2;
                break;
                
            case 2:
                 KEYPAD_LAT_COL0 = KOFF;
                 KEYPAD_LAT_COL1 = KON;
                 KEYPAD_LAT_COL2 = KOFF;  
                 delayUs(1);
                 state=3;
                 break;
                 
            case 3:
                 KEYPAD_LAT_COL0 = KOFF;
                 KEYPAD_LAT_COL1 = KOFF;
                 KEYPAD_LAT_COL2 = KON;
                 delayUs(1);
                 state=1;
                 break;
        }
    
       
   // 
        
   
        
   // 
    
   
    
   // delayUs(10);
    }
        
    
    return 0;
}


//interrupt to go to init state ( reset the system )
void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterupt(){
    
    
    
     key = scanKeypad();
      //delayUs(10);
      if(KEYPAD_PORT_ROW0==1 || KEYPAD_PORT_ROW1==1 || KEYPAD_PORT_ROW2==1 || KEYPAD_PORT_ROW3==1)
      {
         printCharLCD('c');
      }
    
     if(state==1) state=2;
     if(state==2) state=3;
     if(state==3) state=1;
INTERRUPT_E_FLAG = DOWN;
    
}