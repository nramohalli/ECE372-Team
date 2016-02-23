/*
 * File:   timer.c
 * Authors:
 *
 * Created on December 30, 2014, 8:07 PM
 */

#include <xc.h>
#include "timer.h"

void initTimer2(){
    TMR2 = 0;
    T2CONbits.TCKPS = 3; //initializing prescalar to 8
    T2CONbits.TCS = 0;
    IFS0bits.T2IF = 0;
    T2CONbits.ON = 0;
}



void delayUs(unsigned int delay){

    //TODO: Create a delay for "delay" micro seconds using timer 2
    TMR2 = 0;
    PR2 = delay*10;
  
    IFS0bits.T2IF = 0;
    T2CONbits.ON = 1;
    while(IFS0bits.T2IF == 0);
    T2CONbits.ON = 0;
}

void testTimer(void){
    
    int i = 0;
    TRISDbits.TRISD0 = 0;
    for(i=1; i<=10000; i++){
        LATDbits.LATD0 = !LATDbits.LATD0;
        delayUs(i);
    }
    
}
    
    
    
    
    
    
    
  
