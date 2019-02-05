#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#define PI 3.14159265358979323846

int main(int argc, char *argv[]) {
	float angle = 50.00;
	float power = 50.00;
	angle = angle * (PI / 180);
	float yy = 9.00;
	float xx = 12.00;
	float yV = power * sin(angle);
 	float xV = power * cos(angle);
	int i = 1;
	printf("\nYV =%f\nXV =%f\n", yV,xV);
	while (i < 400) {
		float t = i * 0.05;
		// s = ut + 1/2 at^2
		yy = yV * t + 0.50 * -9.70 * pow(t, 2);
		yy = yy + 9.00;
		xx = xV * -t + 0.50 * 0  * pow(t, 2);
		xx = xx + 12.00;
		i++;
		printf("\nY = %f\nX = %f\n", yy,xx);
	}
}

//char angle = 70;
//char x1 = 12;
//char y1 = 40;
//char x2; 
//char y2;
//
//angle = angle * (PI / 180);
//
//x2 = 8 * cos(angle);
//y2 = 8 * sin(angle);
//
//x2 = x2 + x1;
//y2 = y1 - y2;
//
//printf("X2 = %d \nY2 = %d",x2, y2);
//}

//float angle = 80;
//float xx1 = 72.00;
//float yy1 = 9.00;
//float yy2;
//float xx2;
//
//angle = angle * (PI / 180.00);
//xx2 = 10 * cos(angle);
//yy2 = 10 * sin(angle);
//
//xx2 = xx1 + xx2;
//yy2 = yy1 + yy2;
//
//char y2;
//char x2;
//char x1 = 72;
//	char y1 = 9;
//
//x2 = xx2;
//y2 = yy2;
//
//char dx = abs(x2 - x1);
//char dy = abs(y2 - y1);
//char err = dx - dy;
//char sx;
//char sy;
//char e2;
//int i = 0;
//
//if(x1 < x2){
//	sx = 1;
//} else {
//	sx = -1;
//}
//if(y1 < y2){
//	sy = 1;
//} else{
//	sy = -1;
//}
//
//for (i = x1; i > x2; i++) {
//	printf("X2 = %d \nY2 = %d\n",x2, y2);
//	if (x1 == x2 && y1 == y2) {
//		break;
//	}
//	e2 = 2 * err;
//	if (e2 >-dy) {
//		err = err - dy;
//		x1 = x1 - sx;
//	}
//	if (e2 < dx) {
//		err = err + dx;
//		y1 = y1 + sy;
//	}
//}
//for (i = y1; i < y2; i++) {
//		printf("X2 = %d \nY2 = %d\n",x2, y2);
//		if (x1 == x2 && y1 == y2) {
//			break;
//		}
//		e2 = 2 * err;
//		if (e2 >-dy) {
//			err = err - dy;
//			x1 = x1 - sx;
//		}
//		if (e2 < dx) {
//			err = err + dx;
//			y1 = y1 + sy;
//		}
//	}
//
//}