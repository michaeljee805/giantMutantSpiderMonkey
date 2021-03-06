//Jee, Michael
//3/10/19
//CS 536 Lab 4

//#include "pch.h"
#include "stdafx.h"
#include <iostream>
using namespace std;

class inventory
{
private:
	double cost;
	int num;
	unsigned refNum;

	static unsigned totRefNum;

public:
	inventory() { cost = -1, num = 0, ++totRefNum, refNum = totRefNum; }
	inventory(double temp, int temp2) { cost = temp, num = temp2, ++totRefNum, refNum = totRefNum; }
	inventory(const inventory & copyThis) { *this = copyThis, ++totRefNum, refNum = totRefNum; }
	~inventory() { ++refNum; }

	double getCost() const { return cost; }
	int getNum() const { return num; }

	int getRefNum() const { return refNum; }

	void setCost(double temp) { cost = temp; }
	void setNum(int temp) { num = temp; }
};

unsigned inventory::totRefNum = 99999998;

class node
{
private:
	node * next;

	inventory item;

public:
	node() { next = nullptr; }
	~node() { }

	node * getNext() const { return next; }

	double getCost() const { return item.getCost(); }
	int getNum() const { return item.getNum(); }

	int getRefNum() const { return item.getRefNum(); }

	void setNext(node * temp) { next = temp; }

	void setCost(double temp) { item.setCost(temp); }
	void setNum(int temp) { item.setNum(temp); }
};

class warehouse
{
private:
	node end;

	node * leadptr;

	void deleteList();//deletes list
					  //precondition: list exists
					  //postcondition: list is deallocated
public:
	warehouse() { leadptr = &end; }
	~warehouse() { deleteList(); }

	node * getptr() const { return leadptr; }

	void add(double cost, int num); //dynamically allocate a new node and add to the top of the stack
									//precondition: if deliveries called before, wcost >=0 and wnum>0
									//	else if orders called before, onum>0
									//	enough memory exists to allocate a node pointer and node
									//postconditions: if deliveries called before, wleadptr now points to the newest widget entry, and cost and number assigned
									//	else if orders called before, oleadptr now points to the newest order entry, number assigned, and cost left at default of -1
	void iterate() { leadptr = leadptr->getNext(); }//leadpointer of the linkedlist moved down one
					//precondition: leadpointer, node, and linkedlist exist
					//postconditions: leadpointer moved down one item
	void print();//display current inventory/backorders
				 //precondition: widget and order linked lists exist, there is enough memory for two node pointers
				 //postcondition: if neither have nodes with values, print no orders or inventory
				 //	else if no orders, print the inventory
				 //	else print the backorders
};

void deliveries(double & cost, int & num); //take user input for cost and number of widgets
										   //precondition: widget and order warehouses exist
										   //postconditions: wcost>=0, wnum>0
void orders(int & num); //take user input for number of widgets ordered
						//precondition: widget and order warehouses exist
						//postconditions: onum>=0
void output(warehouse & widget, warehouse & order);//recursive function consolidating orders and widget inventory
												   //precondition: either wleadptr or oleadptr have an entry
												   //postcondition: wleadptr and oleadptr update until one or both has no further entries

int main()
{
	double cost = 0;
	int num = 1;
	char option;
	warehouse widget, order;
	do
	{
		cout << "Please choose an option: \na.add a delivery \nb.add an order \nc.print current inventory \nd.exit" << endl;
		cin >> option;
		option = toupper(option);
		switch (option)
		{
		case 'A':
		{
			//add a delivery
			deliveries(cost, num);
			widget.add(cost, num);
			output(widget, order);
			cout << "Delivery completed\n" << endl;
			break;
		}
		case 'B':
		{
			//add an order
			orders(num);
			order.add(cost, num);
			output(widget, order);
			cout << "Order completed\n" << endl;
			break;
		}
		case 'C':
		{
			//print current inventory
			if (widget.getptr()->getNext() == nullptr && order.getptr()->getNext() == nullptr)
				cout << "Inventory is empty, and there are no orders." << endl;
			else if (order.getptr()->getNext() == nullptr)
				widget.print();
			else
				order.print();
			break;
		}
		case 'D':
		{
			//exit
			cout << "Are you sure you wish to exit? ";
			break;
		}
		default:
		{
			//error handling
			cout << "Error. Please enter only a-d." << endl;
		}
		}
		cout << "Enter d to exit, anything else to continue: ";
		cin >> option;
		option = toupper(option);
		cost = 0, num = 1;
	} while (option != 'D');
	return 0;
}

void deliveries(double & cost, int & num)
{
	do
	{
		if (cost < 0)
			cout << "Error. Negative number. ";
		cout << "Please enter the cost: ";
		cin >> cost;
	} while (cost < 0);
	do
	{
		if (num <= 0)
			cout << "Error. ";
		cout << "Please enter the number ordered: ";
		cin >> num;
	} while (num <= 0);
}

void orders(int & num)
{
	do
	{
		if (num <= 0)
			cout << "Error. ";
		cout << "Please enter the number ordered: ";
		cin >> num;
	} while (num <= 0);
}

void warehouse::deleteList()
{
	node * delptr;
	while (leadptr->getNext() != nullptr)
	{
		delptr = leadptr;
		leadptr = leadptr->getNext();
		delete delptr;
	}
	delptr = nullptr;
}

void warehouse::add(double cost, int num)
{
	node *addptr = new (nothrow) node;
	if (addptr == nullptr)
	{
		cout << "Error. Not enough memory. Exiting " << endl;
		deleteList();
		exit(1);
	}
	addptr->setNext(leadptr);
	leadptr = addptr;
	if (cost)
		leadptr->setCost(cost);
	leadptr->setNum(num);
	addptr = nullptr;
}

void output(warehouse & widget, warehouse & order)
{
	if (widget.getptr()->getNext() == nullptr) //no inventory, some order
		cout << "There is no inventory remaining, " << order.getptr()->getNum() << " widgets will be backlogged" << endl;
	else if (order.getptr()->getNext() == nullptr) //some inventory, no orders
		cout << "No current orders, " << widget.getptr()->getNum() << " widgets will be stored in the warehouse" << endl;
	else
	{
		if (order.getptr()->getNum() == widget.getptr()->getNum()) //when newest order number equal to newest widget entry number
		{
			cout << order.getptr()->getNum() << " widgets delivered at $" << 1.5*widget.getptr()->getCost() << " each, totalling: $" << order.getptr()->getNum()*1.5*widget.getptr()->getCost() << endl;
			widget.iterate();
			order.iterate();
		}
		else if (order.getptr()->getNum() < widget.getptr()->getNum()) //when newest order number is less than newest widget entry number
		{
			widget.getptr()->setNum(widget.getptr()->getNum() - order.getptr()->getNum());
			cout << order.getptr()->getNum() << " widgets delivered at $" << 1.5*widget.getptr()->getCost() << " each, totalling: $" << order.getptr()->getNum()*1.5*widget.getptr()->getCost() << endl;
			order.iterate();
			output(widget, order);
		}
		else //when newest order number is greater than the newest widget entry number
		{
			order.getptr()->setNum(order.getptr()->getNum() - widget.getptr()->getNum());
			cout << widget.getptr()->getNum() << " widgets delivered at $" << 1.5*widget.getptr()->getCost() << " each, totalling: $" << widget.getptr()->getNum()*1.5*widget.getptr()->getCost() << endl;
			widget.iterate();
			output(widget, order);
		}
	}
}

void warehouse::print()
{
	node * printptr = leadptr;
	while (printptr->getNext() != nullptr)
	{
		if (printptr->getCost() == -1)
			cout << "backordered: " << printptr->getNum() << " widgets | reference number: " << printptr->getRefNum() << endl;
		else
			cout << "widget cost: $" << printptr->getCost() << " | number of: " << printptr->getNum() << " | reference number: " << printptr->getRefNum() << endl;
		printptr = printptr->getNext();
	}
}

/*
Please choose an option:
a.add a delivery
b.add an order
c.print current inventory
d.exit
c
Inventory is empty, and there are no orders.
Enter d to exit, anything else to continue: a
Please choose an option:
a.add a delivery
b.add an order
c.print current inventory
d.exit
a
Please enter the cost: 3
Please enter the number ordered: 4
No current orders, 4 widgets will be stored in the warehouse
Delivery completed

Enter d to exit, anything else to continue: a
Please choose an option:
a.add a delivery
b.add an order
c.print current inventory
d.exit
c
widget cost: $3 | number of: 4 | reference number: 100000001
Enter d to exit, anything else to continue: a
Please choose an option:
a.add a delivery
b.add an order
c.print current inventory
d.exit
a
Please enter the cost: 4
Please enter the number ordered: 3
No current orders, 3 widgets will be stored in the warehouse
Delivery completed

Enter d to exit, anything else to continue: a
Please choose an option:
a.add a delivery
b.add an order
c.print current inventory
d.exit
c
widget cost: $4 | number of: 3 | reference number: 100000002
widget cost: $3 | number of: 4 | reference number: 100000001
Enter d to exit, anything else to continue: a
Please choose an option:
a.add a delivery
b.add an order
c.print current inventory
d.exit
b
Please enter the number ordered: 2
2 widgets delivered at $6 each, totalling: $12
No current orders, 1 widgets will be stored in the warehouse
Order completed

Enter d to exit, anything else to continue: a
Please choose an option:
a.add a delivery
b.add an order
c.print current inventory
d.exit
c
widget cost: $4 | number of: 1 | reference number: 100000002
widget cost: $3 | number of: 4 | reference number: 100000001
Enter d to exit, anything else to continue: a
Please choose an option:
a.add a delivery
b.add an order
c.print current inventory
d.exit
b
Please enter the number ordered: 2
1 widgets delivered at $6 each, totalling: $6
1 widgets delivered at $4.5 each, totalling: $4.5
No current orders, 3 widgets will be stored in the warehouse
Order completed

Enter d to exit, anything else to continue: a
Please choose an option:
a.add a delivery
b.add an order
c.print current inventory
d.exit
b
Please enter the number ordered: 4
3 widgets delivered at $4.5 each, totalling: $13.5
There is no inventory remaining, 1 widgets will be backlogged
Order completed

Enter d to exit, anything else to continue: a
Please choose an option:
a.add a delivery
b.add an order
c.print current inventory
d.exit
c
backordered: 1 widgets | reference number: 100000005
Enter d to exit, anything else to continue: a
Please choose an option:
a.add a delivery
b.add an order
c.print current inventory
d.exit
b
Please enter the number ordered: 5
There is no inventory remaining, 5 widgets will be backlogged
Order completed

Enter d to exit, anything else to continue: a
Please choose an option:
a.add a delivery
b.add an order
c.print current inventory
d.exit
c
backordered: 5 widgets | reference number: 100000006
backordered: 1 widgets | reference number: 100000005
Enter d to exit, anything else to continue: a
Please choose an option:
a.add a delivery
b.add an order
c.print current inventory
d.exit
a
Please enter the cost: 7
Please enter the number ordered: 7
5 widgets delivered at $10.5 each, totalling: $52.5
1 widgets delivered at $10.5 each, totalling: $10.5
No current orders, 1 widgets will be stored in the warehouse
Delivery completed

Enter d to exit, anything else to continue: a
Please choose an option:
a.add a delivery
b.add an order
c.print current inventory
d.exit
c
widget cost: $7 | number of: 1 | reference number: 100000007
Enter d to exit, anything else to continue: a
Please choose an option:
a.add a delivery
b.add an order
c.print current inventory
d.exit
a
Please enter the cost: 1
Please enter the number ordered: 1
No current orders, 1 widgets will be stored in the warehouse
Delivery completed

Enter d to exit, anything else to continue: a
Please choose an option:
a.add a delivery
b.add an order
c.print current inventory
d.exit
c
widget cost: $1 | number of: 1 | reference number: 100000008
widget cost: $7 | number of: 1 | reference number: 100000007
Enter d to exit, anything else to continue: a
Please choose an option:
a.add a delivery
b.add an order
c.print current inventory
d.exit
b
Please enter the number ordered: 2
1 widgets delivered at $1.5 each, totalling: $1.5
1 widgets delivered at $10.5 each, totalling: $10.5
Order completed

Enter d to exit, anything else to continue: a
Please choose an option:
a.add a delivery
b.add an order
c.print current inventory
d.exit
c
Inventory is empty, and there are no orders.
Enter d to exit, anything else to continue: d

E:\PierceCollege\0_current_term\CS536\CS536Lab4.5\Debug\CS536Lab4.5.exe (process 4164) exited with code 0.
To automatically close the console when debugging stops, enable Tools->Options->Debugging->Automatically close the console when debugging stops.
Press any key to close this window . . .

*/