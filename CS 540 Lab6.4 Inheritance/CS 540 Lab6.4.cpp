// Jee, Michael
// CS 540 Lab 6
// 11/17/18

//#include "pch.h"
#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

class creature
{
private:
	int strength;   // How much damage we can inflict
	int hitpoints;  // How much damage we can sustain

public:
	creature();
	creature(int newStrength, int newHitpoints);
	virtual ~creature() {}
	
	int getStrength() const { return strength; }
	int getHitpoints() const { return hitpoints; }
	string getSpecies() const; // Returns type of species
	virtual int getDamage(); // Returns amount of damage this creature inflicts in one round of combat };

	void setHitpoints(int newHitpoints);
};

class human :public creature
{
public:
	human() :creature() {}
	human(int newStrength, int newHitpoints) : creature(newStrength, newHitpoints) {}
	virtual ~human() {}
};

class demon :public creature
{
public:
	demon() :creature() {}
	demon(int newStrength, int newHitpoints) :creature(newStrength, newHitpoints) {}
	virtual ~demon() {};

	int getDamage();
};

class elf :public creature
{
public:
	elf() :creature() {}
	elf(int newStrength, int newHitpoints) :creature(newStrength, newHitpoints) {}
	virtual ~elf() {};

	int getDamage();
};

class cyberdemon :public demon
{
public:
	cyberdemon() :demon() {}
	cyberdemon(int newStrength, int newHitpoints) :demon(newStrength, newHitpoints) {}
	virtual ~cyberdemon() {};
};

class balrog :public demon
{
public:
	balrog() :demon() {}
	balrog(int newStrength, int newHitpoints) :demon(newStrength, newHitpoints) {}
	virtual ~balrog() {};

	int getDamage();
};

int main()
{
	int hitLeft = 0;
	human human1;
	cyberdemon cyber1(rand() % 25 + 1, rand() % 20 + 1);
	balrog balrog1(rand() % 20 + 1, rand() % 25 + 1);
	elf elf1(-1, 0);

	cout << cyber1.getSpecies() << " hitpoints: " << cyber1.getHitpoints() << endl;
	cout << human1.getSpecies() << " hitpoints: " << human1.getHitpoints() << endl;
	cout << elf1.getSpecies() << " hitpoints: " << elf1.getHitpoints() << endl;
	cout << balrog1.getSpecies() << " hitpoints: " << balrog1.getHitpoints() << endl;
	cout << "****" << endl;
	cout << "\n" << cyber1.getSpecies() << " attacks " << human1.getSpecies() << "." << endl;
	hitLeft = human1.getHitpoints() - cyber1.getDamage();
	human1.setHitpoints(hitLeft);
	if (human1.getHitpoints() <= 0)
		cout << human1.getSpecies() << " died." << endl;
	else
	{
		cout << human1.getSpecies() << " has " << human1.getHitpoints() << " hitpoints remaining." << endl;
		cout << human1.getSpecies() << " counterattacks." << endl;
		hitLeft = cyber1.getHitpoints() - human1.getDamage();
		cyber1.setHitpoints(hitLeft);
		if (cyber1.getHitpoints() <= 0)
			cout << cyber1.getSpecies() << " died." << endl;
		else
			cout << cyber1.getSpecies() << " has " << cyber1.getHitpoints() << " hitpoints remaining." << endl;
	}

	cout << "\n" << elf1.getSpecies() << " attacks " << balrog1.getSpecies() << "." << endl;
	hitLeft = balrog1.getHitpoints() - elf1.getDamage();
	balrog1.setHitpoints(hitLeft);
	if (balrog1.getHitpoints() <= 0)
		cout << balrog1.getSpecies() << " died. ";
	else
	{
		cout << balrog1.getSpecies() << " has " << balrog1.getHitpoints() << " hitpoints remaining." << endl;
		cout << balrog1.getSpecies() << " counterattacks." << endl;
		hitLeft = elf1.getHitpoints() - balrog1.getDamage();
		elf1.setHitpoints(hitLeft);
		if (elf1.getHitpoints() <= 0)
			cout << elf1.getSpecies() << " died." << endl;
		else
			cout << elf1.getSpecies() << " has " << balrog1.getHitpoints() << " hitpoints remaining." << endl;
	}

	system("pause");
	return 0;
}

creature::creature()
{
	strength = 10;
	hitpoints = 10;
}

creature::creature(int newStrength, int newHitpoints)
{
	strength = newStrength;
	if (strength <= 0)
	{
		strength = 1;
		cout << "Error. Strength cannot be below 1. Strength set to 1" << endl;
	}
	hitpoints = newHitpoints;
	if (hitpoints <= 0)
	{
		hitpoints = 1;
		cout << "Error. Hitpoints cannot be below 1. Hitpoints set to 1" << endl;
	}
}

int creature::getDamage()
{
	int damage = (rand() % strength) + 1;
	cout << getSpecies() << " deals " << damage << " damage." << endl;
	return damage;
}

int demon::getDamage()
{
	int damage = (rand() % getStrength()) + 1;
	cout << getSpecies() << " deals " << damage << " damage." << endl;
	//if ((rand() % 100) < 5) // Demons can inflict damage of 50 with a 5% chance
	{
		damage += 50;
		cout << "demonic attack inflicted 50 additional points of damage." << endl;
	}
	return damage;
}

int elf::getDamage()
{
	int damage = creature::getDamage();
	if ((rand() % 10) == 0) // Elves inflict double magical damage with a 10% chance
	{
		cout << "the attack became magical dealing an additional " << damage << " damage" << endl;
		damage *= 2;
	}
	return damage;
}

int balrog::getDamage()
{
	int damage;
	cout << "balrogs are so fast they attack twice: " << endl; // Balrogs are so fast they get to attack twice
	damage = demon::getDamage() + demon::getDamage();
	return damage;
}

string creature::getSpecies() const
{ 
	string temp;
	temp = typeid(*this).name();
	return temp.substr(6);
}

void creature::setHitpoints(int newHitpoints) 
{ 
	hitpoints = newHitpoints; 
	if (hitpoints < 0)
		hitpoints = 0;
}

/*
testing 100% chance for elf to deal double, 100% chance for demon to deal 50 bonus
Error. Strength cannot be below 1. Strength set to 1
Error. Hitpoints cannot be below 1. Hitpoints set to 1
cyberdemon hitpoints: 2
human hitpoints: 10
elf hitpoints: 1
balrog hitpoints: 10
****

cyberdemon attacks human.
cyberdemon deals 18 damage.
demonic attack inflicted 50 additional points of damage.
human died.

elf attacks balrog.
elf deals 1 damage.
the attack became magical dealing an additional 1 damage
balrog has 8 hitpoints remaining.
balrog counterattacks.
balrogs are so fast they attack twice:
balrog deals 1 damage.
demonic attack inflicted 50 additional points of damage.
balrog deals 1 damage.
demonic attack inflicted 50 additional points of damage.
elf died.
Press any key to continue . . .

Error. Strength cannot be below 1. Strength set to 1
Error. Hitpoints cannot be below 1. Hitpoints set to 1
cyberdemon hitpoints: 2
human hitpoints: 20
elf hitpoints: 1
balrog hitpoints: 10
****

testing defaults
cyberdemon attacks human.
cyberdemon deals 18 damage.
human has 2 hitpoints remaining.
human counterattacks.
human deals 9 damage.
cyberdemon died.

elf attacks balrog.
elf deals 1 damage.
balrog has 9 hitpoints remaining.
balrog counterattacks.
balrogs are so fast they attack twice:
balrog deals 1 damage.
balrog deals 1 damage.
elf died.
Press any key to continue . . .
*/