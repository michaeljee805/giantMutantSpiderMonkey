//Jee, Michael
//2/17/19
//CS 536 Lab 2

//#include "pch.h"
#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int ENTRY_SIZE = 11;

class address
{
private:
	string addressNum, addressName, city, state, zip;
public:
	void setAddrNum(string temp) { addressNum = temp; }
	void setAddrName(string temp) { addressName = temp; }
	void setCity(string temp) { city = temp; }
	void setState(string temp) { state = temp; }
	void setZip(string temp) { zip = temp; }
	void setAddress(string temp1, string temp2, string temp3, string temp4, string temp5) { setAddrNum(temp1); setAddrName(temp2); setCity(temp3); setState(temp4); setZip(temp5); }
	string getAddress() const;
};

class date
{
private:
	string month, day, year;
public:
	void setMonth(string temp) { month = temp; }
	void setDay(string temp) { day = temp; }
	void setYear(string temp) { year = temp; }
	void setDate(string temp1, string temp2, string temp3) { setMonth(temp1); setDay(temp2); setYear(temp3); }
	string getDate() const;
};

class people
{
private:
	string first, last, phone;
	address addr;
	date dat;

	static int numPeople;

public:
	people();
	people(string f, string l, string aNum, string aName, string aCity, string aState, string aZip, string p, string dateM, string dateD, string dateY);
	people(const people & copyThis);
	~people() { --numPeople; }

	void setFirst(string temp) { first = temp; }
	void setLast(string temp) { last = temp; }
	void setAddress(string temp1, string temp2, string temp3, string temp4, string temp5) { addr.setAddress(temp1, temp2, temp3, temp4, temp5); }
	void setPhone(string temp) { phone = temp; }
	void setDate(string temp1, string temp2, string temp3) { dat.setDate(temp1, temp2, temp3); }
	void setEntry(string temp1, string temp2, string temp3, string temp4, string temp5, string temp6, string temp7, string temp8, string temp9, string temp10, string temp11) { setFirst(temp1); setLast(temp2); setAddress(temp3, temp4, temp5, temp6, temp7); setPhone(temp8); setDate(temp9, temp10, temp11); }

	string getLast() const { return last; }
	string getPhone() const { return phone; }
	string getEntry() const;

	int getNumPeople() const { return numPeople; }
};

int people::numPeople = 0;

class node
{

private:
	people person;
	node * next;

public:
	node() { next = nullptr; }
	~node() { }

	void setEntry(string temp1, string temp2, string temp3, string temp4, string temp5, string temp6, string temp7, string temp8, string temp9, string temp10, string temp11) { person.setEntry(temp1, temp2, temp3, temp4, temp5, temp6, temp7, temp8, temp9, temp10, temp11); }
	void setNext(node * temp) { next = temp; }

	string getEntry() const { return person.getEntry(); }
	string getLast() const { return person.getLast(); }
	string getPhone() const { return person.getPhone(); }
	node * getNext() const { return next; }

	int getNumPeople() const { return person.getNumPeople(); }
};

class addBook
{
private:
	node * leadptr, start, end;

	void deleteList(); //deletes list
					   //precondition: list exists
					   //postcondition: dynamically allocated nodes are deallocated
public:
	addBook() { leadptr = &start; start.setNext(&end); }
	~addBook() { deleteList(); }

	bool isEmpty();//checks if the list has more than 3 nodes(leadptr, start, end)
				   //precondition:
				   //postcondition: true or false returned

	node * dynAllocEntry(); //add a dynamically allocated node to the addressBook after the empty start node
							//precondition: linkedlist exists, start node exists, there is enough memory to allocate the new node and its pointer
							//postcondition: a new node is added to the addressBook, the addressBook is 1 item larger

	void processFile(string fileName); //file input
									   //precondition: input file exists, there is enough memory to allocate astring, an ifstream, a node pointer, and a node for each entry
									   //postcondition: the linkedlist is populated with a number of nodes equalling entries in the input file

	node * search(char input2, string input3); //searching for an entry by last name or phone number
											   //precondition: the addressBook exists, enough memory exists for a bool, a string, a node pointer
											   //postcondition: the item is found, its entry is output, and a pointer pointing to the address of the previous entry is returned || the item is not found and a pointer pointing to nullptr is returned

	void addEntry(string temp[]);//adding a new item to the addressBook by user input
								 //precondition: the addressBook exists, there is enough memory for temp, a new node, and a node pointer
								 //postcondition: a new node is added to the addressBook, addressBook size increases by 1

	void deleteEntry(string temp);//search for the item and the previous item, remove an item from the addressBook by last name then relink the addressBook
								  //precondition: the addressBook exists, there exists enough memory for a string, 2 node pointers, a bool, and an int
								  //postcondition: the item is deleted and the addressBook is smaller by 1

	void printToFile();//iterate through the addressBook and printToFile each item to the outputFile
					   //precondition: there exists enough memory for a node pointer, an ofstream, the outputFile exists
					   //postcondition: all items in addressBook printed to outputFile
};

void searchMenu(char & input2, string & input3); //member searching menu
												 //precondition: addressBook exists, there exists enough memory for input2
												 //postcondition: char of value input2 is returned

int main()
{
	char input, input2 = 'A';
	string fileName, input3, temp[ENTRY_SIZE], delString;
	addBook addressBook;
	cout << "Hello. This program will input your address book and sort it accordingly. Please enter the name of the file: " << endl;
	cin >> fileName;
	addressBook.processFile(fileName);
	do
	{
		cout << "a. search entries \nb. add an entry \nc. delete an entry \nd. print entries to file \ne. exit" << endl;
		cin >> input;
		switch (toupper(input))
		{
		case ('A'): //search function by last name or phone number
		{
			if (!addressBook.isEmpty())
			{
				searchMenu(input2, input3);
				addressBook.search(input2, input3);
			}
			break;
		}
		case ('B'): //add entry function
		{
			//function treats list and works the same even if list is empty
			cout << "Please enter the entry in the following format: \nFirst Last Address_Number Address_Name City State Zip Phone Month Day Year" << endl;
			for (int i = 0; i < ENTRY_SIZE; ++i)
				cin >> temp[i];
			addressBook.addEntry(temp);
			break;
		}
		case ('C'): //delete function
		{
			if (!addressBook.isEmpty())
			{
				cout << "Please enter the last name of the entry to be deleted: ";
				cin >> delString;
				addressBook.deleteEntry(delString);
			}
			break;
		}
		case ('D'): //printToFile function
		{
			if (!addressBook.isEmpty())
				addressBook.printToFile();
			break;
		}
		case ('E'): //exit switch
		{
			cout << "Exiting. " << endl;
			break;
		}
		default: //error handling
		{
			cout << "Error. Please enter only a-e." << endl;
		}
		}
		cout << "Enter e to exit, anything else to continue: ";
		cin >> input;
	} while (toupper(input) != 'E');
	system("pause");
	return 0;
}

string address::getAddress() const
{
	return addressNum + " " + addressName + " " + city + " " + state + " " + zip;
}

string date::getDate() const
{
	return month + " " + day + " " + year;
}

people::people() //should never see the POTUS
{
	first = "Donald";//POTUS
	last = "Trump";
	addr.setAddrNum("1600");//white house
	addr.setAddrName("Pennsylvania");
	addr.setCity("Washington");
	addr.setState("DC");
	addr.setZip("20500");
	phone = "9177568000";//twitter posted phone number
	dat.setMonth("06");//1984 publish date
	dat.setDay("08");
	dat.setYear("1949");
	++numPeople;
}

people::people(string f, string l, string aNum, string aName, string aCity, string aState, string aZip, string p, string dateM, string dateD, string dateY)
{
	setEntry(f, l, aNum, aName, aCity, aState, aZip, p, dateM, dateD, dateY);
	++numPeople;
}

people::people(const people & copyThis)
{
	*this = copyThis;
	++numPeople;
}

string people::getEntry() const
{
	return first + " " + last + " " + addr.getAddress() + " " + phone + " " + dat.getDate();
}

bool addBook::isEmpty()
{
	if (leadptr->getNumPeople() <= 3)//accounts for leadptr, start, end
	{
		cout << "The list is empty" << endl;
		return true;
	}
	else
		return false;
}

void addBook::deleteList()
{
	node * ptemp;
	leadptr = leadptr->getNext(); //ignore start node
	while ((leadptr->getNext())->getNext() != nullptr) //ignore end node
	{
		ptemp = leadptr;
		leadptr = leadptr->getNext();
		delete ptemp;
	}
	ptemp = nullptr;
}

node * addBook::dynAllocEntry()
{
	node *ptemp = new (nothrow) node;
	//if (leadptr->getNumPeople() > 15) //testing
	if (ptemp == nullptr)
	{
		cout << "Error. Not enough memory. Exiting " << endl;
		//delete ptemp; //dealloc new node
		//ptemp = nullptr;
		deleteList(); //dealloc rest of the list
		exit(1);
	}
	ptemp->setNext(leadptr->getNext()); //dynAllocEntry item to "start" of addressBook, after the empty leading node
	leadptr->setNext(ptemp);
	return ptemp;
}

void addBook::processFile(string fileName)
{
	string tempEntry[ENTRY_SIZE];
	ifstream inputFile;
	inputFile.open(fileName);
	if (!inputFile)
	{
		cout << "Error opening input file." << endl;
		exit(1);
	}
	while (!inputFile.eof())
	{
		node *currentptr = dynAllocEntry();
		/*if (inputFile.eof())
		{
		cout << "Not enough memory. Exiting." << endl;
		deleteList();
		exit(1);
		}*/
		for (int i = 0; i < ENTRY_SIZE; ++i)
			inputFile >> tempEntry[i];
		currentptr->setEntry(tempEntry[0], tempEntry[1], tempEntry[2], tempEntry[3], tempEntry[4], tempEntry[5], tempEntry[6], tempEntry[7], tempEntry[8], tempEntry[9], tempEntry[10]);
	}
	cout << "File processing completed" << endl;
}

void searchMenu(char & input2, string & input3)
{
	do {
		if (input2 != 'A' && input2 != 'B')
			cout << "Error. Please enter only a or b." << endl;
		cout << "Please choose a subselection: \na. by last name\nb. by phone" << endl;//dynAllocEntry an exit
		cin >> input2;
		input2 = toupper(input2);
	} while (input2 != 'A' && input2 != 'B');
	cout << "Please enter search parameter: ";
	cin >> input3;
}

node * addBook::search(char input2, string input3)
{
	bool found = false;
	node * searchptr = leadptr, *prevptr = leadptr;
	searchptr = searchptr->getNext(); //ignore leading empty node
	switch (input2)
	{
	case 'A':
	{
		for (int i = 1; i < searchptr->getNumPeople() - 1 && !found; ++i)
		{
			found = searchptr->getLast() == input3;
			if (!found)//must be in loop to increment pointers
			{
				searchptr = searchptr->getNext(); //move the current copy of searchptr
				prevptr = prevptr->getNext();
			}
		}
		break;
	}
	case 'B':
	{
		for (int i = 1; i < searchptr->getNumPeople() - 1 && !found; ++i)
		{
			found = searchptr->getPhone() == input3;
			if (!found)
			{
				searchptr = searchptr->getNext(); //move the current copy of searchptr
				prevptr = prevptr->getNext();
			}
		}
		break;
	}
	}
	if (found)
	{
		cout << searchptr->getEntry() << endl;
		return prevptr;
	}

	/*if (input2 == 'A')
	{
		for (int i = 1; i < searchptr->getNumPeople() - 1 && !found; ++i) //nAdd-1 to ignore empty trailing node, i=1 to ignore leading empty node
		{
			if (searchptr->getLast() == input3)
			{
				found = true;
				cout << searchptr->getEntry() << endl;
				return prevptr;
			}
			else
			{
				searchptr = searchptr->getNext(); //move the current copy of searchptr
				prevptr = prevptr->getNext();
			}
		}
	}
	else if (input2 == 'B')
	{
		for (int i = 1; i < searchptr->getNumPeople() - 1 && !found; ++i)
		{
			if (searchptr->getPhone() == input3)
			{
				found = true;
				cout << searchptr->getEntry() << endl;
				return prevptr;
			}
			else
			{
				searchptr = searchptr->getNext(); //move the current copy of searchptr
				prevptr = prevptr->getNext();
			}
		}
	}*/
	cout << "Item not found" << endl;
	return prevptr = nullptr;
}

void addBook::addEntry(string temp[])
{
	node * ptemp = dynAllocEntry();
	ptemp->setEntry(temp[0], temp[1], temp[2], temp[3], temp[4], temp[5], temp[6], temp[7], temp[8], temp[9], temp[10]);
	cout << "Item added." << endl;
	ptemp = nullptr;
}

void addBook::deleteEntry(string temp)
{
	node * prevtemp, *deltemp;
	prevtemp = search('A', temp);
	if (prevtemp != nullptr)//if node is found
	{
		deltemp = prevtemp->getNext(); //set the pointer to what we are actually searching for
		prevtemp->setNext((prevtemp->getNext())->getNext()); //set the nextptr of the previous item to the found item's next
		delete deltemp; //dealloc the found item
		cout << "Entry deleted" << endl;
	}
	prevtemp = nullptr;
	deltemp = nullptr;
}

void addBook::printToFile()
{
	node * printptr = leadptr;
	ofstream outputFile;
	outputFile.open("outputFile.txt");
	if (!outputFile)
	{
		cout << "Not enough memory for output file. Exiting" << endl;
		deleteList();
		exit(1);
	}
	printptr = printptr->getNext();
	for (int i = 1; i < printptr->getNumPeople() - 1; ++i) //nAdd+1 because of empty node, does not iterate_ptr through "empty" end node
	{
		outputFile << printptr->getEntry() << "\n" << endl;
		printptr = printptr->getNext();
	}
	cout << "Address book printed to outputFile.txt" << endl;
	outputFile.close();
}

/*
Hello. This program will input your address book and sort it accordingly. Please enter the name of the file:
inputFileHuge.txt
Error. Not enough memory. Exiting

E:\PierceCollege\0_current_term\CS536\CS536Lab2.8\Debug\CS536Lab2.8.exe (process 4460) exited with code 1.
To automatically close the console when debugging stops, enable Tools->Options->Debugging->Automatically close the console when debugging stops.
Press any key to close this window . . .

Hello. This program will input your address book and sort it accordingly. Please enter the name of the file:
a
Error opening input file.

E:\PierceCollege\0_current_term\CS536\CS536Lab2.8\Debug\CS536Lab2.8.exe (process 12632) exited with code 1.
To automatically close the console when debugging stops, enable Tools->Options->Debugging->Automatically close the console when debugging stops.
Press any key to close this window . . .

inputFileEmpty.txt
//empty

Hello. This program will input your address book and sort it accordingly. Please enter the name of the file:
inputFileEmpty.txt
File processing completed
a. search entries
b. add an entry
c. delete an entry
d. print entries to file
e. exit
a
The list is empty
Enter e to exit, anything else to continue: a
a. search entries
b. add an entry
c. delete an entry
d. print entries to file
e. exit
c
The list is empty
Enter e to exit, anything else to continue: a
a. search entries
b. add an entry
c. delete an entry
d. print entries to file
e. exit
d
The list is empty
Enter e to exit, anything else to continue: a
a. search entries
b. add an entry
c. delete an entry
d. print entries to file
e. exit
b
Please enter the entry in the following format: 
First Last Address_Number Address_Name City State Zip Phone Month Day Year
a
a
a
a
a
a
a
a
a
a
a
Item added.
Enter e to exit, anything else to continue: a
a. search entries
b. add an entry
c. delete an entry
d. print entries to file
e. exit
a
Please choose a subselection:
a. by last name
b. by phone
a
Please enter search parameter: a
a a a a a a a a a a a
Enter e to exit, anything else to continue: a
a. search entries
b. add an entry
c. delete an entry
d. print entries to file
e. exit
d
Address book printed to outputFile.txt
Enter e to exit, anything else to continue: e
Press any key to continue . . .

inputFile.txt
A1 A2 20294 Lorenzana Woodland CA 91364 6261923712 03 18 1993

B1 B2 19831 Henshaw Culver CA 94023 9310293712 04 20 2000

C1 C2 5142 Dumont Azusa CA 91112 3812832934 09 01 1934

D1 D2 20636 Forest Woodland CA 91364 0920932371 12 25 2012

E1 E2 20295 Lorenzana Woodland CA 91364 3562731928 05 05 2005

F1 F2 4851 Poe Woodland CA 91364 4356288372 07 07 2007

G1 G2 20225 Lorenzana Angeles CA 91111 0381923172 02 10 2001

H1 H2 20253 Lorenzana Angeles CA 90005 6945683584 12 23 1969

I1 I2 5241 Moreno Angeles CA 91110 5346822684 10 28 1969

J1 J2 5332 Felice Stevenson CA 94135 7984851764 05 08 1916

K1 K2 5135 Quakertown Thousand CA 91362 5973544682 08 08 2008

L1 L2 720 Eucalyptus Inglewood CA 89030 7925971354 06 06 2006

M1 M2 5021 Dumont Woodland CA 91364 3465974321 11 11 2011

N1 N2 4819 Quedo Westlake CA 91362 9879751327 11 30 1958

O1 O2 5331 Felice Stevenson CA 94135 9825557924 04 24 1976

P1 P2 5333 Felice Stevenson CA 94135 3245952842 12 30 1956

Q1 Q2 20044 Wells Beverly CA 90210 9854925823 08 27 2016

R1 R2 7659 Mckinley Angeles CA 90001 5565555555 02 05 2015

Hello. This program will input your address book and sort it accordingly. Please enter the name of the file:
inputFile.txt
File processing completed
a. search entries
b. add an entry
c. delete an entry
d. print entries to file
e. exit
f
Error. Please enter only a-e.
Enter e to exit, anything else to continue: a
a. search entries
b. add an entry
c. delete an entry
d. print entries to file
e. exit
a
Please choose a subselection:
a. by last name
b. by phone
c
Error. Please enter only a or b.
Please choose a subselection:
a. by last name
b. by phone
a
Please enter search parameter: A2
A1 A2 20294 Lorenzana Woodland CA 91364 6261923712 03 18 1993
Enter e to exit, anything else to continue: a
a. search entries
b. add an entry
c. delete an entry
d. print entries to file
e. exit
a
Please choose a subselection:
a. by last name
b. by phone
a
Please enter search parameter: G2
G1 G2 20225 Lorenzana Angeles CA 91111 0381923172 02 10 2001
Enter e to exit, anything else to continue: a
a. search entries
b. add an entry
c. delete an entry
d. print entries to file
e. exit
a
Please choose a subselection:
a. by last name
b. by phone
a
Please enter search parameter: R2
R1 R2 7659 Mckinley Angeles CA 90001 5565555555 02 05 2015
Enter e to exit, anything else to continue: a
a. search entries
b. add an entry
c. delete an entry
d. print entries to file
e. exit
a
Please choose a subselection:
a. by last name
b. by phone
a
Please enter search parameter: A2
A1 A2 20294 Lorenzana Woodland CA 91364 6261923712 03 18 1993
Enter e to exit, anything else to continue: a
a. search entries
b. add an entry
c. delete an entry
d. print entries to file
e. exit
a
Please choose a subselection:
a. by last name
b. by phone
b
Please enter search parameter: 6261923712
A1 A2 20294 Lorenzana Woodland CA 91364 6261923712 03 18 1993
Enter e to exit, anything else to continue: a
a. search entries
b. add an entry
c. delete an entry
d. print entries to file
e. exit
a
Please choose a subselection:
a. by last name
b. by phone
b
Please enter search parameter: 0381923172
G1 G2 20225 Lorenzana Angeles CA 91111 0381923172 02 10 2001
Enter e to exit, anything else to continue: a
a. search entries
b. add an entry
c. delete an entry
d. print entries to file
e. exit
a
Please choose a subselection:
a. by last name
b. by phone
b
Please enter search parameter: 5565555555
R1 R2 7659 Mckinley Angeles CA 90001 5565555555 02 05 2015
Enter e to exit, anything else to continue: a
a. search entries
b. add an entry
c. delete an entry
d. print entries to file
e. exit
a
Please choose a subselection:
a. by last name
b. by phone
b
Please enter search parameter: 6261923712
A1 A2 20294 Lorenzana Woodland CA 91364 6261923712 03 18 1993
Enter e to exit, anything else to continue: a
a. search entries
b. add an entry
c. delete an entry
d. print entries to file
e. exit
b
Please enter the entry in the following format: 
First Last Address_Number Address_Name City State Zip Phone Month Day Year
a
b
c
d
e
f
g
h
i
j
k
Item added.
Enter e to exit, anything else to continue: a
a. search entries
b. add an entry
c. delete an entry
d. print entries to file
e. exit
a
Please choose a subselection:
a. by last name
b. by phone
a
Please enter search parameter: asdf
Item not found
Enter e to exit, anything else to continue: a
a. search entries
b. add an entry
c. delete an entry
d. print entries to file
e. exit
a
Please choose a subselection:
a. by last name
b. by phone
a
Please enter search parameter: b
a b c d e f g h i j k
Enter e to exit, anything else to continue: a
a. search entries
b. add an entry
c. delete an entry
d. print entries to file
e. exit
a
Please choose a subselection:
a. by last name
b. by phone
b
Please enter search parameter: 123
Item not found
Enter e to exit, anything else to continue: a
a. search entries
b. add an entry
c. delete an entry
d. print entries to file
e. exit
a
Please choose a subselection:
a. by last name
b. by phone
b
Please enter search parameter: h
a b c d e f g h i j k
Enter e to exit, anything else to continue: a
a. search entries
b. add an entry
c. delete an entry
d. print entries to file
e. exit
c
Please enter the last name of the entry to be deleted: b
a b c d e f g h i j k
Entry deleted
Enter e to exit, anything else to continue: a
a. search entries
b. add an entry
c. delete an entry
d. print entries to file
e. exit
c
Please enter the last name of the entry to be deleted: G2
G1 G2 20225 Lorenzana Angeles CA 91111 0381923172 02 10 2001
Entry deleted
Enter e to exit, anything else to continue: a
a. search entries
b. add an entry
c. delete an entry
d. print entries to file
e. exit
c
Please enter the last name of the entry to be deleted: R2
R1 R2 7659 Mckinley Angeles CA 90001 5565555555 02 05 2015
Entry deleted
Enter e to exit, anything else to continue: a
a. search entries
b. add an entry
c. delete an entry
d. print entries to file
e. exit
c
Please enter the last name of the entry to be deleted: a
Item not found
Enter e to exit, anything else to continue: a
a. search entries
b. add an entry
c. delete an entry
d. print entries to file
e. exit
d
Address book printed to outputFile.txt
Enter e to exit, anything else to continue: e
Press any key to continue . . .

E:\PierceCollege\0_current_term\CS536\CS536Lab2.8\Debug\CS536Lab2.8.exe (process 2776) exited with code 0.
To automatically close the console when debugging stops, enable Tools->Options->Debugging->Automatically close the console when debugging stops.
Press any key to close this window . . .

outputFile.txt
Q1 Q2 20044 Wells Beverly CA 90210 9854925823 08 27 2016

P1 P2 5333 Felice Stevenson CA 94135 3245952842 12 30 1956

O1 O2 5331 Felice Stevenson CA 94135 9825557924 04 24 1976

N1 N2 4819 Quedo Westlake CA 91362 9879751327 11 30 1958

M1 M2 5021 Dumont Woodland CA 91364 3465974321 11 11 2011

L1 L2 720 Eucalyptus Inglewood CA 89030 7925971354 06 06 2006

K1 K2 5135 Quakertown Thousand CA 91362 5973544682 08 08 2008

J1 J2 5332 Felice Stevenson CA 94135 7984851764 05 08 1916

I1 I2 5241 Moreno Angeles CA 91110 5346822684 10 28 1969

H1 H2 20253 Lorenzana Angeles CA 90005 6945683584 12 23 1969

F1 F2 4851 Poe Woodland CA 91364 4356288372 07 07 2007

E1 E2 20295 Lorenzana Woodland CA 91364 3562731928 05 05 2005

D1 D2 20636 Forest Woodland CA 91364 0920932371 12 25 2012

C1 C2 5142 Dumont Azusa CA 91112 3812832934 09 01 1934

B1 B2 19831 Henshaw Culver CA 94023 9310293712 04 20 2000

A1 A2 20294 Lorenzana Woodland CA 91364 6261923712 03 18 1993
*/