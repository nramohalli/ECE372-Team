#include <xc.h>
#include "keypad.h"
#include "timer.h"
//
//#define INPUT 1
//#define OUTPUT 0
//
//#define ENABLED 1
//
//#define ON 1
//#define OFF 0
//
//#define DOWN 0;
//
//#define PRIORITY_7 7
//
//#define KEYPAD_TRIS_ROW0 TRISEbits.TRISE6
//#define KEYPAD_TRIS_ROW1 TRISEbits.TRISE4
//#define KEYPAD_TRIS_ROW2 TRISEbits.TRISE2
//#define KEYPAD_TRIS_ROW3 TRISEbits.TRISE0
//
//#define KEYPAD_PORT_ROW0 PORTEbits.RE6
//#define KEYPAD_PORT_ROW1 PORTEbits.RE4
//#define KEYPAD_PORT_ROW2 PORTEbits.RE2
//#define KEYPAD_PORT_ROW3 PORTEbits.RE0
//
//#define KEYPAD_TRIS_COL0 TRISBbits.TRISB11
//#define KEYPAD_TRIS_COL1 TRISBbits.TRISB13
//#define KEYPAD_TRIS_COL2 TRISBbits.TRISB15
//
//#define KEYPAD_LAT_COL0 LATBbits.LATB11
//#define KEYPAD_LAT_COL1 LATBbits.LATB13
//#define KEYPAD_LAT_COL2 LATBbits.LATB15
//
//#define PULLUP_ROW0 CNPUEbits.CNPUE6
//#define PULLUP_ROW1 CNPUEbits.CNPUE4
//#define PULLUP_ROW2 CNPUEbits.CNPUE2
//#define PULLUP_ROW3 CNPUEbits.CNPUE0
//
//#define CN_PORT_E CNCONEbits.ON
//#define CN_ROW0 CNENEbits.CNE6
//#define CN_ROW1 CNENEbits.CNE4
//#define CN_ROW2 CNENEbits.CNE2
//#define CN_ROW3 CNENEbits.CNE0
//
//#define INTERRUPT_E_FLAG IFS1bits.CNEIF
//#define INTERRUPT_E_PINS IEC1bits.CNEIE
//#define INTERRUPT_PRIORITY IPC8bits.CNIP
//
//#define ODC_COL0 ODCEbits.ODCE0
//#define ODC_COL1 ODCDbits.ODCD4
//#define ODC_COL2 ODCDbits.ODCD10


/* Initialize the rows as ODC outputs and the columns as inputs with pull-up
 * resistors. Don't forget about other considerations...
 */
void initKeypad(void){
    
    KEYPAD_TRIS_ROW0 = INPUT;
    KEYPAD_TRIS_ROW1 = INPUT;
    KEYPAD_TRIS_ROW2 = INPUT;
    KEYPAD_TRIS_ROW3 = INPUT;
        
    KEYPAD_TRIS_COL0 = OUTPUT;
    KEYPAD_TRIS_COL1 = OUTPUT;
    KEYPAD_TRIS_COL2 = OUTPUT;
    
    CN_PORT_E = KON;
    
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
char scanKeypad(void){
    char key = -1;
    
//    KEYPAD_LAT_COL0 = KON;  // If this was E pin...it might have triggered E CN
//    KEYPAD_LAT_COL1 = KOFF;
//    KEYPAD_LAT_COL2 = KOFF;
    
    if(KEYPAD_PORT_ROW0 == 0) key = '1';
    if(KEYPAD_PORT_ROW1 == 0) key = '4';
    if(KEYPAD_PORT_ROW2 == 0) key = '7';
    if(KEYPAD_PORT_ROW3 == 0) key = '*';
//    
//    KEYPAD_LAT_COL0 = KOFF;
//    KEYPAD_LAT_COL1 = KON;
//    KEYPAD_LAT_COL2 = KOFF;
    
    if(KEYPAD_PORT_ROW0 == 0) key = '2';
    if(KEYPAD_PORT_ROW1 == 0) key = '5';
    if(KEYPAD_PORT_ROW2 == 0) key = '8';
    if(KEYPAD_PORT_ROW3 == 0) key = '0';
//    
//    KEYPAD_LAT_COL0 = KOFF;
//    KEYPAD_LAT_COL1 = KOFF;
//    KEYPAD_LAT_COL2 = KON;
    
    if(KEYPAD_PORT_ROW0 == 0) key = '3';
    if(KEYPAD_PORT_ROW1 == 0) key = '6';
    if(KEYPAD_PORT_ROW2 == 0) key = '9';
    if(KEYPAD_PORT_ROW3 == 0) key = '#';
    
    return key;
}

