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
   WAIT4PRESS, WAIT, WAIT4RELEASE, COL0, COL1, COL2, ENTER, ENTER_ENTRY, SETMODE, SETMODE_ENTRY, GOOD, BAD, VALID, INVALID
} stateType;

volatile stateType state=ENTER;
//volatile char key=-1;
volatile int j=0;
volatile int check=0;
volatile int col=3;
volatile char returnedKey = -1;
volatile int set_mode = 0;

// 3/2/16- so far column 1 works I think there is a code problem that doesn't let the other two columns go low when button pressed
//switch interrupts from triggering on row changes to triggering on column changes since that is what we are scanning
// ******************************************************************************************* //

int main(void)
{
    
    int i = 0;
    int c = 0;
    int r = 0;
    
    char pass1[5] = "0000";
    char pass2[5] = "0000";
    char pass3[5] = "0000";
    char pass4[5] = "0000";
    char passEntry[5] = "";
    
    enableInterrupts();                   //This function is necessary to use interrupts.
    initTimer2();
    initLCD();
    initKeypad();
    
    SYSTEMConfigPerformance(10000000);
    
    while(1){
        
        switch(state){
            case WAIT4PRESS:
                //INTERRUPT_E_PINS = _ON;
                delayUs(1000);
                KEYPAD_LAT_COL0 = ODC_CLOSED;
                KEYPAD_LAT_COL1 = ODC_CLOSED;
                KEYPAD_LAT_COL2 = ODC_CLOSED;
                if ((i == 4) && (set_mode == 0)){
                    if (!(strcmp(passEntry, pass1)) || !(strcmp(passEntry, pass2)) || !(strcmp(passEntry, pass3)) || !(strcmp(passEntry, pass4))){
                        state = GOOD; 
                    }
                    else{
                        state = BAD;
                    }
                }
                else if ((i == 4) && (set_mode == 1)){
                    j = 0;
                    for(j=0;j<4;j++){
                        if ((passEntry[j] == '*') || (passEntry[j] == '#')){
                            state = INVALID;
                            break;
                        }
                        else{
                            state = VALID;
                        }
                    }
                }
                else if ((i == 2) && (set_mode == 0)){
                    if ((passEntry[0] == '*') && (passEntry[1] == '*')){
                        i = 0;
                        set_mode = 1;
                        state = SETMODE;
                    }
                }
                if (i == 4) i = 0;
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
                    //printCharLCD(returnedKey);
                    //moveCursorLCD(1,0);
                    if (i > 3) i = 0;
                    passEntry[i] = returnedKey;
                    i = i + 1;
                    delayUs(1000);
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
                    //printCharLCD(returnedKey);
                    //moveCursorLCD(1,0);
                    if (i > 3) i = 0;
                    passEntry[i] = returnedKey;
                    i = i + 1;
                    delayUs(1000);
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
                    //printCharLCD(returnedKey);
                    //moveCursorLCD(1,0);
                    if (i > 3) i = 0;
                    passEntry[i] = returnedKey;
                    i = i + 1;
                    delayUs(1000);
                    state = WAIT4RELEASE;
                }
                //********************************
                state = WAIT4RELEASE;
                break;
                
            //************PART2************************************************
            case ENTER:
                printStringLCD("Enter");
                state = WAIT4PRESS;
                break;

            case SETMODE:
                clearLCD();
                delayUs(1000);
                printStringLCD("Set Mode");
                state = WAIT4PRESS;
                break;
            case SETMODE_ENTRY:
                break;
            case GOOD:
                clearLCD();
                printStringLCD("Good");
                j = 0;
                for(j=0;j<1000;j++) delayUs(1000);
                clearLCD();
                set_mode = 0;
                state = ENTER;
                break;
                
            case BAD:
                clearLCD();
                printStringLCD("Bad");
                j = 0;
                for(j=0;j<1000;j++) delayUs(1000);
                clearLCD();
                set_mode = 0;
                state = ENTER;
                break;
                
            case VALID:
                clearLCD();
                printStringLCD("Valid");
                j = 0;
                for(j=0;j<1000;j++) delayUs(1000);
                clearLCD();
                j = 0;
                if (c == 4) c = 0;
                c = c + 1;

                if (c == 1) strcpy(pass1,passEntry);
                if (c == 2) strcpy(pass2,passEntry);
                if (c == 3) strcpy(pass3,passEntry);
                if (c == 4) strcpy(pass4,passEntry);
                    
                set_mode = 0;
                state = ENTER;
                break;
                
            case INVALID:
                clearLCD();
                printStringLCD("Invalid");
                j = 0;
                for(j=0;j<1000;j++) delayUs(1000);
                clearLCD();
                set_mode = 0;
                state = ENTER;
                break;
        }
        
    }
    
    return 0;
}


//interrupt to go to init state ( reset the system )
void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterupt(){
    INTERRUPT_E_FLAG = DOWN;
    int i = 0;
    
    if (state == WAIT4PRESS && (KEYPAD_PORT_ROW0 == PRESSED || KEYPAD_PORT_ROW1 == PRESSED || KEYPAD_PORT_ROW2 == PRESSED || KEYPAD_PORT_ROW3 == PRESSED)) {
        INTERRUPT_E_PINS = _OFF;
        state = WAIT;
    }
    if (state == WAIT4RELEASE && KEYPAD_PORT_ROW0 == RELEASED && KEYPAD_PORT_ROW1 == RELEASED && KEYPAD_PORT_ROW2 == RELEASED && KEYPAD_PORT_ROW3 == RELEASED ){
        //INTERRUPT_E_PINS = _ON;
        state = WAIT4PRESS;
    }
    
//    if (KEYPAD_PORT_ROW0 == PRESSED){
//        printStringLCD("ROW0");
//        for(i=0;i<1000;i++) delayUs(1000);
//        clearLCD();
//        delayUs(1000);
//        returnedKey = scanKeypad();
//        printCharLCD(returnedKey);
//        for(i=0;i<1000;i++) delayUs(1000);
//        clearLCD();
//        delayUs(1000);
//        
//    }
//    
//    if (KEYPAD_PORT_ROW1 == PRESSED){
//        printStringLCD("ROW1");
//        for(i=0;i<1000;i++) delayUs(1000);
//        clearLCD();
//        delayUs(1000);
//    }
//    
//    if (KEYPAD_PORT_ROW2 == PRESSED){
//        printStringLCD("ROW2");
//        for(i=0;i<1000;i++) delayUs(1000);
//        clearLCD();
//        delayUs(1000);
//    }
//    
//    if (KEYPAD_PORT_ROW3 == PRESSED){
//        printStringLCD("ROW3");
//        for(i=0;i<1000;i++) delayUs(1000);
//        clearLCD();
//        delayUs(1000);
//    }
    
    

}