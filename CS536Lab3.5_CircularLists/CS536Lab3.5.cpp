//Jee, Michael
//3/4/19
//CS 536 Lab 3

//#include "pch.h"
#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

class person
{
private:
	string name;
	int num;
	static int total;

public:
	person() { name = "aaa", ++total, num = total; }
	person(string nam) { name = nam, ++total, num = total; }
	~person() { --total; }

	string getName() const { return name; }
	int getNum() const { return num; }
	int getTotal() const { return total; }

	void setName(string temp) { name = temp; }
};

int person::total = 0;

class node
{
private:
	node * next;
	node * prev;
	person people;

public:
	node() { next = nullptr, prev = nullptr; }
	~node() {}

	node * getNext() const { return next; }
	node * getPrev() const { return prev; }
	string getName() const { return people.getName(); }
	int getNum() const { return people.getNum(); }
	int getTotal() const { return people.getTotal(); }

	void setNext(node * temp) { next = temp; }
	void setPrev(node * temp) { prev = temp; }
	void setName(string temp) { people.setName(temp); }
};

class LinkedList
{
private:
	node * leadptr;
public:
	void input(int & total, int & npass); //user input to obtain names from a list, total number of people, number of passes, calls add()
	//precondition: enough memory exists for a string and ifstream
	//postconditions: total>0, npass>=0, infile closed, add executed
	void add(int total, ifstream & infile); //dynamically allocate people equalling total number user input
	//precondition: valid infile, total>0, enough memory exists for a node pointer, string, and nodes equalling total
	//postconditions: leadptr->getTotal()==total, circular list is created and filled with names and numbers of people totalling total
	void output(int & total, int npass); //print each eliminated member then deallocate them, print the winnder then deallocate
	//precondition: list has at least one person, total>0, npass>=0, enough memory for a node pointer
	//postcondition: list is empty
};

int main()
{
	int total = 1, npass = 0; //npass is number of passes
	char cont;
	LinkedList list;
	do
	{
		list.input(total, npass);
		list.output(total, npass);
		cout << "Continue? (Y/N)";
		cin >> cont;
		cont = toupper(cont);
	} while (cont != 'N');

	return 0;
}

void LinkedList::input(int & total, int & npass)
{
	string fileName;
	ifstream infile;
	cout << "Please enter the file name: ";
	cin >> fileName;
	infile.open(fileName);
	if (!infile)
	{
		cout << "Error opening infile." << endl;
		exit(1);
	}
	do
	{
		if (total <= 0)
			cout << "Error. ";
		cout << "Please enter the number of people: ";
		cin >> total;
	} while (total <= 0);
	do
	{
		if (npass < 0)
			cout << "Error. ";
		cout << "Please enter the number of passes: ";
		cin >> npass;
	} while (npass < 0);
	add(total, infile);
	infile.close();
}

void LinkedList::add(int total, ifstream & infile)
{
	string temp;
	infile >> temp;
	do
	{
		node *ptemp = new (nothrow) node;
		if (ptemp == nullptr)
		{
			cout << "Error. Not enough memory. Exiting " << endl;
			exit(1);
		}
		if (leadptr->getTotal() == 1)
		{
			leadptr = ptemp;
			leadptr->setPrev(ptemp);
			leadptr->setNext(ptemp);
		}
		else
		{
			ptemp->setPrev(leadptr->getPrev());
			ptemp->setNext(leadptr);
			(leadptr->getPrev())->setNext(ptemp);
			leadptr->setPrev(ptemp);

		}
		ptemp->setName(temp);
		infile >> temp;
		ptemp = nullptr;
	} while (!infile.eof() && leadptr->getTotal() < total);
	cout << "File processing completed\n" << endl;
}

void LinkedList::output(int & total, int npass)
{
	node * ptemp;
	if (total != 1)
	{
		do
		{
			for (int i = 0; i < npass; ++i)
				leadptr = leadptr->getNext();
			--total;
			cout << "person eliminated: " << setw(3) << leadptr->getName() << " | number: " << setw(3) << leadptr->getNum() << " | remaining: " << leadptr->getTotal() << endl;
			(leadptr->getPrev())->setNext(leadptr->getNext());
			(leadptr->getNext())->setPrev(leadptr->getPrev());
			ptemp = leadptr->getNext();
			delete leadptr;
			leadptr = ptemp;
			ptemp = nullptr;
		} while (total != 1);
	}
	cout << "winner:            " << setw(3) << leadptr->getName() << " | " << "number: " << setw(3) << leadptr->getNum() << endl;
	delete leadptr;
	leadptr = nullptr;
}

/*
Please enter the file name: a
Error opening infile.

E:\PierceCollege\0_current_term\CS536\CS536Lab3.5\Debug\CS536Lab3.5.exe (process 14560) exited with code 1.
To automatically close the console when debugging stops, enable Tools->Options->Debugging->Automatically close the console when debugging stops.
Press any key to close this window . . .


Please enter the file name: infile.txt
Please enter the number of people: 1
Please enter the number of passes: 1
File processing completed

winner:             A1 | number:   1
Continue? (Y/N)y
Please enter the file name: infile.txt
Please enter the number of people: 9
Please enter the number of passes: 03
File processing completed

person eliminated:  D1 | number:   4 | remaining: 9
person eliminated:  H1 | number:   8 | remaining: 8
person eliminated:  C1 | number:   3 | remaining: 7
person eliminated:  I1 | number:   9 | remaining: 6
person eliminated:  F1 | number:   6 | remaining: 5
person eliminated:  E1 | number:   5 | remaining: 4
person eliminated:  G1 | number:   7 | remaining: 3
person eliminated:  B1 | number:   2 | remaining: 2
winner:             A1 | number:   1
Continue? (Y/N)y
Please enter the file name: infile.txt
Please enter the number of people: 1
Please enter the number of passes: 3
File processing completed

winner:             A1 | number:   1
Continue? (Y/N)y
Please enter the file name: infile.txt
Please enter the number of people: 3
Please enter the number of passes: 1
File processing completed

person eliminated:  B1 | number:   2 | remaining: 3
person eliminated:  A1 | number:   1 | remaining: 2
winner:             C1 | number:   3
Continue? (Y/N)y
Please enter the file name: infile.txt
Please enter the number of people: 0
Error. Please enter the number of people: 5
Please enter the number of passes: 8
File processing completed

person eliminated:  D1 | number:   4 | remaining: 5
person eliminated:  E1 | number:   5 | remaining: 4
person eliminated:  C1 | number:   3 | remaining: 3
person eliminated:  A1 | number:   1 | remaining: 2
winner:             B1 | number:   2
Continue? (Y/N)y
Please enter the file name: infile.txt
Please enter the number of people: 20
Please enter the number of passes: 0
File processing completed

person eliminated:  A1 | number:   1 | remaining: 20
person eliminated:  B1 | number:   2 | remaining: 19
person eliminated:  C1 | number:   3 | remaining: 18
person eliminated:  D1 | number:   4 | remaining: 17
person eliminated:  E1 | number:   5 | remaining: 16
person eliminated:  F1 | number:   6 | remaining: 15
person eliminated:  G1 | number:   7 | remaining: 14
person eliminated:  H1 | number:   8 | remaining: 13
person eliminated:  I1 | number:   9 | remaining: 12
person eliminated:  J1 | number:  10 | remaining: 11
person eliminated:  K1 | number:  11 | remaining: 10
person eliminated:  L1 | number:  12 | remaining: 9
person eliminated:  M1 | number:  13 | remaining: 8
person eliminated:  N1 | number:  14 | remaining: 7
person eliminated:  O1 | number:  15 | remaining: 6
person eliminated:  P1 | number:  16 | remaining: 5
person eliminated:  Q1 | number:  17 | remaining: 4
person eliminated:  R1 | number:  18 | remaining: 3
person eliminated:  S1 | number:  19 | remaining: 2
winner:             T1 | number:  20
Continue? (Y/N)y
Please enter the file name: infile.txt
Please enter the number of people: 25
Please enter the number of passes: 9
File processing completed

person eliminated:  J1 | number:  10 | remaining: 25
person eliminated:  T1 | number:  20 | remaining: 24
person eliminated:  E1 | number:   5 | remaining: 23
person eliminated:  P1 | number:  16 | remaining: 22
person eliminated:  B1 | number:   2 | remaining: 21
person eliminated:  N1 | number:  14 | remaining: 20
person eliminated:  A1 | number:   1 | remaining: 19
person eliminated:  O1 | number:  15 | remaining: 18
person eliminated:  D1 | number:   4 | remaining: 17
person eliminated:  S1 | number:  19 | remaining: 16
person eliminated:  I1 | number:   9 | remaining: 15
person eliminated:  Y1 | number:  25 | remaining: 14
person eliminated:  U1 | number:  21 | remaining: 13
person eliminated:  M1 | number:  13 | remaining: 12
person eliminated:  K1 | number:  11 | remaining: 11
person eliminated:  H1 | number:   8 | remaining: 10
person eliminated:  L1 | number:  12 | remaining: 9
person eliminated:  R1 | number:  18 | remaining: 8
person eliminated:  X1 | number:  24 | remaining: 7
person eliminated:  Q1 | number:  17 | remaining: 6
person eliminated:  G1 | number:   7 | remaining: 5
person eliminated:  W1 | number:  23 | remaining: 4
person eliminated:  C1 | number:   3 | remaining: 3
person eliminated:  V1 | number:  22 | remaining: 2
winner:             F1 | number:   6
Continue? (Y/N)y
Please enter the file name: infile.txt
Please enter the number of people: 25
Please enter the number of passes: 45
File processing completed

person eliminated:  U1 | number:  21 | remaining: 25
person eliminated:  R1 | number:  18 | remaining: 24
person eliminated:  Q1 | number:  17 | remaining: 23
person eliminated:  T1 | number:  20 | remaining: 22
person eliminated:  Y1 | number:  25 | remaining: 21
person eliminated:  F1 | number:   6 | remaining: 20
person eliminated:  N1 | number:  14 | remaining: 19
person eliminated:  D1 | number:   4 | remaining: 18
person eliminated:  V1 | number:  22 | remaining: 17
person eliminated:  O1 | number:  15 | remaining: 16
person eliminated:  P1 | number:  16 | remaining: 15
person eliminated:  A1 | number:   1 | remaining: 14
person eliminated:  J1 | number:  10 | remaining: 13
person eliminated:  G1 | number:   7 | remaining: 12
person eliminated:  I1 | number:   9 | remaining: 11
person eliminated:  X1 | number:  24 | remaining: 10
person eliminated:  B1 | number:   2 | remaining: 9
person eliminated:  M1 | number:  13 | remaining: 8
person eliminated:  E1 | number:   5 | remaining: 7
person eliminated:  S1 | number:  19 | remaining: 6
person eliminated:  W1 | number:  23 | remaining: 5
person eliminated:  H1 | number:   8 | remaining: 4
person eliminated:  K1 | number:  11 | remaining: 3
person eliminated:  C1 | number:   3 | remaining: 2
winner:             L1 | number:  12
Continue? (Y/N)n

E:\PierceCollege\0_current_term\CS536\CS536Lab3.5\Debug\CS536Lab3.5.exe (process 13164) exited with code 0.
To automatically close the console when debugging stops, enable Tools->Options->Debugging->Automatically close the console when debugging stops.
Press any key to close this window . . .
*/