#pragma once

#include "Nouns.h"

#ifndef INVENTORY_H
#define INVENTORY_H

class  Inventory
{
public:

	void SetNouns(Noun* Nouns);

	Inventory();
	void PickUp(Noun*);
	void DropItem(Noun*);
	void ReadInventory();

private:
	int CurrentWeight;
	const int MaxWeight = 50;
	std::vector<Noun*> InventoryItems;
	const std::string OverweightWarning = "Your bag is too heavy!\n";

	virtual enum ERooms
	{
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
};

#endif // !INVENTORY_H
