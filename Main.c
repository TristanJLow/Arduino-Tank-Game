#include <avr/io.h>
#include <util/delay.h> 
#include <math.h>
#include "LCD.h" 
#include "Graphics.h"
#include <avr/interrupt.h>
#define PI 3.14159265358979323846

// n9217126 - Tristan Low

void initialise();
void startScreen();
int gameScreen();
void gameOver(int winner);
int angleSelection();
int powerSelection(int angle);
int shoot(int power, int angle);
int enemyShoot();
void tanksDraw(int numTanks);
void terrainDraw();
void countdown(unsigned char *time);
void angleDraw(int angle);
void powerDraw(int power);
void initiateTime();

volatile int timeSeed = 0;

int main() {
	initialise();
	initiateTime();
	while(1) {
		startScreen();
		int winner = gameScreen();
		gameOver(winner);
	}// end while
}// end main

void initialise() {
	// sets LED0 and LED1 outputs and the rest of port b to inputs (including SW0 and SW1)
	DDRB = 0b00001100;
	// sets all b port pins to off/low voltage
	PORTB = 0b00000000;
	// initialises LCD with high contrast
	LCDInitialise(LCD_HIGH_CONTRAST);
	 
}// end initialise

void initiateTime() {
	TCCR0A |= 0b00000010;	

	TCCR0B |= 0b00000101;   

	TIMSK0 |= (1 << OCIE0A);

	OCR0A = 77; 
	sei(); 
}

ISR(TIMER0_COMPA_vect){
	timeSeed++;
	if(timeSeed >= 100){
		timeSeed = 0;
	}
}

int randInRange(int min, int max, int seed) {
	srand(seed);
	return rand()%(max-min) + min; 
}

void countdown(unsigned char *time) {
	ClearBuffer();
	terrainDraw();
	tanksDraw(1);
	PresentBuffer();
	LCDPosition(31, 2);
	LCDString(time);
	_delay_ms(1000);
}

void terrainDraw() { //redo from 5th row down with the buffer 
	int i;
	for (i = 0; i < 84; i = i + 2) {
		SetPixel(i,6,1);
		SetPixel(i,5,0);
		SetPixel(i,4,1);
		SetPixel(i,3,0);
		SetPixel(i,2,1);
		SetPixel(i,1,0);
		
		SetPixel(i + 1,6,1);
		SetPixel(i + 1,5,1);
		SetPixel(i + 1,4,0);
		SetPixel(i + 1,3,1);
		SetPixel(i + 1,0,0);
		SetPixel(i + 1,1,1);
	}// end for
}// end terrainDraw

void tanksDraw(int numTanks) {
	if (numTanks <= 2) {
		SetPixel(10,8,1);
		SetPixel(10,7,1);
		SetPixel(11,8,1);
		SetPixel(11,7,1);
		SetPixel(12,9,1);
		SetPixel(12,8,1);
		SetPixel(12,7,1);
		SetPixel(13,8,1);
		SetPixel(13,7,1);
		SetPixel(14,8,1);
		SetPixel(14,7,1);
	}
	
	if (numTanks >= 2) {
		SetPixel(70,8,1);
		SetPixel(70,7,1);
		SetPixel(71,8,1);
		SetPixel(71,7,1);
		SetPixel(72,8,1);
		SetPixel(72,7,1);
		SetPixel(72,9,1);
		SetPixel(73,8,1);
		SetPixel(73,7,1);
		SetPixel(74,8,1);
		SetPixel(74,7,1);
	}
}

void angleDraw(int angle) {
	LCDPosition(0,0);

	char charAngle[2];

	itoa(angle, charAngle, 10);
	
	ClearBuffer();
	terrainDraw();
	tanksDraw(2);
	AngleLine(angle);
	PresentBuffer();
	
	LCDString("ANGLE: ");
	LCDString(charAngle);
	LCDString("DEG");
}

void powerDraw(int power) {
	LCDPosition(0,1);
	LCDString("POWER: ");
	
	char charPower[3];

	itoa(power, charPower, 10);
		
	LCDString(charPower);
	LCDCharacter('%');
}

int angleSelection() {
	 
	ClearBuffer();
	terrainDraw();
	tanksDraw(2);
	PresentBuffer();
	
	int angle = 10;
	angleDraw(angle);
	while(1) {
		// reads the value of switch 0
		char SW0Value = (PINB>>0) & 1;
			
		// if the switch is being pressed do this
		if (SW0Value == 00000001) {
			_delay_ms(200);
			if (SW0Value == 00000001) {
				if (angle <= 75) {
					angle = angle + 5;
					
					angleDraw(angle);
				}
				else if (angle == 80) {
					angle = 10;
	
					angleDraw(angle);
				}
			}// end if
		}// end if
		
		// reads the value of switch 1
		char SW1Value = (PINB>>1) & 1;
				
		// if the switch is being pressed do this
		if (SW1Value == 00000001) {
			_delay_ms(200);
			if (SW1Value == 00000001) {
				return angle;
			}// end if
		}// end if 
	}// end while
}// end angleSelection

int powerSelection(int angle) {
	int power = 10;
	 
	ClearBuffer();
	tanksDraw(2);
	terrainDraw();
	PresentBuffer();
	
	angleDraw(angle);
	powerDraw(power);
	_delay_ms(100);
	while(1) {
		// reads the value of switch 0
		char SW0Value = (PINB>>0) & 1;
			
		// if the switch is being pressed do this
		if (SW0Value == 00000001) {
			_delay_ms(200);
			if (SW0Value == 00000001) {
				if (power <= 90) {
					power = power + 10;
					 
					ClearBuffer();
					terrainDraw();
					tanksDraw(2);
					PresentBuffer();
					
					angleDraw(angle);
					powerDraw(power);
				}
				else if (power == 100) {
					power = 10;
					 
					ClearBuffer();
					terrainDraw();
					tanksDraw(2);
					PresentBuffer();
					
					angleDraw(angle);
					powerDraw(power);
				}
			}// end if
		}// end if
		// reads the value of switch 1
		char SW1Value = (PINB>>1) & 1;
				
		// if the switch is being pressed do this
		if (SW1Value == 00000001) {
			_delay_ms(100);
			if (SW1Value == 00000001) {
				return power;
			}// end if
		}// end if 
	}// end while
}// end powerSelection

int shoot(int power, int angleInt) {
	float angle = angleInt;
	power = power / 2;
	unsigned char x = 12;
	unsigned char y = 9;
	unsigned char xPrev = 12;
	unsigned char yPrev = 9;
	float yy = 9.00;
	float xx = 12.00;
	int i = 1;
	angle = angle * (PI / 180.00);
	float yV = power * sin(angle);
 	float xV = power * cos(angle);
	
	while(1) {
		float t = i * 0.05;
		if ((xx >= 68.00 && xx <= 75.00) && (yy >= 7.00 && yy <= 9.00)) {

			return 1;
		}// end if
		if (xx > 83.00) {
			return 0;
		}
		if (yy <= 6.00 && yy >1.00) {
			return 0;
		}
		if (yy < 48.0) {
			ClearBuffer();
			terrainDraw();
			tanksDraw(2);
			DrawBall(xPrev,yPrev);
			DrawBall(x,y);
		}
		if (yy > 48.0) {
			ClearBuffer();
			terrainDraw();
			tanksDraw(2);
			PresentBuffer();
		}
		_delay_ms(25);
		xPrev = x;
		yPrev = y;
		yy = yV * t + 0.50 * -9.70 * pow(t, 2);
		yy = yy + 9.00;
		y = yy;
		xx = xV * t + 0.50 * 0 * pow(t, 2);
		xx = xx + 12.00;
		x  = xx;
		i++;
	}
}

int enemyShoot() {
	unsigned char x = 70;
	unsigned char y = 9;
	int power;
	int angleInt;
	power = (randInRange(1,10, timeSeed) * 10);
	angleInt = (randInRange(1,8, timeSeed)* 10);
	ClearBuffer();
	terrainDraw();
	tanksDraw(2);
	PresentBuffer();
	LCDPosition(6, 2); 
	LCDString("You Missed!");
	_delay_ms(2000);
	
	int intline;
	char charAngle[2];
	itoa(angleInt, charAngle, 10);
	char charPower[3];
	itoa(power, charPower, 10);
	
	for (intline = 10; intline <= angleInt; intline = intline + 5) {
		ClearBuffer();
		tanksDraw(2);
		terrainDraw();
		EnemyLine(intline);
		PresentBuffer();
			
		LCDPosition(7, 0); 
		LCDString("\"AIM ");
		LCDString(charAngle);
		LCDString("DEG\"");
		
		LCDPosition(0,1);
		LCDString(" \"");
		LCDString(charPower);
		LCDString("% POWER\"");
		_delay_ms(300);
	}
		
	_delay_ms(2000);
	
	float angle = angleInt;
	unsigned char xPrev = 12;
	unsigned char yPrev = 9;
	float yy = 9.00;
	float xx = 70.00;
	unsigned char i = 0;
	power = power / 2;
	angle = angle * (PI / 180.00);
	float yV = power * sin(angle);
 	float xV = power * cos(angle);		
		while(1) {
			float t = i * 0.05;
			if (xx >= 8.00 && xx <= 15.00 && yy >= 7.00 && yy <= 9.00) {

				return 2;
			}// end if
			if (xx < 0) {
				return 0;

			}
			if (yy <= 6.00 && yy >1.00) {
				return 0;

			}
			if (yy < 48.00) { 
				ClearBuffer();
				terrainDraw();
				tanksDraw(2);
				DrawBall(xPrev, yPrev);
				DrawBall(x,y);
			}
			if (yy > 48.0) {
				ClearBuffer();
				terrainDraw();
				tanksDraw(2);
				PresentBuffer();
			}
			_delay_ms(25);
			xPrev = x;
			yPrev = y;
			yy = yV * t + 0.50 * -9.70 * pow(t, 2);
			yy = yy + 9.00;
			y = yy;
			xx = xV * -t + 0.50 * 0 * pow(t, 2);
			xx = xx + 72.00;
			x  = xx;
			i++;
		}
}

void startScreen() {
	LCDClear();
	ClearBuffer();
	tanksDraw(1);
	terrainDraw();
	PresentBuffer();

	LCDPosition(14, 1); 
	LCDString("Scorched");
	LCDPosition(17, 2); 
	LCDString("Tristan");
	LCDPosition(14, 3); 
	LCDString("n9217126");
	
	
	// infinite loop to wait for button press
	while(1) {
		// reads the value of switch 0
		char SW0Value = (PINB>>0) & 1;
			
		// if the switch is being pressed do this
		if (SW0Value == 00000001) {
			break;
		}// end if
		
		// reads the value of switch 1
		char SW1Value = (PINB>>1) & 1;
				
		// if the switch is being pressed do this
		if (SW1Value == 00000001) {
			break;
		}// end if 
	}// end while
	
	countdown("-3-");
	countdown("-2-");
	countdown("-1-");
}// end startScreen

int gameScreen() {
	int winner = 0;
	while (winner == 0) {
		int angle = angleSelection();
		int power = powerSelection(angle);
		winner = shoot(power, angle);
		if (winner == 0) {
			winner = enemyShoot();
		}
		if (winner == 0) {
			ClearBuffer();
			tanksDraw(2);
			terrainDraw();
			PresentBuffer();
			LCDPosition(9, 2); 
			LCDString("Try Again!");
			_delay_ms(2000);
		}
	}
	return winner;

}// end gameScreen

void gameOver(int winner) {
	if (winner == 1) {
		ClearBuffer();
		tanksDraw(1);
		terrainDraw();
		PresentBuffer();

		LCDPosition(11, 2); 
		LCDString("You Won!!");
		PORTB ^= (1<<2);
		_delay_ms(200);
		PORTB ^= (1<<2);
		PORTB ^= (1<<3);
		_delay_ms(200);
		PORTB ^= (1<<2);
		PORTB ^= (1<<3);
		LCDPosition(11, 1); 
		_delay_ms(200);
		PORTB ^= (1<<2);
		PORTB ^= (1<<3);
		_delay_ms(200);
		PORTB ^= (1<<2);
		PORTB ^= (1<<3);
		_delay_ms(200);
		PORTB ^= (1<<2);
	}
	if (winner == 2) {
		ClearBuffer();
		terrainDraw();
		tanksDraw(3);
		PresentBuffer();

		LCDPosition(11, 2); 
		LCDString("You Lose!");
		PORTB ^= (1<<2);
		_delay_ms(200);
		PORTB ^= (1<<2);
		PORTB ^= (1<<3);
		_delay_ms(200);
		PORTB ^= (1<<2);
		PORTB ^= (1<<3);
		_delay_ms(200);
		PORTB ^= (1<<2);
		PORTB ^= (1<<3);
		_delay_ms(200);
		PORTB ^= (1<<2);
		PORTB ^= (1<<3);
		_delay_ms(200);
		PORTB ^= (1<<2);
	}
	_delay_ms(2000);
}// end gameOver