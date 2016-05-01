/* 
 * File:   ADC.h
 * Author: Shivani
 *
 * Created on March 7, 2016, 10:05 AM
 */

#ifndef ADC_H
#define	ADC_H

#ifdef	__cplusplus
extern "C" {
#endif

void initADC();
void scanMiddleIRVoltage();
void scanLeftIRVoltage();
void scanRightIRVoltage();
void scanBackIRVoltage();

#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */

