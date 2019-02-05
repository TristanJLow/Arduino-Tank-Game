/*
 * Graphics.h
 *
 * Created: 20/12/2012 11:59:59 PM
 *  Author: Michael a.k.a Mickey Mouse
 */ 


#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include "LCD.h"

// The size of the buffer we need to represent the LCD RAM
#define LCD_BUFFER_SIZE LCD_X * (LCD_Y / 8)
#define boxsize 14
 
// We declare the screen buffer here as extern, since it is defined in our C file.
// This way other files have will have direct access to the buffer if they include Graphics.h
extern unsigned char screenBuffer[LCD_BUFFER_SIZE];

void SetPixel(unsigned char x, unsigned char y, unsigned char value);
void DrawLine(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2);
void PresentBuffer(void);
void ClearBuffer(void);
void bufferCharacter(unsigned char x, unsigned char y, unsigned char character);
void bufferString(unsigned char x, unsigned char y, unsigned char *characetrs);

#endif /* GRAPHICS_H_ */