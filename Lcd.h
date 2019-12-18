/*
 * Lcd.h:
 * Header file library for LCD 2x16 (hd44780)
 * Author: Carlos 
 */

#ifndef _Lcd_H
#define _Lcd_H

#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <string.h> 


//*********************************************************************
// Wiring definitions
//*********************************************************************

#define Pin_num 1  //Pin numbering: 0-BCM 1-wPi

#define LCD_E 4
#define LCD_RS 3
#define LCD_D4 5
#define LCD_D5 6
#define LCD_D6 2
#define LCD_D7 26

//*********************************************************************
// Functions
//*********************************************************************

// LCD initialization
void lcd_init(void);

// Send text to LCD
void lcd_text(char *s);

// Clear LCD 
void lcd_clear(void);

// Set cursor to position 0;0
void lcd_home(void);

//Set cursor position 
void lcd_GoTo(char, char);

#endif