/* 
 * File:   PWM.h
 * Author: Shivani
 *
 * Created on March 7, 2016, 10:19 AM
 */

#ifndef PWM_H
#define	PWM_H

#ifdef	__cplusplus
extern "C" {
#endif


void initPWM();
void printVoltage(int adcVal);
void setLeftWheelSpeed(int val);
void setRightWheelSpeed(int val);
void setLeftForward(int true);
void setRightForward(int true);







#ifdef	__cplusplus
}
#endif

#endif	/* PWM_H */

