/*
Class to hold all character information and performs any changes to characters.
*/

#pragma once

#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <iostream>
#include "Nouns.h"

class Inventory
{
public:
	Inventory();
	void PickUp(Noun);
	void DropItem(Noun);
	void ReadInventory();

private:
	int CurrentWeight;
	const int MaxWeight = 50;
	std::vector<Noun> InventoryItems;
	const std::string OverweightWarning = "Your bag is too heavy!\n";

};

class Character : public Inventory
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


#endif // CHARACTER_H