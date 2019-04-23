// Jee, Michael
// CS 540 Lab 7
// 11/28/18

#ifndef FUNCTIONS_H
#define FUNCTIONS_H
//#include "pch.h"
//#include "stdafx.h"
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
	virtual int getDamage() const; //abstract class; Returns amount of damage this creature inflicts in one round of combat };

	void setHitpoints(int newHitpoints);

	virtual void dummy() = 0;
};

class human :public creature
{
public:
	human() :creature() {}
	human(int newStrength, int newHitpoints) : creature(newStrength, newHitpoints) {}
	virtual ~human() {}
	void dummy() override {}
};

class demon :public creature
{
public:
	demon() :creature() {}
	demon(int newStrength, int newHitpoints) :creature(newStrength, newHitpoints) {}
	virtual ~demon() {};

	int getDamage();
	void dummy() override {}
};

class elf :public creature
{
public:
	elf() :creature() {}
	elf(int newStrength, int newHitpoints) :creature(newStrength, newHitpoints) {}
	virtual ~elf() {};

	int getDamage();
	void dummy() override {}
};

class cyberdemon :public demon
{
public:
	cyberdemon() :demon() {}
	cyberdemon(int newStrength, int newHitpoints) :demon(newStrength, newHitpoints) {}
	virtual ~cyberdemon() {};
	void dummy() override {}
};

class balrog :public demon
{
public:
	balrog() :demon() {}
	balrog(int newStrength, int newHitpoints) :demon(newStrength, newHitpoints) {}
	virtual ~balrog() {};

	int getDamage();
	void dummy() override {}
};

#endif