// Michael Jee
// 11/7/18
// CS 540 Lab 5

#include"stdafx.h"
//#include "pch.h"
#include <iostream>
#include <iomanip>
using namespace std;

//test functions
//test deallocating on fail

class fractions
{
private:
	int who;
	int num;
	int den;
	static int count;

public:
	fractions(); //default constructor declaration
	fractions(int num, int den); //two argument constructor declaration
	fractions(int who, int num, int den); //three argument constructor declaration
	fractions(const fractions & copyThis); //copy constructor declaration; copies copyThis into the member
	~fractions(); //destructor declaration

	void setWho(int w); //mutator to set who to argument w
	void setNum(int n); //mutator to set num to argument n
	void setDen(int d);//mutator to set den to argument d
	
	static int getCount() { return count; }//accessor for counting fractions
	int getWho() const; //accessor for wholes
	int getNum() const; //accessor for numerator
	int getDen() const; //accessor for denominator
	void print() const; //accessor to print

	fractions operator + (const fractions & temp) const;
	fractions operator * (const fractions & temp) const;
	bool operator == (const fractions & temp) const;
	fractions & operator = (const fractions & temp);
	friend ostream & operator << (ostream & cout, const fractions & temp);
	friend istream & operator >> (istream & cin, fractions & temp);
};

int input();
void allocate(int userD, bool & error1, bool & error2, bool & error3, fractions *** & ptemp);
void setValue(int userD, fractions *** & ptemp);
void output(int userD, fractions *** & ptemp);
void deallocate(int userD, fractions *** & ptemp);
char contin();

int main()
{
	char cont;
	int userD;
	bool error1 = false;
	bool error2 = false;
	bool error3 = false;
	fractions ***ptemp = nullptr;
	do
	{
		userD = input();
		allocate(userD, error1, error2, error3, ptemp);
		if (!error1 && !error2 && !error3)
		{
			setValue(userD, ptemp);
			output(userD, ptemp);
			deallocate(userD, ptemp);
		}
		else
		{
			cout << "Error. ";
			error1 = false;
			error2 = false;
			error3 = false;
		}
		cont = contin();
	} while (cont == 'y' || cont == 'Y');
	system("pause");
	return 0;
}

int fractions::count = 0;

fractions::fractions() { //default constructor definition
	who = 0;
	num = 0;
	den = 1;
	count++;
}
fractions::fractions(int num, int den) { //two argument constructor definition
	who = 0;
	setNum(num);
	setDen(den);
	count++;
}
fractions::fractions(int who, int num, int den) { //three argument constructor definition
	setWho(who);
	setNum(num);
	setDen(den);
	count++;
}
fractions::fractions(const fractions & copyThis) { //copy constructor definition
	*this = copyThis;
	count++;
}
fractions::~fractions() { //destructor defintion
who = 0;
num = 0;
den = 1;
count--;
}

void fractions::setWho(int w) { //mutator for wholes
	who = w;
	if (who < 0) {
		who = 0;
		cout << "Error. Only numbers greater than or equal to 0 allowed for the whole number." << endl;
	}
}
void fractions::setNum(int n) { //mutator for numerators
	num = n;
	if (num < 0) {
		num = 0;
		cout << "Error. Only numbers greater than or equal to 0 allowed for the numerator." << endl;
	}
}
void fractions::setDen(int d) { //mutator for denominators
	den = d;
	if (den <= 0) {
		den = 1;
		cout << "Error. Only numbers greater than 0 allowed for the denominator." << endl;
	}
}
int fractions::getWho() const { //accessor for wholes
	return who;
}
int fractions::getNum() const { //accessor for numerators
	return num;
}
int fractions::getDen() const { //accessor for denominators
	return den;
}
void fractions::print() const {
	cout << getWho() << " " << getNum() << "/" << getDen() << endl;
}

fractions fractions::operator + (const fractions & temp) const
{
	int wh = 0, nu = 0, de = 1;
	wh = who + temp.who;
	if (den != temp.den) //converting to common denominator
	{
		nu = (num*temp.den + temp.num*den);
		de = den * temp.den;
	}
	else
	{
		nu = num + temp.num;
		de = den;
	}
	if (nu > de)//converting to wholes
	{
		wh += nu / de;
		nu %= de;

	}
	return fractions(wh, nu, de);
}
fractions fractions::operator * (const fractions & temp) const
{
	int wh = 0, nu = 0, de = 1;
	if (who != 0 || temp.who != 0)//converting wholes to improper fractions
		nu = (num + who * den)*(temp.num + temp.who*temp.den);
	else
		nu = num * temp.num;
	de = den * temp.den;
	if (nu > de)//converting to wholes
	{
		wh = nu / de;
		nu %= de;
	}
	return fractions(wh, nu, de);
}
bool fractions::operator == (const fractions & temp) const
{
	int nu1, nu2;
	nu1 = (who * den + num)*temp.den;
	nu2 = (temp.who*temp.den + temp.num)*den;
	if (nu1 == nu2)
		cout << "yes";
	else
		cout << "no";
	return (nu1 == nu2) ? true : false;
}
fractions & fractions::operator = (const fractions & temp)
{
	who = temp.who;
	num = temp.num;
	den = temp.den;
	return *this;
}
ostream & operator << (ostream & cout, const fractions & temp)
{
	return cout << temp.num << "/" << temp.den;
}
istream & operator >> (istream & cin, fractions & temp)
{
	do
	{
		cin >> temp.who >> temp.num >> temp.den;
		if (temp.who < 0)
			cout << "Error. Only numbers greater than or equal to 0 allowed for the whole number." << endl;
		if (temp.num < 0)
			cout << "Error. Only numbers greater than or equal to 0 allowed for the numerator." << endl;
		if (temp.den <= 0)
			cout << "Error. Only numbers greater than 0 allowed for the denominator." << endl;
		if (temp.who < 0 || temp.num < 0 || temp.den <= 0)
			cout << "Please re-enter your numbers: ";
	} while (temp.who < 0 || temp.num < 0 || temp.den <= 0);
	return cin;
}

int input()
{
	int userD;
	do
	{
		cout << "Please enter a positive denominator and I will return the products of all combinations of two fractions with that denominator between 0 and 1: ";
		cin >> userD;
	} while (userD < 1);
	return userD;
}

void allocate(int userD, bool & error1, bool & error2, bool & error3, fractions *** & ptemp)
{
	ptemp = new (nothrow) (fractions**[userD]); //allocate pointer to 2d array
	if (ptemp == nullptr)
	{
		cout << "Memory allocation failed (rows)." << endl;
		error1 = true;
	}
	if (!error1)
	{
		for (int i = 0; i < userD; i++) //allocate columns
		{
			ptemp[i] = new (nothrow) (fractions*[userD]);
			if (ptemp[i] == nullptr)
			{
				cout << "Memory allocation failed (columns)." << endl;
				error2 = true;
				for (i; i >= 0; i--)
				{
					delete[] ptemp[i];
					ptemp[i] = nullptr;
				}
				delete[] ptemp;
				ptemp = nullptr;
				i = userD; //ends outer loop
			}
		}
	}
	if (!error1 && !error2)
	{
		for (int i = 0; i < userD; i++) //allocate fractions
		{
			for (int j = 0; j < userD; j++)
			{
				ptemp[i][j] = new (nothrow) (fractions);
				if (ptemp[i][j] == nullptr)
				{
					cout << "Memory allocation failed (fractions)." << endl;
					error3 = true;
					for (i; i >= 0; i--)
					{
						for (int k = j; k >= 0; k--)
						{
							delete ptemp[i][k];
							ptemp[i][k] = nullptr;
						}
						delete[] ptemp[i];
						ptemp[i] = nullptr;
					}
					delete[] ptemp;
					ptemp = nullptr;
					j = userD; //ends 2nd loop
					i = userD; //ends 1st loop
				}
			}
		}
	}
}

void setValue(int userD, fractions *** & ptemp)
{
	for (int i = 0; i < userD; i++) //set values for column and row headers
	{
		fractions temp(i, userD);
		*ptemp[i][0] = temp;
		*ptemp[0][i] = temp;
	}
	for (int i = 1; i < userD; i++) //set values for fraction combos
	{
		for (int j = 1; j < userD; j++)
		{
			*ptemp[i][j] = (*ptemp[i][0]) * (*ptemp[0][j]);
		}
	}
}

void output(int userD, fractions *** & ptemp)
{
	int digits = userD / 10 + 5;
	for (int i = 0; i < userD; i++) //output first row
	{
		if (i)
			cout << setw(digits + 1) << *ptemp[0][i]; //extra space for after 0th
		else
			cout << setw(digits) << *ptemp[0][i];
	}
	cout << "\n";
	for (int i = 1; i < userD; i++) //output rest of table
	{
		for (int j = 0; j < userD; j++)
		{
			cout << setw(digits) << right << *ptemp[i][j];
		}
		cout << endl;
	}
	cout << "count " << fractions::getCount() << endl;
}

void deallocate(int userD, fractions *** & ptemp)
{
	for (int i = 0; i < userD; i++)
	{
		for (int j = 0; j < userD; j++)
		{
			delete ptemp[i][j];
			ptemp[i][j] = nullptr;
		}
		delete[] ptemp[i];
		ptemp[i] = nullptr;
	}
	delete[] ptemp;
	ptemp = nullptr;
}

char contin()
{
	char cont;
	do
	{
		cout << "\nContinue? (Y/N): ";
		cin.clear();
		cin.ignore(100, '\n');
		cin >> cont;
	} while (cont != 'y' && cont != 'Y' && cont != 'n' && cont != 'N');
	return cont;
}

/*
Please enter a positive denominator and I will return the products of all combinations of two fractions with that denominator between 0 and 1: 5
0/5     1/5     2/5     3/5     4/5
1/5    1/25    2/25    3/25    4/25
2/5    2/25    4/25    6/25    8/25
3/5    3/25    6/25    9/25   12/25
4/5    4/25    8/25   12/25   16/25
count 25

Continue? (Y/N): y
Please enter a positive denominator and I will return the products of all combinations of two fractions with that denominator between 0 and 1: 8
0/8     1/8     2/8     3/8     4/8     5/8     6/8     7/8
1/8    1/64    2/64    3/64    4/64    5/64    6/64    7/64
2/8    2/64    4/64    6/64    8/64   10/64   12/64   14/64
3/8    3/64    6/64    9/64   12/64   15/64   18/64   21/64
4/8    4/64    8/64   12/64   16/64   20/64   24/64   28/64
5/8    5/64   10/64   15/64   20/64   25/64   30/64   35/64
6/8    6/64   12/64   18/64   24/64   30/64   36/64   42/64
7/8    7/64   14/64   21/64   28/64   35/64   42/64   49/64
count 64

Continue? (Y/N): y
Please enter a positive denominator and I will return the products of all combinations of two fractions with that denominator between 0 and 1: 10000
Memory allocation failed (fractions).
Error.
Continue? (Y/N): y
Please enter a positive denominator and I will return the products of all combinations of two fractions with that denominator between 0 and 1: 100000
Memory allocation failed (columns).
Error.
Continue? (Y/N): y
Please enter a positive denominator and I will return the products of all combinations of two fractions with that denominator between 0 and 1: 8
0/8     1/8     2/8     3/8     4/8     5/8     6/8     7/8
1/8    1/64    2/64    3/64    4/64    5/64    6/64    7/64
2/8    2/64    4/64    6/64    8/64   10/64   12/64   14/64
3/8    3/64    6/64    9/64   12/64   15/64   18/64   21/64
4/8    4/64    8/64   12/64   16/64   20/64   24/64   28/64
5/8    5/64   10/64   15/64   20/64   25/64   30/64   35/64
6/8    6/64   12/64   18/64   24/64   30/64   36/64   42/64
7/8    7/64   14/64   21/64   28/64   35/64   42/64   49/64
count 64

Continue? (Y/N): n
Press any key to continue . . .
*/