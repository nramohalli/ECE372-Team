/* ************************************************************************** */
/* This file is going to initialize the SPI communication ports for the IR sensors on the
 * Robot. It will also be where the functions for initializing SPI will be put. There will
 * also be a test function to test to see if SPI is working the way we expect */

/* ************************************************************************** */

#ifndef _SPI_H    /* Guard against multiple inclusion */
#define _SPI_H

#define SPI2_SDI    SDI2Rbits.SDI2R
#define SPI2_SDO    RPG8bits.RPG8R
#define SPI2_CKEDGE SPI2CONbits.CKE
#define SPI2_CKPOL  SPI2CONbits.CKP

//functions
void initSPI2();

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
