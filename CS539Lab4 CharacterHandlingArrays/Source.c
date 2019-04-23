/*Jee, Michael
CS 539 Lab 4
10/22/18
This program will: 1. generate a random pattern of uppercase letters, 2. allow the user to enter 2 to 20 characters and a replacement character, 
3. replace any characters from 2. that match 1. with the replacement character, 4. output the original string, user entered string, and new string*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#define ORIGSIZE 41
#define USERSIZE 21
#define MAXSIZE 1000

void genOrig(char origArr[], char newArr[]);
int userInput(char userArr[]);
char repChar();
void replaceChar(char newArr[], char userArr[], int num, char replace);
void output(const char origArr[], const char userArr[], char replace, const char newArr[]);
void reset(char userArr[]);
void resetAll(char userArr[], char newArr[], const char origArr[], int num);

int main(void)
{
	char origArr[ORIGSIZE];
	char userArr[USERSIZE] = { '\0' };
	char newArr[ORIGSIZE]; //copy for original array for output
	char replace;
	int num;
	char cont;
	genOrig(origArr, newArr);
	do
	{
		num = userInput(userArr);
		replace = repChar();
		replaceChar(newArr, userArr, num, replace);
		output(origArr, userArr, replace, newArr);
		printf("\nWould you like to do this again? (Y/N): ");
		reset(userArr, newArr, origArr, num);
		cont = getchar();
		getchar();
	} while (cont == 'y' || cont == 'Y');
	system("pause");
	return 0;
}

void genOrig(char origArr[], char newArr[])
{
	for (int i = 0; i < ORIGSIZE; i++) //creates random string of characters of size ORIGSIZE
	{
		if (i != ORIGSIZE - 1)
		origArr[i] = rand() % 26 + 'A';
		else
			origArr[ORIGSIZE - 1] = '\0';
	}
	for (int i = 0; i < ORIGSIZE; i++) //copies origArr into newArr
	{
		newArr[i] = origArr[i];
	}
}

int userInput(char userArr[])
{
	char iochar;
	int num = 0;
	int error1 = 0;
	int error2 = 0;
	printf("Please enter a string of uppercase letters between 2 and 20 characters without spaces: ");
	gets(userArr, MAXSIZE); //obtain user's string
	num = strlen(userArr);
	do
	{
		if (error1 || error2) //checking error flag
		{
			printf("Error. Please enter a string of uppercase letters between 2 and 20 characters without spaces: ");
			reset(userArr);
			gets(userArr, MAXSIZE);
			num = strlen(userArr);
		}
		if (num < 2 || num > 20) //checking size of string
		{
			error1 = 1;
		}
		else
			error1 = 0;
		for (int i = 0; i < num; i++)
		{
			if (*(userArr + i) < 'A' || *(userArr + i) > 'Z') //checking if capital letters
			{
				error2 = 1;
			}
			else
				error2 = 0;
		}
	} while (error1 || error2);
	return num;
}

char repChar()
{
	char iochar;
	char tempChar = '\0';
	int num = 0;
	printf("\nPlease enter the replacement character: ");
	do
	{
		if (num > 1) //checking replacement character
			printf("Error. Please only enter one replacement character. Last entered character used.\n");
		tempChar = getchar();
		if (tempChar != '\n')
		{
			iochar = tempChar;
			num++;
		}
	} while (tempChar != EOF && tempChar != '\n');
	if (num > 1)
		printf("Error. Please only enter one replacement character.\n");
	return iochar;
}

void replaceChar(char newArr[], char userArr[], int num, char replace)
{
	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < ORIGSIZE; j++) //replaing characters
		{
			if (userArr[i] == newArr[j])
				newArr[j] = replace;
		}
	}
}

void output(const char origArr[], const char userArr[], char replace, const char newArr[])
{
	printf("\nThe original array was: ");
	puts(origArr);
	printf("\nYour string was: ");
	puts(userArr);
	printf("\nYour replace character was: ");
	putchar(replace);
	printf("\n\nThe new string is: ");
	puts(newArr);
}

void reset(char userArr[])
{
	for (int i = 0; i < USERSIZE; i++)
	{
		userArr[i] = '\0';
	}
}

void resetAll(char userArr[], char newArr[], const char origArr[], int num)
{
	for (int i = 0; i < ORIGSIZE; i++) //reset copy of original array
	{
		newArr[i] = origArr[i];
	}
	for (int i = 0; i < num; i++) //zero out user's array
	{
		userArr[i] = '\0';
	}
}

/*
Please enter a string of uppercase letters between 2 and 20 characters without spaces:
Error. Please enter a string of uppercase letters between 2 and 20 characters without spaces: 1
Error. Please enter a string of uppercase letters between 2 and 20 characters without spaces: asdf
Error. Please enter a string of uppercase letters between 2 and 20 characters without spaces: ASDFASDFASDFASDFASDFSADFASDF
Error. Please enter a string of uppercase letters between 2 and 20 characters without spaces: ';\
Error. Please enter a string of uppercase letters between 2 and 20 characters without spaces: ASDF

Please enter the replacement character: 1*
Error. Please only enter one replacement character. Last entered character used.

The original array was: PHQGHUMEAYLNLFDXFIRCVSCXGGBWKFNQDUXWFNFO

Your string was: ASDF

Your replace character was: *

The new string is: PHQGHUME*YLNL**X*IRCV*CXGGBWK*NQ*UXW*N*O

Would you like to do this again? (Y/N): y
Please enter a string of uppercase letters between 2 and 20 characters without spaces: Q
Error. Please enter a string of uppercase letters between 2 and 20 characters without spaces: QWERTY

Please enter the replacement character: z

The original array was: PHQGHUMEAYLNLFDXFIRCVSCXGGBWKFNQDUXWFNFO

Your string was: QWERTY

Your replace character was: z

The new string is: PHzGHUMzAzLNLFDXFIzCVSCXGGBzKFNzDUXzFNFO

Would you like to do this again? (Y/N): n
Press any key to continue . . .
*/