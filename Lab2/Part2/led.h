/* 
 * File:   led.h
 * Author: gvanhoy
 *
 * Created on August 27, 2015, 3:15 PM
 */

#ifndef LED_H
#define	LED_H

#define OUTPUT 0
#define INPUT 1
#define ON 1
#define OFF 0

#define RedLED LATDbits.LATD0
#define YellowLED LATDbits.LATD1
#define GreenLED LATDbits.LATD2

void initLEDs();
void turnOnLED(int led);

#endif	/* LED_H */

