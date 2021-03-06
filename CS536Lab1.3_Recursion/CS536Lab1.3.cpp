// Jee, Michael
// 2/21/19
// CS 536 Thurs Lab 1

#include "stdafx.h"
#include <iostream>
using namespace std;

double power(double x, int n);
double descSum(int n, int numFrac);
double ascSum(int n);
void fracIO(int & n);

int main()
{
	double x;
	int n = 1, numFrac = 0; //x is base, n is exponent for a or denominator for b and c
	char input;
	do
	{
		cout << "Hello. Please choose one of the following options: \n" //\n rather than endl to save resources
			<< "a. Raise a number to a power of itself. \n"
			<< "b. Add the first n terms of the series: 1+1/2+1/3+1/4...+1/n \n"
			<< "c. Add the first n terms of the series: 1/n...+1/4+1/3+1/2+1 \n"
			<< "d. Exit." << endl;
		cin >> input;
		switch (input)
		{
		case 'a': 
		case 'A':
		{
			cout << "Please enter the base number x: " << endl;
			cin >> x;
			cout << "Please enter the exponent n: " << endl;
			cin >> n;
			cout << "The result of " << x << " to the " << n << " power is: " << power(x, n) << "\n" << endl;
			break;
		}
		case 'b': 
		case 'B':
		{
			fracIO(n);
			numFrac = n;
			cout << descSum(n, numFrac) << endl;
			break;
		}
		case 'c':
		case 'C':
		{
			fracIO(n);
			cout << ascSum(n) << endl;
			break;
		}
		case 'd': //exits switch
		case 'D':
		{	
			cout << "Exiting." << endl;
			break;	
		}
		default: //error handling
		{
			input = 'e';
			cout << "Error. Please enter only a-d. \n" << endl;
		}
		}
		n = 1;
	} while (input != 'd' && input != 'D');
	system("pause");
	return 0;
}

double power(double x, int n)
{
	if (n == 0)
		return 1;
	else if (n == 1)
		return x;
	else if (n > 1)
		return x * power(x, n - 1);
	else
		return 1 / power(x, -n);
}

double descSum(int n, int numFrac)
{
	double temp;
	if (n == 1)
	{
		cout << "1";
		if (numFrac == 1)
			cout << "=";
		else
			cout << "+";
		return 1.0;
	}
	else
	{
		temp = 1.0 / n + descSum(n - 1, numFrac);
		cout << "1/" << n;
		if (n == numFrac)
			cout << "=";
		else
			cout << "+";
		return temp;
	}
}

double ascSum(int n)
{
	if (n == 1)
	{
		cout << "1=";
		return 1.0;
	}
	else
	{
		cout << "1/" << n << "+";
		return 1.0 / n + ascSum(n - 1);
	}
}

void fracIO(int & n)
{
	do
	{
		if (n < 1)
			cout << "Error. ";
		cout << "Please enter a positive number n: " << endl;
		cin >> n;
	} while (n < 1);
}

/*
Hello. Please choose one of the following options:
a. Raise a number to a power of itself.
b. Add the first n terms of the series: 1+1/2+1/3+1/4...+1/n
c. Add the first n terms of the series: 1/n...+1/4+1/3+1/2+1
d. Exit.
1
Error. Please enter only a-d.

Hello. Please choose one of the following options:
a. Raise a number to a power of itself.
b. Add the first n terms of the series: 1+1/2+1/3+1/4...+1/n
c. Add the first n terms of the series: 1/n...+1/4+1/3+1/2+1
d. Exit.
e
Error. Please enter only a-d.

Hello. Please choose one of the following options:
a. Raise a number to a power of itself.
b. Add the first n terms of the series: 1+1/2+1/3+1/4...+1/n
c. Add the first n terms of the series: 1/n...+1/4+1/3+1/2+1
d. Exit.
!
Error. Please enter only a-d.

Hello. Please choose one of the following options:
a. Raise a number to a power of itself.
b. Add the first n terms of the series: 1+1/2+1/3+1/4...+1/n
c. Add the first n terms of the series: 1/n...+1/4+1/3+1/2+1
d. Exit.
-4
Error. Please enter only a-d.

Hello. Please choose one of the following options:
a. Raise a number to a power of itself.
b. Add the first n terms of the series: 1+1/2+1/3+1/4...+1/n
c. Add the first n terms of the series: 1/n...+1/4+1/3+1/2+1
d. Exit.
a
Please enter the base number x:
2
Please enter the exponent n:
2
The result of 2 to the 2 power is: 4

Hello. Please choose one of the following options:
a. Raise a number to a power of itself.
b. Add the first n terms of the series: 1+1/2+1/3+1/4...+1/n
c. Add the first n terms of the series: 1/n...+1/4+1/3+1/2+1
d. Exit.
a
Please enter the base number x:
4
Please enter the exponent n:
-3
The result of 4 to the -3 power is: 0.015625

Hello. Please choose one of the following options:
a. Raise a number to a power of itself.
b. Add the first n terms of the series: 1+1/2+1/3+1/4...+1/n
c. Add the first n terms of the series: 1/n...+1/4+1/3+1/2+1
d. Exit.
a
Please enter the base number x:
7
Please enter the exponent n:
3
The result of 7 to the 3 power is: 343

Hello. Please choose one of the following options:
a. Raise a number to a power of itself.
b. Add the first n terms of the series: 1+1/2+1/3+1/4...+1/n
c. Add the first n terms of the series: 1/n...+1/4+1/3+1/2+1
d. Exit.
a
Please enter the base number x:
-9
Please enter the exponent n:
2
The result of -9 to the 2 power is: 81

Hello. Please choose one of the following options:
a. Raise a number to a power of itself.
b. Add the first n terms of the series: 1+1/2+1/3+1/4...+1/n
c. Add the first n terms of the series: 1/n...+1/4+1/3+1/2+1
d. Exit.
a
Please enter the base number x:
-9
Please enter the exponent n:
3
The result of -9 to the 3 power is: -729

Hello. Please choose one of the following options:
a. Raise a number to a power of itself.
b. Add the first n terms of the series: 1+1/2+1/3+1/4...+1/n
c. Add the first n terms of the series: 1/n...+1/4+1/3+1/2+1
d. Exit.
a
Please enter the base number x:
-4
Please enter the exponent n:
2
The result of -4 to the 2 power is: 16

Hello. Please choose one of the following options:
a. Raise a number to a power of itself.
b. Add the first n terms of the series: 1+1/2+1/3+1/4...+1/n
c. Add the first n terms of the series: 1/n...+1/4+1/3+1/2+1
d. Exit.
a
Please enter the base number x:
-4
Please enter the exponent n:
3
The result of -4 to the 3 power is: -64

Hello. Please choose one of the following options:
a. Raise a number to a power of itself.
b. Add the first n terms of the series: 1+1/2+1/3+1/4...+1/n
c. Add the first n terms of the series: 1/n...+1/4+1/3+1/2+1
d. Exit.
a
Please enter the base number x:
2
Please enter the exponent n:
0
The result of 2 to the 0 power is: 1

Hello. Please choose one of the following options:
a. Raise a number to a power of itself.
b. Add the first n terms of the series: 1+1/2+1/3+1/4...+1/n
c. Add the first n terms of the series: 1/n...+1/4+1/3+1/2+1
d. Exit.
a
Please enter the base number x:
0
Please enter the exponent n:
2
The result of 0 to the 2 power is: 0

Hello. Please choose one of the following options:
a. Raise a number to a power of itself.
b. Add the first n terms of the series: 1+1/2+1/3+1/4...+1/n
c. Add the first n terms of the series: 1/n...+1/4+1/3+1/2+1
d. Exit.
b
Please enter a positive number n:
-5
Error. Please enter a positive number n:
0
Error. Please enter a positive number n:
9
1+1/2+1/3+1/4+1/5+1/6+1/7+1/8+1/9+2.82897
Hello. Please choose one of the following options:
a. Raise a number to a power of itself.
b. Add the first n terms of the series: 1+1/2+1/3+1/4...+1/n
c. Add the first n terms of the series: 1/n...+1/4+1/3+1/2+1
d. Exit.
c
Please enter a positive number n:
-9
Error. Please enter a positive number n:
0
Error. Please enter a positive number n:
5
1/5+1/4+1/3+1/2+1=2.28333
Hello. Please choose one of the following options:
a. Raise a number to a power of itself.
b. Add the first n terms of the series: 1+1/2+1/3+1/4...+1/n
c. Add the first n terms of the series: 1/n...+1/4+1/3+1/2+1
d. Exit.
b
Please enter a positive number n:
1
1=1
Hello. Please choose one of the following options:
a. Raise a number to a power of itself.
b. Add the first n terms of the series: 1+1/2+1/3+1/4...+1/n
c. Add the first n terms of the series: 1/n...+1/4+1/3+1/2+1
d. Exit.
c
Please enter a positive number n:
1
1=1
Hello. Please choose one of the following options:
a. Raise a number to a power of itself.
b. Add the first n terms of the series: 1+1/2+1/3+1/4...+1/n
c. Add the first n terms of the series: 1/n...+1/4+1/3+1/2+1
d. Exit.
a
Please enter the base number x:
1.5
Please enter the exponent n:
2
The result of 1.5 to the 2 power is: 2.25

Hello. Please choose one of the following options:
a. Raise a number to a power of itself.
b. Add the first n terms of the series: 1+1/2+1/3+1/4...+1/n
c. Add the first n terms of the series: 1/n...+1/4+1/3+1/2+1
d. Exit.
a
Please enter the base number x:
3.3
Please enter the exponent n:
-5
The result of 3.3 to the -5 power is: 0.00255523

Hello. Please choose one of the following options:
a. Raise a number to a power of itself.
b. Add the first n terms of the series: 1+1/2+1/3+1/4...+1/n
c. Add the first n terms of the series: 1/n...+1/4+1/3+1/2+1
d. Exit.
a
Please enter the base number x:
8.1
Please enter the exponent n:
0
The result of 8.1 to the 0 power is: 1
Hello. Please choose one of the following options:
a. Raise a number to a power of itself.
b. Add the first n terms of the series: 1+1/2+1/3+1/4...+1/n
c. Add the first n terms of the series: 1/n...+1/4+1/3+1/2+1
d. Exit.
d
Press any key to continue . . .
*/