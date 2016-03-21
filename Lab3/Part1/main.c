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
    INIT_IDLE, DE_IDLE, FORWARD, DE_FORWARD, IDLE_2, DE_IDLE_2, BACKWARD, DE_BACKWARD
} stateType;

volatile stateType state=INIT_IDLE;
//volatile char key=-1;
volatile int j=0;
volatile int check=0;
volatile int col=3;
volatile char returnedKey = -1;

// 3/2/16- so far column 1 works I think there is a code problem that doesn't let the other two columns go low when button pressed
//switch interrupts from triggering on row changes to triggering on column changes since that is what we are scanning
// ******************************************************************************************* //

int main(void)
{   
    enableInterrupts();                   //This function is necessary to use interrupts.
    initLCD();
    initPWM();
    initADC();
   
    unsigned long int speed = 0;
    unsigned long int direction = 0;
    double voltPOT = 0;
    
    SYSTEMConfigPerformance(10000000);
    
    while(1){
        // get voltage across the POT
        voltPOT = ;
        
        // read data from interrupt
        // print data to lcd
        printStringLCD(voltPOT);
        
        // move motor
        setMotorSpeed(speed);
        setMotorDirection(direction);
    }
    return 0;
}

//interrupt to go to init state ( reset the system )
void __ISR(27_ADC_VECTOR, ip17) _CNInterupt(){
    //INTERRUPT_FLAG = DOWN;
    IFS0bits.AD1IF = 0;
    
    speed = ADC1BUF0;
    direction = ADC1BUF8;  
}