/* 
 * File:   LCD_4bits.h
 * Author: Ing. Marcos Becerra.
 * Date: January 11, 2021
 * Copyright (c) 2021 Marcos Becerra
 * see the file LICENSE for copying permission.
 * 
 * Version 1.0 developed in 2020.
 * -Development of the source code and its control function.
 * Version 2.0 developed in 2021.
 * -Library creation with its own functions.
 * Version 3.0 developed in 2022.
 * -Integration of more functions.
 * 
 * INFO:
 * This library is open source, so you can modify it as you like.
 * The library was developed for the XC8 V2.32 compiler specifically for the 
 * PIC16F887 microcontroller, this code is flexible to implement for any 8-bit 
 * microcontroller, clearly making certain modifications to be 100% compatible 
 * with the device you use, also the library is prepared to work in 4 bit mode.
 * 
 * This library is compatible for 16x2 LCD model "LM016L" which uses the chip
 * HITACHI HD44780U or equivalent.
 * 
 * For more information contact me:
 * My Account:
 * marcos.bzarate@alumnos.udg.mx
 * 
 * My YouTube Channel:
 * https://www.youtube.com/channel/UCaW-5pa18N2Yxjkc4ejOPdQ
 * LCD library header file
 * 
 */

/******************************************************************************/
/*      Pin Connections
 *      |---LCD---|     |--PIC16F887---|
 *          VSS ------------- GND 
 *          VDD ------------- +5V.
 *          Vo  ------------- (-)  to the potentiometer.
 *          RS  ------------- RB2
 *          RW  ------------- GND
 *          E   ------------- RB3
 *        D0..D3------------- (-) No connection, the lcd works in mode 4 bits.
 *          D4  ------------- RB4                
 *          D5  ------------  RB5
 *          D6  ------------  RB6
 *          D7  ------------  RB7
 *   
 * For the library to work well, it's necessary to include these three functions
 * in the main code.
 * 
 * void delay_5ms_LCD(void) { __delay_ms(5); }
 * void delay_2ms_LCD(void) { __delay_ms(2); }
 * void delay_40us_LCD(void) { __delay_us(40); }
 */




#ifndef LCD_4BITS_H
#define	LCD_4BITS_H

#include <xc.h>

#ifdef	__cplusplus
extern "C" {
#endif
//Macros:
//----------------------------Control commands----------------------------------
#define LCD_CLEAR 0x01                                  //Clear LCD.
#define LCD_CURSOR_HOME 0x02                            //Return Cursor (0,0).

//Entry mode set
#define LCD_DECREASE_DDRAM_DISPLAY_SHIFT_OFF   0x04            //Decrease DDRAM pointer, no shift.
#define LCD_DECREASE_DDRAM_DISPLAY_SHIFT_ON    0x05            //Decrease DDRAM pointer, shift.
#define LCD_INCREASE_DDRAM_DISPLAY_SHIFT_OFF   0x06            //Increase DDRAM pointer, no shift.
#define LCD_INCREASE_DDRAM_DISPLAY_SHIFT_ON    0x07            //Increase DDRAM pointer, shift.

//Display on/off control
#define LCD_DISPLAY_OFF_CURSOR_OFF_CHARACTER_BLINK_OFF  0x08   //Display off, cursor off, and character no blink. 
#define LCD_DISPLAY_OFF_CURSOR_OFF_CHARACTER_BLINK_ON   0x09   //Display off, cursor off, and character blink.
#define LCD_DISPLAY_OFF_CURSOR_ON_CHARACTER_BLINK_OFF   0x0A   //Display off, cursor on, and character no blink.
#define LCD_DISPLAY_OFF_CURSOR_ON_CHARACTER_BLINK_ON    0x0B   //Display off, cursor on, and character blink.
#define LCD_DISPLAY_ON_CURSOR_OFF_CHARACTER_BLINK_OFF   0x0C   //Display on, cursor off, and character no blink.
#define LCD_DISPLAY_ON_CURSOR_OFF_CHARACTER_BLINK_ON    0x0D   //Display on, cursor off, and character blink.
#define LCD_DISPLAY_ON_CURSOR_ON_CHARACTER_BLINK_OFF    0x0E   //Display on, cursor on, and character no blink.
#define LCD_DISPLAY_ON_CURSON_ON_CHARACTER_BLINK_ON     0x0F   //Display on, cursor on, and character blink.

//Cursor or display shift
#define LCD_CURSOR_SHIFT_LEFT   0x10    //Move cursor and shift to the left.
#define LCD_CURSOR_SHIFT_RIGHT  0x14    //Move cursor and shift to the right.
#define LCD_DISPLAY_SHIFT_LEFT  0x18    //Move display to the left.
#define LCD_DISPLAY_SHIFT_RIGHT 0x1C    //Move display to the right.

//Function set
#define LCD_4BITS_1LINE_5X8     0x20    //4 bits, 1 line and 5x8 dots.
#define LCD_4BITS_1LINES_5X10   0x24    //4 bits, 1 line and 5x10 dots.
#define LCD_4BITS_2LINES_5X8    0x28    //4 bits, 2 lines and 5x8 dots.
#define LCD_4BITS_2LINES_5X10   0x2C    //4 bits, 2 lines, and 5x10 dots.
#define LCD_8BITS_1LINE_5X8     0x30    //8 bits, 1 line, and 5x8 dots.
#define LCD_8BITS_1LINE_5X10    0x34    //8 bits, 1 line, and 5x10 dots.
#define LCD_8BITS_2LINES_5X8    0x38    //8 bits, 2 lines, and 5x8 dots.
#define LCD_8BITS_2LINES_5X10   0x3C    //8 bits, 2 lines, and 5x10 dots.

//Select port for lcd.
#define PORT_LCD PORTB
#define TRIS_LCD TRISB
    
void Lcd_Init(void);                                
void Lcd_Cmd(char command);
void Lcd_SetCursor(char row, char column);
void Lcd_Chr(char row, char column, char out_char);
void Lcd_Chr_Cp(char out_char);
void Lcd_String(char row, char column, char *text);
void Lcd_String_Cp(char *text);
extern void delay_5ms_LCD(void);
extern void delay_2ms_LCD(void);
extern void delay_40us_LCD(void);

#ifdef	__cplusplus
}
#endif

#endif	/* LCD_4BITS_H */

/*You can probe the next code for PIC16F887:
#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config LVP = OFF
#pragma config FCMEN = OFF

#include <xc.h>
#include "LCD_4bits.h"
#define _XTAL_FREQ 16000000

void setup(void);
void delay_5ms_LCD(void);
void delay_2ms_LCD(void);
void delay_40us_LCD(void);

void main(int argc, char** argv) {
    setup();
    Lcd_Init();
    Lcd_Cmd(LCD_CLEAR);
    Lcd_SetCursor(1,1);
    Lcd_String_Cp("Hello my friends");
    Lcd_SetCursor(2,1);
    Lcd_String_Cp("Libreria LCD 16x2");
    __delay_ms(1000);
    
    while(1)    {
        PORTBbits.RB0 = 1;
        PORTBbits.RB1 = 1;
        __delay_ms(500);
        PORTBbits.RB0 = 0;
        PORTBbits.RB1 = 0;
        __delay_ms(500);
        
    }
    return;
}

void setup()    {
    OSCCONbits.SCS = 0;            //Clock source defined by FOSC<2:0> of the CONFIG1 register
    ANSELH = 0x00;                 
    TRISB = 0xFC;
    PORTB = 0x00;
} 

void delay_5ms_LCD(void) { 
    __delay_ms(5); 
}
void delay_2ms_LCD(void) { 
    __delay_ms(2); 
}
void delay_40us_LCD(void) { 
    __delay_us(40); 
}

 */
