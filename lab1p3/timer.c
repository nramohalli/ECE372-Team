/*
 * File:   timer.c
 * Authors:
 *
 * Created on December 30, 2014, 8:07 PM
 */

#include <xc.h>
#include "timer.h"


void initTimer1(){
    TMR1=0; //clear timer
    PR1=39061;//initializing PR1


	// for this part i think this needs to be changed to millisec

    T1CONbits.TCKPS= 3;//setting prescalar for 1 sec
    T1CONbits.TCS=0;//counter
    IEC0bits.T1IE=1; //interrupt configuration
    IFS0bits.T1IF=0;
    IPC1bits.T1IP=7; //priority
    T1CONbits.ON=1; //turning timer on

}

initTimer2(){
    TMR2=0;
    T2CONbits.TCKPS=0;
    T2CONbits.TCS=0;
    IFS0bits.T2IF=0;
}

void delayUs(unsigned int delay){

    TMR2= 0;
    PR2 = 624*delay;
    IFS0bits.T2IF=0;
    T2CONbits.ON = 1;
    while(IFS0bits.T2IF==0){};
    T2CONbits.ON=0;

    
}

//function will create a string using the timers value and return in MM:SS:FF format
String getTimeString()
{
	int min = 0;
	int sec = 0;
	int pre = 0;
	
	min = TMR1%360;
	sec = (TMR1 - min*360)%60;
	pre = (TMR1 - min*360 - sec*60)/60*100;

	return ("%d:%d:%d", min, sec, pre);;
}