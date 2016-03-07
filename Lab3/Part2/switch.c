
#include <xc.h>
#include "switch.h"


void switch1() {
    
 TRISAbits.TRISA7= 1;  
 CNPUAbits.CNPUA7= 1;
 CNCONAbits.ON =1;
 CNENAbits.CNIEA7= 1;
 IFS1bits.CNAIF=0;
 IEC1bits.CNAIE=1;
 IPC8bits.CNIP=7;

    
}
