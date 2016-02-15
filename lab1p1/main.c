

#include <xc.h>
#include <sys/attribs.h>
#include "config.h"
#include "interrupt.h"
#include "switch.h"
#include "led.h"
#include "timer.h"




#define OUTPUT 0
#define INPUT 1


int main() {
    SYSTEMConfigPerformance(10000000);    //Configures low-level system parameters for 10 MHz clock
    enableInterrupts();                   //This function is necessary to use interrupts.

    
    initLEDs();
    //initTimer1();
   initTimer2();
    initSW();
    
    
    while(1){
        
        if(IFS1bits.CNAIF==1 && PORTAbits.RA7==1)
        {
            delayMs(5);
        LATGbits.LATG12=!LATGbits.LATG12;
        LATGbits.LATG14=!LATGbits.LATG14;
        IFS1bits.CNAIF=0;
            delayMs(5);
        }
        
    }
    
    return 0;
}


  

