/* 
 * File:   timer.c
 * Author: gvanhoy
 *
 * Created on August 27, 2015, 3:26 PM
 */

#include <xc.h>
#include "timer.h"

void initTimer1(){
    //TODO: Initialize Timer 1 to have a period of
    // 1 second. Enable its interrupt
    TMR1 = 0;// clear TMR1 
    T1CONbits.TCKPS = 3; // pre-scalar of 256
    PR1 = 39061;// Initialize PR1 
    T1CONbits.ON = 1;// Turn the timer on 
    IEC0bits.T1IE = 1;// Enable the interrupt 
    IPC1bits.T1IP = 7;// Configure the Interrupt Priority 
    TIMERFLAG = 0;// Put the flag down 
    T1CONbits.TCS = 0; // Setting the oscillator 
}