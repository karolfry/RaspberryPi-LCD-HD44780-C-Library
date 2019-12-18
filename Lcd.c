/*
 * Lcd.c:
 * Source file library for LCD 2x16 (hd44780)
 * Author: Carlos 
 */

#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <string.h> 
#include "Lcd.h"

//*********************************************************************
//pulsEnable
//set E_Pin to HIGH than too LOW
//*********************************************************************
void pulseEnable ()
{
   digitalWrite (LCD_E, HIGH) ; 
   delay(0.5); //  1/2 microsecond pause - enable pulse must be > 450ns
   digitalWrite (LCD_E, LOW) ; 
}

//*********************************************************************
//SetCmdMode
//set RS_Pin to LOW - sending command to LCD 
//*********************************************************************
void lcd_byte(char bits)
{
  digitalWrite (LCD_D4,(bits & 0x10)) ;  
  digitalWrite (LCD_D5,(bits & 0x20)) ;  
  digitalWrite (LCD_D6,(bits & 0x40)) ;  
  digitalWrite (LCD_D7,(bits & 0x80)) ;  
  pulseEnable();

  digitalWrite (LCD_D4,(bits & 0x1)) ;  
  digitalWrite (LCD_D5,(bits & 0x2)) ;  
  digitalWrite (LCD_D6,(bits & 0x4)) ;  
  digitalWrite (LCD_D7,(bits & 0x8)) ;  
  pulseEnable();      	
}

//*********************************************************************
//SetCmdMode
//set RS_Pin to LOW - sending command to LCD 
//*********************************************************************
void SetCmdMode() 
{
  digitalWrite (LCD_RS, 0); 
}

//*********************************************************************
//SetChrMode
//set RS_Pin to HIGH - sending text to LCD 
//*********************************************************************
void SetChrMode() 
{
  digitalWrite (LCD_RS, 1); // set for characters
}

//*********************************************************************
//lcd_init
//Initialization GPIO and LCD
//*********************************************************************
void lcd_init()
{
  //choosing GPIO numbering method
  if (Pin_num == 0) wiringPiSetupSys () ;       
  else if (Pin_num == 1) wiringPiSetupGpio () ;

  // Setting pins as outputs
   pinMode (LCD_E,  OUTPUT);
   pinMode (LCD_RS, OUTPUT);
   pinMode (LCD_D4, OUTPUT);
   pinMode (LCD_D5, OUTPUT);
   pinMode (LCD_D6, OUTPUT);
   pinMode (LCD_D7, OUTPUT);
   
   // initialize LCD
   SetCmdMode();   // set for commands
   lcd_byte(0x33); // full init 
   lcd_byte(0x32); // 4 bit mode
   lcd_byte(0x28); // 2 line mode
   lcd_byte(0x0C); // display on, cursor off, blink off
   lcd_byte(0x01);  // clear screen
   delay(3);        // clear screen is slow!
}


//*********************************************************************
//lcd_text
//send string to LCD 
//*********************************************************************
void lcd_text(char *s)
{
  SetChrMode();
  while(*s) 
	lcd_byte(*s++);
 }


//*********************************************************************
//lcd_clear
//Clear Lcd screen
//*********************************************************************
void lcd_clear()
{
  SetCmdMode();    // Cmd mode
  lcd_byte(0x01);  // clear screen
  delay(3);        // clear screen is slow!
}


//*********************************************************************
//lcd_home
//Set cursor to position 0;0
//*********************************************************************
void lcd_home()
{
  SetCmdMode();    // Cmd mode
  lcd_byte(0x02);  // clear screen
  delay(3);
}

//*********************************************************************
//lcd_home
//Set cursor position x,y 
//*********************************************************************
void lcd_GoTo(char x, char y)
{
  SetCmdMode();    // Cmd mode
  lcd_byte(0x80 | (x + (0x40 * y)));
  delay(3);
}



