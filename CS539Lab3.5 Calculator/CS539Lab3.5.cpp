/*Jee, Michael
CS 539 Lab 3
10/15/18
This program is a basic calculator that reads only positive integers and only allows addition, subtraction, multiplication, division, and modulus*/

#include "stdafx.h"
#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS

int calculate(char operate, int num1, int num2);
double dcalculate(int num1, int num2);
int calculateMult(int num1, int num2);
int calculateAdd(int num1, int num2);
int calculateSub(int num1, int num2);
double calculateDiv(int num1, int num2);
int calculateMod(int num1, int num2);
void output(int num1, int num2, char operate, double dfinal, int final);

int main(void)
{
	char iochar;
	int num1 = -1;
	int num2 = -1;
	char operate;
	int final = 0;
	double dfinal = 0;
	int numNum = 0;
	int numOps = 0;
	int numDig1 = 0;
	int numDig2 = 0;
	int lastChar = 0; //if last char was a number
	printf("Please enter your calculation using only two positive integers in the following format: num1+num2=: \n");
	do
	{
		while ((iochar = getchar()) && iochar != '=' && iochar != '\n' && iochar != 'z' && iochar != 'Z')
		{
			if ((iochar >= 48 && iochar <= 57) || iochar == 42 || iochar == 43 || iochar == 45 || iochar == 47 || iochar == 37 || iochar == 32 || iochar == 61 || iochar == 10)
			{
				if (iochar >= 48 && iochar <= 57)
				{
					if (!numNum)
					{
						if (numDig1 == 0)
						{
							num1 = iochar - '0';
						}
						else
						{
							num1 = num1 * 10 + iochar - '0';
						}
						numDig1++;
						lastChar = 1;
						/*printf("%d, %d, %d\n", num1, numDig1, numNum);*/
					}
					else if (numNum == 1)
					{
						if (numDig2 == 0)
						{
							num2 = iochar - '0';
						}
						else
						{
							num2 = num2 * 10 + iochar - '0';
						}
						numDig2++;
						lastChar = 1;
						/*printf("%d, %d, %d\n", num2, numDig2, numNum);*/
					}
				}
				else if (iochar == 42 || iochar == 43 || iochar == 45 || iochar == 47 || iochar == 37)
				{
					operate = iochar;
					numOps++;
					/*printf("%c\n", operate);*/
				}
				if ((iochar == 42 || iochar == 43 || iochar == 45 || iochar == 47 || iochar == 37 || iochar == 32) && lastChar)
				{
					numNum++;
					lastChar = 0;
				}
			}
			else
				printf("Error. Invalid characters.\n");
		}
		if (numOps > 1)
			printf("Error. Too many operators\n");
		if (numNum >= 2)
			printf("Error. Too many numbers.\n");
		if (iochar != 'Z' && iochar != 'z')
		{
			if (operate != '/')
			{
				final = calculate(operate, num1, num2);
			}
			else if (operate == '/')
			{
				dfinal = dcalculate(num1, num2);
			}
			output(num1, num2, operate, dfinal, final);
			printf("Enter z to exit. Next calculation: \n");
			numNum = 0;
			numDig1 = 0;
			numDig2 = 0;
			numOps = 0;
		}
	} while (iochar != 'z' && iochar != 'Z');
	return 0;
}

int calculateMult(int num1, int num2)
{
	return num1 * num2;
}

int calculateAdd(int num1, int num2)
{
	return num1 + num2;
}

int calculateSub(int num1, int num2)
{
	return num1 - num2;
}

double calculateDiv(int num1, int num2)
{
	return num1 / (num2 + 0.0);
}

int calculateMod(int num1, int num2)
{
	return num1 % num2;
}

int calculate(char operate, int num1, int num2)
{
	switch (operate)
	{
	case '*':
		return calculateMult(num1, num2);
	case '+':
		return calculateAdd(num1, num2);
	case '-':
		return calculateSub(num1, num2);
	case '%':
		return calculateMod(num1, num2);
	}
}

double dcalculate(int num1, int num2)
{
	return calculateDiv(num1, num2);
}
void output(int num1, int num2, char operate, double dfinal, int final)
{
	if (operate != '/')
		printf("%d %c %d = %d\n\n", num1, operate, num2, final);
	else if (operate == '/')
		printf("%d %c %d = %f\n\n", num1, operate, num2, dfinal);
}

/*
Please enter your calculation using only two positive integers in the followinkbg format: num1+num2=:
865 / 213 =
865 / 213 = 4.061033

Enter z to exit. Next calculation:
92 * 463 =
92 * 463 = 42596

Enter z to exit. Next calculation:
123- 789 =
123 - 789 = -666

Enter z to exit. Next calculation:
789-123 =
789 - 123 = 666

Enter z to exit. Next calculation:
65+5=
65 + 5 = 70

Enter z to exit. Next calculation:
496 % 56=
496 % 56 = 48

Enter z to exit. Next calculation:
8%2 =
8 % 2 = 0

Enter z to exit. Next calculation:
15 + - 30
Error. Too many operators
15 - -1 = 16

Enter z to exit. Next calculation:
15         +          30
15 + 30 = 45

Enter z to exit. Next calculation:
15 15 + 30
Error. Too many numbers.
15 + 15 = 30

Enter z to exit. Next calculation:
15+15 30
Error. Too many numbers.
15 + 15 = 30

Enter z to exit. Next calculation:
15 + 30 - 45
Error. Too many operators
Error. Too many numbers.
15 - 30 = -15

Enter z to exit. Next calculation:
z
Press any key to continue . . .
*/