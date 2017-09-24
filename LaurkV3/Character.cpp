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

//void Character::Attack(Character* Target)

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
