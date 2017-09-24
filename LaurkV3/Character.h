/*
Class to hold all character information and performs any changes to characters.
*/

#pragma once

#include <string>
#include <iostream>

class Inventory;

class Character //: public Inventory
{
public:
	Character(int);
	~Character();

	std::string GetCharName();
	std::string GetNewName();

	bool IsCharAlive();

	//void Attack(Character*);

	//TODO Give health inc/decrements richer values, bool to show successful?
	void HealthIncrement();
	void HealthIncrement(int);
	void HealthDecrement();
	void HealthDecrement(int);

private:
	std::string CharName;
	int CurrentHealth;
	const int MaxHealth;

	unsigned int Damage, Defense;

};

