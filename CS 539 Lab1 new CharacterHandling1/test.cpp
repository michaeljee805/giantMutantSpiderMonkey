//Michael Jee
//9/23/18
//CS 539

#include "stdafx.h"
#include <stdio.h>
//#include "pch.h"
#include <iostream>
#pragma warning(disable:4996)
//#define _CRT_SECURE_NO_WARNINGS

int main(void)
{
	char iochar;
	int space = 0;
	printf("Please enter your text here: ");
	while ((iochar = getchar()) != EOF)
	{
		while ((iochar > 64 && iochar < 91) || (iochar > 96 && iochar < 123) || (iochar > 31 && iochar < 35) || (iochar > 38 && iochar < 42) || iochar == 44 || iochar == 46 || iochar == 58 || iochar == 59)
		{
			if ((iochar > 64 && iochar < 91) || (iochar > 96 && iochar < 123))
			{
				putchar(iochar);
				space = 0;
			}
			else if ((iochar == 32 || iochar == 10) && space == 0)
			{
				putchar('\n');
				space = 1;
			}
			iochar = getchar();
		}
	}
	return 0;
}