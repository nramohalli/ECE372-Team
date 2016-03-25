// ******************************************************************************************* //
//
// File:         lab3p1.c
// Date:         3-7-2016
// Authors:      Team 213
//
// Description: 
// ******************************************************************************************* //

#include <xc.h>
#include <sys/attribs.h>
#include "lcd.h"
#include "timer.h"
#include "config.h"
#include "interrupt.h"
#include "keypad.h"
#include "ADC.h"
#include "PWM.h"

//TODO: Define states of the state machine
typedef enum stateTypeEnum{
    INIT_IDLE, DE_IDLE, FORWARD, DE_FORWARD, IDLE_2, DE_IDLE_2, BACKWARD, DE_BACKWARD, VOLTAGE_LCD
} stateType;


volatile stateType state = INIT_IDLE;
volatile int speed = 0;
//volatile char key=-1;
volatile int i=0;
volatile int check=0;
volatile int val = 0;
volatile int col=3;
volatile char returnedKey = -1;
volatile int ready = 0;

// ******************************************************************************************* //

int main(void)
{   
    
    SYSTEMConfigPerformance(40000000);
    
    initLCD();
    initPWM();
    initTimer2();
    initTimer3();
    initADC();
    enableInterrupts();                   //This function is necessary to use interrupts.
   
    unsigned long int speed = 0;
    unsigned long int direction = 0;
    volatile float printbuffer = 0; //maybe change to float
   // double voltPOT = 0;
    
    char str[16];
    
    while(1){
        
        switch(state){
            
            case INIT_IDLE:
                OC2RS = 0;
                OC4RS = 0;
                break;
            
            
            case FORWARD:
                OC2RS = ADC1BUF0;
                OC4RS = 0;
                break;
                
            case BACKWARD:
                OC2RS = 0;
                OC4RS = 1023 - ADC1BUF0;
                break;
        }
        
    }
    
    return 0;
}

//interrupt to go to init state ( reset the system ) but I dont think we will need this for part 1
void __ISR(_ADC_VECTOR, IPL7SRS) _ADCInterrupt(){
    
   IFS0bits.AD1IF = 0; //flag down
   
   if(ADC1BUF0 > 512){
       state = FORWARD;
       OC2RS = ADC1BUF0;
       OC4RS = 0;
   }
   else if(ADC1BUF0 == 512){
       state = INIT_IDLE;
       OC2RS = 0;
       OC4RS = 0;
   }
   
   else {
       state = BACKWARD;
       OC2RS = 0;
       OC4RS = 1032 - ADC1BUF0;
   }
   
}
 