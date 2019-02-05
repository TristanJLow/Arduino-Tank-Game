#include "LCD.h"
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "ASCIIFont.h"	

void LCDWrite(unsigned char dc, unsigned char data) {
	// Set the DC pin based on the parameter 'dc'
	OUTPUT_WRITE(PORTB,DCPIN,dc);
	
	// Pull the SCE/SS pin low to signal to the LCD we have data
	OUTPUT_LOW(PORTD,SCEPIN);
	
	// Write the byte of data using "bit bashing"
	int i;
	for(i = 7; i >= 0; i--) {
		OUTPUT_LOW(PORTF, SCKPIN) ;
		if(data>>i & 1 == 1) {
			OUTPUT_HIGH(PORTB, DINPIN);
		} else {
			OUTPUT_LOW(PORTB, DINPIN);
		}
		OUTPUT_HIGH(PORTF, SCKPIN);
	}
	
	// Pull SCE/SS high to signal the LCD we are done
	OUTPUT_HIGH(PORTD,SCEPIN);
}

void LCDInitialise(unsigned char contrast) {
	// Configure all of the pins correctly
	SET_OUTPUT(DDRD, SCEPIN);
	SET_OUTPUT(DDRB, RSTPIN);
	SET_OUTPUT(DDRB, DCPIN);
	SET_OUTPUT(DDRB, DINPIN);
	SET_OUTPUT(DDRF, SCKPIN);
		
	// Reset the screen
	OUTPUT_LOW(PORTB, RSTPIN);
	OUTPUT_HIGH(PORTD, SCEPIN);
	OUTPUT_HIGH(PORTB, RSTPIN);
  
  	// Send configuration commands to the screen
	LCDWrite(LCD_C, 0x21); 				// Enable LCD extended command set
	LCDWrite(LCD_C, 0x80 | contrast ); 	// Set LCD Vop (Contrast)
	LCDWrite(LCD_C, 0x04);
	LCDWrite(LCD_C, 0x14); 				// LCD bias mode 1:48
  
	LCDWrite(LCD_C, 0x0C); 				// LCD in normal mode.
  	LCDWrite(LCD_C, 0x20); 				// Enable LCD basic command set
	LCDWrite(LCD_C, 0x0C);

	LCDWrite(LCD_C, 0x40); 				// Reset row to 0
	LCDWrite(LCD_C, 0x80); 				// Reset column to 0
}

void LCDClear(void) {
	int i;
	for (i = 0; i <= (LCD_X * (LCD_Y/8)); i++) {
		LCDWrite(LCD_D, 0x00);
	}
}

void LCDCharacter(unsigned char character) {
	LCDWrite(LCD_D, 0x00);
	int i;
	
	for (i = 0; i < 5; i++) {
		LCDWrite(LCD_D, ASCII[character - 0x20][i]);
	}

	LCDWrite(LCD_D, 0x00);
}

void LCDString(unsigned char *characters) {
	int i = 0;
	while (characters[i] != '\0') {
		LCDCharacter(characters[i]);
		i++;
	}	
}

void LCDPosition(unsigned char x, unsigned char y) {
	//sets Y address between 0 and 5
	LCDWrite(LCD_C, 0b01000000 | y);
	
	//sets X address between 0 and 83
	LCDWrite(LCD_C, 0b10000000 | x);
}