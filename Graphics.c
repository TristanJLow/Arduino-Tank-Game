#include <math.h>
#include "Graphics.h"
#include "LCD.h"
#include <util/delay.h> 
#define PI 3.14159265358979323846

//20/60

unsigned char screenBuffer[LCD_BUFFER_SIZE]; // Our screen buffer array

void SetPixel(unsigned char x, unsigned char y, unsigned char value){
	y = 48 - y;
	int bit = y%8;
	if (bit != 0) {
		int row = 84 * (y / 8) + x;
		screenBuffer[row] |= (value<<(bit-1));
	}
	else {
		int row = 84 * ((y / 8) - 1) + x;
		screenBuffer[row] |= (value<<7);
	}
	
}

void DrawLine(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2) {
	
}

void PresentBuffer(void) {
	LCDPosition(0,0);
	int i;
	for (i = 0; i <= 504; i++) {
		LCDWrite(LCD_D, screenBuffer[i]);
	}
}

void ClearBuffer(void) {
	int i;
		for (i = 0; i <= 504; i++) {
			screenBuffer[i] = 0x00;
		}
	}

void ClearBall(unsigned char x, unsigned char y){
	SetPixel(x,y,0);
	SetPixel(x+1,y,0);
	SetPixel(x,y+1,0);
	SetPixel(x+1,y+1,0);
	PresentBuffer();
}

void DrawBall(unsigned char x, unsigned char y){
	SetPixel(x,y,1);
	SetPixel(x+1,y,1);
	SetPixel(x,y+1,1);
	SetPixel(x+1,y+1,1);
	PresentBuffer();
}

char AngleLine(int angleInt){
	float angle = angleInt;
	float xx1 = 12.00;
	float yy1 = 9.00;
	float yy2;
	float xx2;
	
	angle = angle * (PI / 180.00);
	xx2 = 10 * cos(angle);
	yy2 = 10 * sin(angle);
	
	xx2 = xx1 + xx2;
	yy2 = yy1 + yy2;
	
	char y2;
	char x2;
	char x1 = 12;
 	char y1 = 9;

	x2 = xx2;
	y2 = yy2;
	
	char dx = abs(x2 - x1);
	char dy = abs(y2 - y1);
	char err = dx - dy;
	char sx;
	char sy;
	char e2;
	int i = 0;

	if(x1 < x2){
		sx = 1;
	} else {
		sx = -1;
	}
	if(y1 < y2){
		sy = 1;
	} else{
		sy = -1;
	}
	
	for (i = x1; i <= x2; i++) {
		SetPixel(x1, y1, 1);
		if (x1 == x2 && y1 == y2) {
			break;
		}
		e2 = 2 * err;
		if (e2 >-dy) {
			err = err - dy;
			x1 = x1 + sx;
		}
		if (e2 < dx) {
			err = err + dx;
			y1 = y1 + sy;
		}
	}
	for (i = y1; i < y2; i++) {
			SetPixel(x1, y1, 1);
			if (x1 == x2 && y1 == y2) {
				break;
			}
			e2 = 2 * err;
			if (e2 >-dy) {
				err = err - dy;
				x1 = x1 + sx;
			}
			if (e2 < dx) {
				err = err + dx;
				y1 = y1 + sy;
			}
		}
}

char EnemyLine(int angleInt){
		float angle = angleInt;
		float xx1 = 72.00;
		float yy1 = 9.00;
		float yy2;
		float xx2;
		
		angle = angle * (PI / 180.00);
		xx2 = 10 * cos(angle);
		yy2 = 10 * sin(angle);
		
		xx2 = (0 -xx2) + xx1 + 1;
		yy2 = yy1 + yy2;
		
		
		char y2;
		char x2;
		char x1 = 72;
	 	char y1 = 9;

		x2 = xx2;
		y2 = yy2;
		
		char dx = abs(x2 - x1);
		char dy = abs(y2 - y1);
		char err = dx - dy;
		char sx;
		char sy;
		char e2;
		int i = 0;

		if(x1 < x2){
			sx = 1;
		} else {
			sx = -1;
		}
		if(y1 < y2){
			sy = 1;
		} else{
			sy = -1;
		}
		
		for (i = x1; i >= x2; i--) {
			SetPixel(x1, y1, 1);
			if (x1 == x2 && y1 == y2) {
				break;
			}
			e2 = 2 * err;
			if (e2 >-dy) {
				err = err - dy;
				x1 = x1 + sx;
			}
			if (e2 < dx) {
				err = err + dx;
				y1 = y1 + sy;
			}
		}
		for (i = y1; i < y2; i++) {
				SetPixel(x1, y1, 1);
				if (x1 == x2 && y1 == y2) {
					break;
				}
				e2 = 2 * err;
				if (e2 >-dy) {
					err = err - dy;
					x1 = x1 + sx;
				}
				if (e2 < dx) {
					err = err + dx;
					y1 = y1 + sy;
				}
			}
}