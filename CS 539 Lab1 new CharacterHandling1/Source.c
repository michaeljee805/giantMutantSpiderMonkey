#include "stdafx.h"
#include "stdio.h"
//#include "pch.h"
#include <math.h>
#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS

/* problem with *c and/or *%s
math broken
while loops broken */

int main(void) {
	char repeat;
	int side1, side2, side3;
	float calcTemp;
	float area;
	do {
		printf("This program will determine if the sides of a triangle are valid, the type of triangle, and the area of the triangle. \n");
		printf("Please enter the lengths of the sides of the triangle: ");
		scanf("%d %d %d", &side1, &side2, &side3);
		while (side1 + side2 <= side3 || side2 + side3 <= side1 || side1 + side3 <= side2) {
			printf("Error. The sum of any two sides of a triangle must be greater than the third. Please re-enter the sides: \n");
			printf("Please re-enter the sides of the triangle: ");
			scanf("%d %d %d", &side1, &side2, &side3);
		}
		printf("You entered: %d %d %d \n", side1, side2, side3);
		if (side1 == side2 == side3)
			printf("The triangle is equilateral.\n");
		else if (side1 == side2 || side1 == side3 || side2 == side3)
			printf("The triangle is isosceles.\n");
		else
			printf("The triangle is scalene.\n");
		calcTemp = side1 + side2 + side3;
		printf("%d", calcTemp);
		calcTemp /= 2.0;
		printf("%d", calcTemp);
		area = sqrt(calcTemp * (calcTemp - side1) * (calcTemp - side2) * (calcTemp - side3));
		printf("The area of the triangle is: %d. \n", area);
		printf("Would you like to continue? (Y/N): ");
		scanf("%c", &repeat);
		while (repeat != 'Y' || repeat != 'y' || repeat != 'N' || repeat != 'n') {
			printf("Error. Please enter Y or N: ");
			scanf("%c", &repeat);
		}
	} while (repeat == 'Y' || repeat == 'y');
	return 0;
}
