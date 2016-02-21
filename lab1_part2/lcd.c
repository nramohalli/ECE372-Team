/*
 * File:   lcd.c
 * Authors:
 *
 * Created on December 31, 2014, 1:39 PM
 */

/* TODO: Make define statements for each pin used in the LCD
 */
#include <xc.h>
#include "lcd.h"
#include "timer.h"

/* The pins that you will use for the lcd control will be
 * LCD_RS      RC4
 * LCD_E       RC2
 * LCD_D4      RE7
 * LCD_D5      RE5
 * LCD_D6      RE3
 * LCD_D7      RE1
 * Use these so that we will be able to test your code for grading and to
 * help you debug your implementation!
 */

#define OUTPUT 0
#define INPUT 1



#define LCD_DATA 
#define LCD_RS   LATCbits.LATC4 // pin 9
#define LCD_E    LATCbits.LATC2 // pin 7
#define LCD_D7   LATEbits.LATE7 // pin 5
#define LCD_D6   LATEbits.LATE5 // pin 4
#define LCD_D5   LATEbits.LATE3 // pin 3
#define LCD_D4   LATEbits.LATE1 // pin 100 change register 

#define TRIS_D7 TRISEbits.TRISE7 // pin 84
#define TRIS_D6 TRISEbits.TRISE5 // pin 83
#define TRIS_D5 TRISEbits.TRISE3 //pin 82
#define TRIS_D4 TRISEbits.TRISE1 //pin 81
#define TRIS_RS TRISCbits.TRISC4 // pin 9 
#define TRIS_E  TRISCbits.TRISC2 // pin 7


/* This function should take in a two-byte word and writes either the lower or upper
 * byte to the last four bits of LATE. Additionally, according to the LCD data sheet
 * It should set LCD_RS and LCD_E with the appropriate values and delays.
 * After these commands are issued, there should be a delay.
 * The command type is a simplification. From the data sheet, the RS is '1'
 * when you are simply writing a character. Otherwise, RS is '0'.
 */
void writeFourBits(unsigned char word, unsigned int commandType, unsigned int delayAfter, unsigned int lower){
    //TODO:
    // set the commandType (RS value)
       // set the commandType (RS value)
    if (lower == 1) {
        LCD_D4 = word&0x01;     // First bit
        LCD_D5 = (word&0x02) >> 1;     // Second bit
        LCD_D6 = (word&0x04) >> 2;     // Third bit
        LCD_D7 = (word&0x08) >> 3;     // Fourth bit
    }
    else {
        LCD_D4 = (word&0x10) >> 4;     // First bit
        LCD_D5 = (word&0x20) >> 5;     // Second bit
        LCD_D6 = (word&0x40) >> 6;     // Third bit
        LCD_D7 = (word&0x80) >> 7;     // Fourth bit 
    }
    
    
    LCD_RS = commandType;
    delayUs(1);
    LCD_E = 1;                      //enable
    delayUs(1);            //delay
    LCD_E = 0;   
    delayUs(delayAfter);
    //disable

    
}

/* Using writeFourBits, this function should write the two bytes of a character
 * to the LCD.
 */
void writeLCD(unsigned char word, unsigned int commandType, unsigned int delayAfter){
    //TODO:
     writeFourBits(word, commandType, delayAfter, 0);
    writeFourBits(word, commandType, delayAfter, 1);  
    
    
}

/* Given a character, write it to the LCD. RS should be set to the appropriate value.
 */
void printCharLCD(char c) {
    //TODO:
     writeLCD(c,1,40);

}
/*Initialize the LCD
 */
void initLCD(void) {
    // Setup D, RS, and E to be outputs (0).
    TRIS_D7 = OUTPUT;
    TRIS_D6 = OUTPUT;
    TRIS_D5 = OUTPUT;
    TRIS_D4 = OUTPUT;
    TRIS_RS = OUTPUT;
    TRIS_E = OUTPUT; // Enable 4-bit interface
    
    // Initilization sequence utilizes specific LCD commands before the general configuration
    // commands can be utilized. The first few initialition commands cannot be done using the
    // WriteLCD function. Additionally, the specific sequence and timing is very important.

    //delayUs(15000); //150ms delay 
     int i = 0; // Loop needed to make a diley of 1.64 ms
    for (i = 0; i < 100; i++) { //
        delayUs(150); //***********************
    }
    

    // Function Set (specifies data width, lines, and font.
    
    writeFourBits(0x30, 0, 4100, 0); //4100ms delay 
    writeFourBits(0x30, 0, 100, 0); //change to 100 us delay later 
    writeLCD(0x32, 0, 40); 
   
     // 4-bit mode initialization is complete. We can now configure the various LCD
    // options to control how the LCD will function.
    
    writeLCD(0x28, 0, 40); //sets N to two lien display 
    writeLCD(0x08, 0, 40); //on and off display
    writeLCD(0x01, 0, 1640); //clear display 
    writeLCD(0x06, 0, 40); //entry mode set
    writeLCD(0x0C, 0, 40); // display on, cursor off, blink off
   
}

/*
 * You can use printCharLCD here. Note that every time you write a character
 * the cursor increments its position automatically.
 * Since a string is just a character array, try to be clever with your use of pointers.
 */
void printStringLCD(const char* s) {
    //TODO:
    
     int i = 0;
    for(i = 0; i < strlen(s); i++){
    printCharLCD(s[i]);
    }

}

/*
 * Clear the display.
 */
void clearLCD(){
    writeLCD(0x01, 0, 1640);
}

/*
 Use the command for changing the DD RAM address to put the cursor somewhere.
 */
void moveCursorLCD(unsigned char x, unsigned char y){
    
    if (y != 0) y = 0x40;
    writeLCD(0x80 + x + y, 0, 46); 
    
}

/*
 * This function is called in lab1p2.c for testing purposes.
 * If everything is working properly, you should get this to look like the video on D2L
 * However, it is suggested that you test more than just this one function.
 */
void testLCD(){
    initLCD();
    int i = 0;
    printCharLCD('c');
    for(i = 0; i < 1000; i++) delayUs(1000);
    clearLCD();
    printStringLCD("Hello!");
    moveCursorLCD(1, 2);
    for(i = 0; i < 1000; i++) delayUs(1000);
    printStringLCD("Hello!");
    for(i = 0; i < 1000; i++) delayUs(1000);
     
}