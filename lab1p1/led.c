/* 
 * File:   led.c
 * Author: gvanhoy
 *
 * Created on August 27, 2015, 3:15 PM
 */

#include <xc.h>
#include "led.h"
//#define ON 0
#define OUTPUT 0

void initLEDs(){
 
TRISGbits.TRISG12= OUTPUT;   
LATGbits.LATG12=0;//define LED1 as output and initialize as ON
  
 //ODCGbits.ODCG12=1; 
    
//ODCGbits.ODCG14=1;
TRISGbits.TRISG14= OUTPUT;
LATGbits.LATG14= 1;//define LED2 as output and initialize as ON
 
    
//LATDbits.LATD2= ON; //define LED3 as output and initialize as ON
//    TRISDbits.TRISD2= OUTPUT;    
}

  //IEC1bits.CNAIE= 1;
// IPC8bits.CNIP=7;
  

