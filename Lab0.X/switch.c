/* 
 * File:   led.c
 * Author: jtjohnston
 *
 * Created on February 4, 2016, 9:22 AM
 */

#include <xc.h>
#include "switch.h"

#define OUTPUT 0
#define INPUT 1

void initSwitch(){
    //TODO: Initialize LEDs
    TRISDbits.TRISD6 = INPUT;
    CNPUDbits.CNPUD6 = 1;
    CNCONDbits.ON = 1;
    CNENDbits.CNIED6 = 1;
    IFS1bits.CNDIF = 0;
    IEC1bits.CNDIE = 1;
    IPC8bits.CNIP = 7;
    
}
