/*
Class to hold all character information and performs any changes to characters, inherits Inventory.
*/

#pragma once

#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <iostream>
#include "Inventory.h"

class Character : public Inventory
{
public:
	Character(int);
	~Character();

	std::string GetCharName();
	std::string GetNewName();

	bool IsCharAlive();

	//void Attack(Character*);

	void HealthIncrement(int);
	void HealthDecrement(int);

private:
	std::string CharName;
	int CurrentHealth;
	const int MaxHealth;

	unsigned int Damage, Defense;

};


#endif // CHARACTER_H