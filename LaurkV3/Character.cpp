#include "stdafx.h"
#include "Character.h"

Character::Character(int Max)
	:MaxHealth(Max), CurrentHealth(Max), Damage(0), Defense(0), CharName("Default")
{
	CharName = GetNewName();
}
Character::~Character() { std::cout << "Character " << CharName << " destroyed.\n"; }

std::string Character::GetCharName() { return CharName; }
std::string Character::GetNewName()
{
	std::cout << "What is the name of your adventurer?\n";
	std::string NewName;
	std::cin >> NewName;
	std::cin.ignore();
	std::cout << "Okay, " << NewName << " lets begin your adventure.\n";
	return NewName;
}

bool Character::IsCharAlive() { return CurrentHealth > 0; }

void Character::HealthIncrement()
{
	if (CurrentHealth < MaxHealth)
	{
		CurrentHealth++;
		std::cout << "Your health has increased to " << CurrentHealth << " HP.\n\n";
	}
	else { std::cout << "Your health is already full...\n\n"; }
}
void Character::HealthIncrement(int Inc)
{
	if (CurrentHealth < MaxHealth)
	{
		CurrentHealth = CurrentHealth + Inc;
		if (CurrentHealth > MaxHealth) { CurrentHealth = MaxHealth; }
		std::cout << "Your health has increased to " << CurrentHealth << " HP.\n\n";
	}
	else { std::cout << "Your health is already full...\n\n"; }
}

void Character::HealthDecrement()
{
	CurrentHealth--;
	std::cout << "You health has been reduced to " << CurrentHealth << " HP.\n\n";
}
void Character::HealthDecrement(int Dec)
{
	CurrentHealth = CurrentHealth - Dec;
	if (CurrentHealth < 0) { CurrentHealth = 0; }
	std::cout << "You health has been reduced to " << CurrentHealth << " HP.\n\n";
}

Inventory::Inventory()
	:CurrentWeight(0)
{
	InventoryItems.clear();
}

void Inventory::PickUp(Noun* Item)
{
	if (CurrentWeight + Item->Weight <= MaxWeight)
	{
		InventoryItems.push_back(Item);
		CurrentWeight += Item->Weight;
		std::cout << "You put the " << Item->Name << " into your pack.\n";
	}
	else { std::cout << OverweightWarning; }
}

void Inventory::DropItem(Noun* Item)
	{
		int InitialSize = InventoryItems.size();
		for (unsigned int i = 0; i < InventoryItems.size(); ++i)
		{
			if (Item->Code == InventoryItems[i]->Code)
			{
				std::cout << "You dropped your " << InventoryItems[i]->Name << ".\n";
				CurrentWeight -= InventoryItems[i]->Weight;
				InventoryItems.erase(InventoryItems.begin() + i);
			}
		}
		if (int NewSize = InventoryItems.size() == InitialSize)
		{
			std::cout << "You dont have that in your bag...\n";
		}
	}

void Inventory::ReadInventory()
{
	if (InventoryItems.size() > 0)
	{
		std::cout << "Your bag weight is " << CurrentWeight << " out of " << MaxWeight << "Kg.\n";
		std::cout << "You look into your bag and find..\n";
		for (unsigned int i = 0; i < InventoryItems.size(); ++i)
		{
			std::cout << "Your " << InventoryItems[i]->Name << std::endl;
		}
	}
	else { std::cout << "There is nothing in your inventory... Perhaps you should pick something up.\n"; }
}
