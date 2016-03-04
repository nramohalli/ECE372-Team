#include <xc.h>
#include "timer.h"



void initTimer1(){
    TMR1=0; //clear timer
    PR1=19531;//initializing PR1 counting to 1 ms
    T1CONbits.TCKPS=3;//setting prescalar for 1 sec
    T1CONbits.TCS=0;//setting the oscillator
    IEC0bits.T1IE=1; //interrupt configuration
    IFS0bits.T1IF=0;
    IPC1bits.T1IP=3;
    //T1CONbits.TON=0;
}

void initTimer2(){
       TMR2 = 0;
    T2CONbits.TCKPS = 2; //initializing prescalar to 
    T2CONbits.TCS = 0;
    IFS0bits.T2IF = 0;
    T2CONbits.ON = 0;

}

void delayUs(unsigned int delay){
TMR2 = 0;
    PR2 = delay*4;
  
    IFS0bits.T2IF = 0;
    T2CONbits.ON = 1;
    while(IFS0bits.T2IF == 0);
    T2CONbits.ON = 0;
    // while(IFS0bits.T2IF==0){};
    //T2CONbits.ON=0; 

    
}