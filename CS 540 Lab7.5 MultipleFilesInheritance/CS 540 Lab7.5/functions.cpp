// Jee, Michael
// CS 540 Lab 6
// 11/28/18

#include "Functions.h"
//#include "stdafx.h"
#include <string>
using namespace std;
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
		cout << "Error. Strength cannot be below 0. Strength set to 1" << endl;
	}
	hitpoints = newHitpoints;
	if (hitpoints <= 0)
	{
		hitpoints = 1;
		cout << "Error. Hitpoints cannot be below 0. Hitpoints set to 1" << endl;
	}
}

int creature::getDamage() const
{
	int damage = (rand() % strength) + 1;
	cout << getSpecies() << " deals " << damage << " damage." << endl;
	return damage;
}

int demon::getDamage()
{
	int damage = (rand() % getStrength()) + 1;
	cout << getSpecies() << " deals " << damage << " damage." << endl;
	if ((rand() % 100) < 5) // Demons can inflict damage of 50 with a 5% chance
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