// Jee, Michael
// CS 540 Lab 6
// 11/28/18

#include "Functions.h"
//#include "stdafx.h"

int main()
{
	int hitLeft = 0;
	creature *monster[4];
	monster[0] = new human;
	monster[1] = new cyberdemon(rand() % 25 + 1, rand() % 20 + 1);
	monster[2] = new balrog(rand() % 20 + 1, rand() % 25 + 1);
	monster[3] = new elf(-1, 0);

	cout << monster[1]->getSpecies() << " hitpoints: " << monster[1]->getHitpoints() << endl;
	cout << monster[0]->getSpecies() << " hitpoints: " << monster[0]->getHitpoints() << endl;
	cout << monster[3]->getSpecies() << " hitpoints: " << monster[3]->getHitpoints() << endl;
	cout << monster[2]->getSpecies() << " hitpoints: " << monster[2]->getHitpoints() << endl;
	cout << "****" << endl;

	cout << "\n" << monster[1]->getSpecies() << " attacks " << monster[0]->getSpecies() << "." << endl;
	hitLeft = monster[0]->getHitpoints() - monster[1]->getDamage();
	monster[0]->setHitpoints(hitLeft);
	if (monster[0]->getHitpoints() <= 0)
		cout << monster[0]->getSpecies() << " died." << endl;
	else
	{
		cout << monster[0]->getSpecies() << " has " << monster[0]->getHitpoints() << " hitpoints remaining." << endl;
		cout << monster[0]->getSpecies() << " counterattacks." << endl;
		hitLeft = monster[1]->getHitpoints() - monster[0]->getDamage();
		monster[1]->setHitpoints(hitLeft);
		if (monster[1]->getHitpoints() <= 0)
			cout << monster[1]->getSpecies() << " died." << endl;
		else
			cout << monster[1]->getSpecies() << " has " << monster[1]->getHitpoints() << " hitpoints remaining." << endl;
	}

	cout << "\n" << monster[3]->getSpecies() << " attacks " << monster[2]->getSpecies() << "." << endl;
	hitLeft = monster[2]->getHitpoints() - monster[3]->getDamage();
	monster[2]->setHitpoints(hitLeft);
	if (monster[2]->getHitpoints() <= 0)
		cout << monster[2]->getSpecies() << " died. ";
	else
	{
		cout << monster[2]->getSpecies() << " has " << monster[2]->getHitpoints() << " hitpoints remaining." << endl;
		cout << monster[2]->getSpecies() << " counterattacks." << endl;
		hitLeft = monster[3]->getHitpoints() - monster[2]->getDamage();
		monster[3]->setHitpoints(hitLeft);
		if (monster[3]->getHitpoints() <= 0)
			cout << monster[3]->getSpecies() << " died." << endl;
		else
			cout << monster[3]->getSpecies() << " has " << monster[2]->getHitpoints() << " hitpoints remaining." << endl;
	}

	for (int i = 0; i < 4; i++)
	{
		delete monster[i];
	}

	system("pause");
	return 0;
}