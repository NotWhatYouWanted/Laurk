#pragma once

#ifndef NOUNS_H
#define NOUNS_H

enum ERooms {
	Hangar,
	Freezer,
	Kitchen,
	CorridoorN,
	Office,
	Reception,
	AmmoStoreN,
	CorridoorS,
	MaintRoom,
	AmmoStoreS,
	Dorm,
	Lab
};
enum ENouns { LabDoor, Tape, Knife, BrokenLever, Wrench, OfficeDrawer, Battery };
const int NOUNSNo = 7;
struct Word
{
	std::string word;
	int Code;
};
struct Noun
{
	std::string Word;
	std::string Name;
	std::string Description;
	int Location;
	int Code;
	int Weight;
	bool CanCarry;
	bool CanOpen;
	bool IsWeapon;
};

#endif // !NOUNS_H