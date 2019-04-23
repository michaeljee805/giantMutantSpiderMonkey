/*Jee, Michael
9/23/18
CS 539 Lab 2*/

#include <stdio.h>
#pragma warning(disable:4996)
/*#include "pch.h"
#define _CRT_SECURE_NO_WARNINGS*/

/*
This program will take in a poem and output the words, one word per line without punctuation or spaces
*/

int main(void)
{
	char iochar;
	int space = 0;
	while ((iochar = getchar()) != EOF)
	{
		while ((iochar > 64 && iochar < 91) || (iochar > 96 && iochar < 123) || (iochar > 31 && iochar < 35) || (iochar > 38 && iochar < 42) || iochar == 44 || iochar == 46 || iochar == 58 || iochar == 59 || iochar == 10)
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

/*
cmd code: I:\>PierceCollege\CS539\CS539Lab2.6\Debug\CS539Lab2.6.exe<PierceCollege\CS539\CS539Lab2.6\Debug\TheParsnip.txt>PierceCollege\CS539\CS539Lab2.6\Debug\TheParsnipNew.txt
*/

/*
input:
The Parsnip


The parsnip,  children,  I repeat,
Is simply an anemic beet.
Some people call the parsnip edible;
Myself,  I find this claim incredible.

output:
The
Parsnip
The
parsnip
children
I
repeat
Is
simply
an
anemic
beet
Some
people
call
the
parsnip
edible
Myself
I
find
this
claim
incredible
*/