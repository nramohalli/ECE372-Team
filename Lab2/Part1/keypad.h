/* 
 * File:   keypad.h
 * Author: user
 *
 * Created on February 5, 2015, 11:42 AM
 */

#ifndef KEYPAD_H
#define	KEYPAD_H


#define INPUT 1
#define OUTPUT 0

#define ENABLED 1

#define KON 1
#define KOFF 0

#define DOWN 0;

#define PRIORITY_7 7

#define KEYPAD_TRIS_ROW0 TRISEbits.TRISE0
#define KEYPAD_TRIS_ROW1 TRISEbits.TRISE6
#define KEYPAD_TRIS_ROW2 TRISEbits.TRISE4
#define KEYPAD_TRIS_ROW3 TRISEbits.TRISE2

#define KEYPAD_PORT_ROW0 PORTEbits.RE0
#define KEYPAD_PORT_ROW1 PORTEbits.RE6
#define KEYPAD_PORT_ROW2 PORTEbits.RE4
#define KEYPAD_PORT_ROW3 PORTEbits.RE2

#define KEYPAD_TRIS_COL0 TRISGbits.TRISG14
#define KEYPAD_TRIS_COL1 TRISDbits.TRISD4
#define KEYPAD_TRIS_COL2 TRISDbits.TRISD5

#define KEYPAD_LAT_COL0 LATGbits.LATG14
#define KEYPAD_LAT_COL1 LATDbits.LATD4
#define KEYPAD_LAT_COL2 LATDbits.LATD5

#define PULLUP_ROW0 CNPUEbits.CNPUE0
#define PULLUP_ROW1 CNPUEbits.CNPUE6
#define PULLUP_ROW2 CNPUEbits.CNPUE4
#define PULLUP_ROW3 CNPUEbits.CNPUE2

#define CN_PORT_E CNCONEbits.ON
#define CN_ROW0 CNENEbits.CNIEE0
#define CN_ROW1 CNENEbits.CNIEE6
#define CN_ROW2 CNENEbits.CNIEE4
#define CN_ROW3 CNENEbits.CNIEE2

#define INTERRUPT_E_FLAG IFS1bits.CNEIF
#define INTERRUPT_E_PINS IEC1bits.CNEIE
#define INTERRUPT_PRIORITY IPC8bits.CNIP


#define ODC_COL0 ODCGbits.ODCG14
#define ODC_COL1 ODCDbits.ODCD4
#define ODC_COL2 ODCDbits.ODCD5

void initKeypad(void);
char scanKeypad(void);

#endif	/* KEYPAD_H */

