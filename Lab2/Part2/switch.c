#include <xc.h>
#include "switch.h"

#define INPUT 1
#define OUTPUT 0

#define ENABLED 1
#define DISABLED 0


void initSW()
{
 TRISAbits.TRISA7= 1;    
  CNCONAbits.ON =1;
  CNENAbits.CNIEA7= 1;
  CNPUAbits.CNPUA7= 1;
  IFS1bits.CNAIF=0;
}