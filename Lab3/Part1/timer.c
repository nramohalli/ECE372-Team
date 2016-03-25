#include <xc.h>
#include "timer.h"

void initTimer2(){
    TMR2 = 0;
    //PR2 = 1023;
    T2CONbits.TCKPS = 2; //initializing prescalar to 
    T2CONbits.TCS = 0;
    T2CONbits.ON = 0;
    IFS0bits.T2IF = 0;
}

void initTimer3(){
    TMR3 = 0;
    PR3 = 1023;
    T3CONbits.TCKPS = 0; //initializing prescalar to 
    T3CONbits.TCS = 0;
    T3CONbits.ON = 1;
    IFS0bits.T3IF = 0;
}

void delayUs(unsigned int delay){
    
    //T2CONbits.ON = 0;
    
    TMR2 = 0;
    PR2 = delay*4;
    IFS0bits.T2IF = 0;
    T2CONbits.ON = 1;
    while(IFS0bits.T2IF == 0);
    T2CONbits.ON = 0;
}