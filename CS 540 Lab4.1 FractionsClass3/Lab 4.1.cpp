// Michael Jee
// 10/29/18
// CS 540 Lab 4

#include"stdafx.h"
//#include "pch.h"
#include <iostream>
using namespace std;

//const int LARGEDIVIS = 10;

class fractions {
private:
	int who;
	int num;
	int den;
public:
	fractions(); //default constructor declaration
	fractions(int num, int den); //two argument constructor declaration
	fractions(int who, int num, int den); //three argument constructor declaration
	fractions(const fractions & copyThis); //copy constructor declaration; copies copyThis into the member

	~fractions(); //destructor declaration

	void setWho(int w); //mutator to set who to argument w
	void setNum(int n); //mutator to set num to argument n
	void setDen(int d);//mutator to set den to argument d

	int getWho() const; //accessor for wholes
	int getNum() const; //accessor for numerator
	int getDen() const; //accessor for denominator
	void print() const; //accessor to print

	fractions operator + (const fractions & temp) const;
	fractions operator * (const fractions & temp) const;
	bool operator == (const fractions & temp) const;
	fractions operator = (const fractions & temp);
friend ostream & operator << (ostream & cout, const fractions & temp);
friend istream & operator >> (istream & cin, fractions & temp);
};

//fractions simplify(const fractions & frac);

int main() {
	fractions fracA;
	fractions fracB;
	char cont;
	do
	{
		cout << "Please enter a positive fraction in the following format: whole numerator denominator: ";
		cin >> fracA;
		cout << "Please enter a second positive fraction in the following format: whole numerator denominator: ";
		cin >> fracB;
		cout << "Are fractions one and two equal? " << endl;
		fracA == fracB;
		cout << "\nSum: " << (fracA + fracB) << "Product: " << (fracA*fracB) << "Assigning the first faction to the second." << endl;
		fracB = fracA;
		cout << "The first fraction is: " << fracA << "The second fraction is: " << fracB << "Are fractions one and two equal? " << endl;
		fracA == fracB;
		cout << "\nContinue? (Y/N): ";
		cin >> cont;
	} while (cont == 'y' || cont == 'Y');
	//system("pause");
	return 0;
}

fractions::fractions() { //default constructor definition
	who = 0;
	num = 0;
	den = 1;
}
fractions::fractions(int num, int den) { //two argument constructor definition
	who = 0;
	setNum(num);
	setDen(den);
}
fractions::fractions(int who, int num, int den) { //three argument constructor definition
	setWho(who);
	setNum(num);
	setDen(den);
}
fractions::fractions(const fractions & copyThis) { //copy constructor definition
	*this = copyThis;
}
fractions::~fractions() { //destructor defintion
	who = 0;
	num = 0;
	den = 1;
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
fractions fractions::operator = (const fractions & temp)
{
	who = temp.who;
	num = temp.num;
	den = temp.den;
	return *this;
}
ostream & operator << (ostream & cout, const fractions & temp)
{
	//cout << temp.who << " " << temp.num << "/" << temp.den << endl;
	return cout << temp.who << " " << temp.num << "/" << temp.den << endl;
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
/*fractions simplify(const fractions & frac) //works always if you increment i up instead until i==num
{
	int wh = frac.getWho();
	int nu = frac.getNum();
	int de = frac.getDen();
	for (int i = LARGEDIVIS; i > 1; i--)
	{
		if (!((nu%i) || (de&i)))
		{
			nu /= i;
			de /= i;
		}
	}
	return fractions(wh, nu, de);
}*/

/*
Please enter a positive fraction in the following format: whole numerator denominator: 1 2 3
Please enter a second positive fraction in the following format: whole numerator denominator: 4 5 6
Are fractions one and two equal?
No
Sum: 6 1/2
Product: 8 1/18
Assigning the first faction to the second.
The first fraction is: 1 2/3
The second fraction is: 1 2/3
Are fractions one and two equal?
Yes

Continue? (Y/N): y
Please enter a positive fraction in the following format: whole numerator denominator: 1 2 3
Please enter a second positive fraction in the following format: whole numerator denominator: 1 2 3
Are fractions one and two equal?
Yes
Sum: 3 1/3
Product: 2 7/9
Assigning the first faction to the second.
The first fraction is: 1 2/3
The second fraction is: 1 2/3
Are fractions one and two equal?
Yes

Continue? (Y/N): Y
Please enter a positive fraction in the following format: whole numerator denominator: 1 2 3
Please enter a second positive fraction in the following format: whole numerator denominator: 1 4 6
Are fractions one and two equal?
Yes
Sum: 3 6/18
Product: 2 14/18
Assigning the first faction to the second.
The first fraction is: 1 2/3
The second fraction is: 1 2/3
Are fractions one and two equal?
Yes

Continue? (Y/N): Y
Please enter a positive fraction in the following format: whole numerator denominator: -1 -2 -3
Error. Only numbers greater than or equal to 0 allowed for the whole number.
Error. Only numbers greater than or equal to 0 allowed for the numerator.
Error. Only numbers greater than 0 allowed for the denominator.
Please re-enter your numbers: -1 -2 0
Error. Only numbers greater than or equal to 0 allowed for the whole number.
Error. Only numbers greater than or equal to 0 allowed for the numerator.
Error. Only numbers greater than 0 allowed for the denominator.
Please re-enter your numbers: 7 8 9
Please enter a second positive fraction in the following format: whole numerator denominator: -1 -2 -3
Error. Only numbers greater than or equal to 0 allowed for the whole number.
Error. Only numbers greater than or equal to 0 allowed for the numerator.
Error. Only numbers greater than 0 allowed for the denominator.
Please re-enter your numbers: -1 -2 0
Error. Only numbers greater than or equal to 0 allowed for the whole number.
Error. Only numbers greater than or equal to 0 allowed for the numerator.
Error. Only numbers greater than 0 allowed for the denominator.
Please re-enter your numbers: 11 22 33
Are fractions one and two equal?
No
Sum: 19 165/297
Product: 92 11/297
Assigning the first faction to the second.
The first fraction is: 7 8/9
The second fraction is: 7 8/9
Are fractions one and two equal?
Yes

Continue? (Y/N): n
Press any key to continue . . .
*/