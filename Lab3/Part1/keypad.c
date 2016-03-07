#include <xc.h>
#include "keypad.h"
#include "timer.h"
#include "lcd.h"


/* Initialize the rows as ODC outputs and the columns as inputs with pull-up
 * resistors. Don't forget about other considerations...
 */
void initKeypad(void){
    ANSELE=0;
    KEYPAD_TRIS_ROW0 = INPUT;
    KEYPAD_TRIS_ROW1 = INPUT;
    KEYPAD_TRIS_ROW2 = INPUT;
    KEYPAD_TRIS_ROW3 = INPUT;
        
    KEYPAD_TRIS_COL0 = OUTPUT;
    KEYPAD_TRIS_COL1 = OUTPUT;
    KEYPAD_TRIS_COL2 = OUTPUT;
    
    CN_PORT_E = _ON;
    
    CN_ROW0 = ENABLED;
    CN_ROW1 = ENABLED;
    CN_ROW2 = ENABLED;
    CN_ROW3 = ENABLED;
    
    INTERRUPT_E_FLAG = DOWN;
    INTERRUPT_E_PINS = ENABLED;         // Enables interrupt for E pins
    INTERRUPT_PRIORITY = PRIORITY_7;

    PULLUP_ROW0 = ENABLED;
    PULLUP_ROW1 = ENABLED;
    PULLUP_ROW2 = ENABLED;
    PULLUP_ROW3 = ENABLED;
//    
    ODC_COL0 = ENABLED;
    ODC_COL1 = ENABLED;
    ODC_COL2 = ENABLED;
    
}

/* This function will be called AFTER you have determined that someone pressed
 * SOME key. This function is to figure out WHICH key has been pressed.
 * This function should return -1 if more than one key is pressed or if
 * no key is pressed at all. Otherwise, it should return the ASCII character of
 * the key that is pressed. The ascii character c programmatically is just 'c'
 */
char scanKeypad(int column){
    
    char key= '!';
    
    if(column == 0){
    if(KEYPAD_PORT_ROW0 == PRESSED) return '1';
    if(KEYPAD_PORT_ROW1 == PRESSED) return '4';
    if(KEYPAD_PORT_ROW2 == PRESSED) return '7';
    if(KEYPAD_PORT_ROW3 == PRESSED) return '*';
    }
    
    if(column == 1){
    if(KEYPAD_PORT_ROW0 == PRESSED) return '2';
    if(KEYPAD_PORT_ROW1 == PRESSED) return '5';
    if(KEYPAD_PORT_ROW2 == PRESSED) return '8';
    if(KEYPAD_PORT_ROW3 == PRESSED) return '0';
    }
    
    if(column == 2){
    if(KEYPAD_PORT_ROW0 == PRESSED) return '3';
    if(KEYPAD_PORT_ROW1 == PRESSED) return '6';
    if(KEYPAD_PORT_ROW2 == PRESSED) return '9';
    if(KEYPAD_PORT_ROW3 == PRESSED) return '#';
    }
    
    return key;
}

