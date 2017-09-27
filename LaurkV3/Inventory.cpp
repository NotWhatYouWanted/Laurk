#include "stdafx.h"
#include "Inventory.h"

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

void Inventory::SetNouns(Noun* Nouns)
{
	Nouns[LabDoor].CanOpen = true;
	Nouns[LabDoor].CanCarry = false;
	Nouns[LabDoor].Location = AmmoStoreS;
	Nouns[LabDoor].Code = LabDoor;
	Nouns[LabDoor].Description = "A heavy-set door hidden in the darkest corner.";
	Nouns[LabDoor].IsWeapon = false;
	Nouns[LabDoor].Weight = 100;
	Nouns[LabDoor].Word = "DOOR";
	Nouns[LabDoor].Name = "Lab Door";

	Nouns[Tape].CanOpen = false;
	Nouns[Tape].CanCarry = true;
	Nouns[Tape].Code = Tape;
	Nouns[Tape].Location = Dorm;
	Nouns[Tape].Description = "A roll of duct tape.";
	Nouns[Tape].IsWeapon = false;
	Nouns[Tape].Weight = 5;
	Nouns[Tape].Word = "TAPE";
	Nouns[Tape].Name = "Tape";

	Nouns[Knife].CanOpen = false;
	Nouns[Knife].CanCarry = true;
	Nouns[Knife].Code = Knife;
	Nouns[Knife].Location = Kitchen;
	Nouns[Knife].Description = "A honed kitchen blade.";
	Nouns[Knife].IsWeapon = true;
	Nouns[Knife].Weight = 5;
	Nouns[Knife].Word = "KNIFE";
	Nouns[Knife].Name = "Knife";

	Nouns[BrokenLever].CanOpen = false;
	Nouns[BrokenLever].CanCarry = false;
	Nouns[BrokenLever].Code = BrokenLever;
	Nouns[BrokenLever].Location = Hangar;
	Nouns[BrokenLever].Description = "A snapped lever.";
	Nouns[BrokenLever].IsWeapon = false;
	Nouns[BrokenLever].Weight = 100;
	Nouns[BrokenLever].Word = "LEVER";
	Nouns[BrokenLever].Name = "Broken Lever";

	Nouns[Wrench].CanOpen = false;
	Nouns[Wrench].CanCarry = true;
	Nouns[Wrench].Code = Wrench;
	Nouns[Wrench].Location = MaintRoom;
	Nouns[Wrench].Description = "A worn torque wrench.";
	Nouns[Wrench].IsWeapon = true;
	Nouns[Wrench].Weight = 15;
	Nouns[Wrench].Word = "WRENCH";
	Nouns[Wrench].Name = "Rusty Wrench";

	Nouns[OfficeDrawer].CanOpen = true;
	Nouns[OfficeDrawer].CanCarry = false;
	Nouns[OfficeDrawer].Code = OfficeDrawer;
	Nouns[OfficeDrawer].Location = Office;
	Nouns[OfficeDrawer].Description = "A finely crafted mahogany drawer.";
	Nouns[OfficeDrawer].IsWeapon = false;
	Nouns[OfficeDrawer].Weight = 100;
	Nouns[OfficeDrawer].Word = "DRAWER";
	Nouns[OfficeDrawer].Name = "Drawer";

	Nouns[Battery].CanOpen = false;
	Nouns[Battery].CanCarry = true;
	Nouns[Battery].Code = Battery;
	Nouns[Battery].Location = Lab;
	Nouns[Battery].Description = "A gently humming battery.";
	Nouns[Battery].IsWeapon = false;
	Nouns[Battery].Weight = 20;
	Nouns[Battery].Word = "BATTERY";
	Nouns[Battery].Name = "Smooth Battery";
}
