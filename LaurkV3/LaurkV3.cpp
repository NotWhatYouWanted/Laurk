// LaurkV3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//Game loop and main functions.
void GameIntro();

//Map Management see Nouns.h for Rooms enumeration
const int ROOMSNo = 12;
enum EDirections {North, East, South, West};
const int NONE = -1;
const int LOCKED = -5;
const int DIRECTIONSNo = 4;
struct Room 
{
	std::string Name;
	std::string Description;
	int Exits[DIRECTIONSNo];
};
void SetRooms(Room*);
void SetDirections(Word*);

//User input handling see Nouns.h for Map, Word and Noun definitions.
enum EVerbs { Inventory, Look, Use, Get, Drop, Open, Close, Attack, Help };
const int VERBSNo = 9;
void SetVerbs(Word* Verbs);
void SetNouns(Noun* Nouns);

bool GetCommand(std::string, std::string&, std::string&);
bool Parse(int& OUTLocation, std::string, std::string, Word* Directions, Word* Verbs, Noun* Nouns, Room*, Character&);
void LookAround(int Location, Room*, Word*, Noun*);

int main()
{
	GameIntro();
	Character Player(20);

	//Create array of rooms and set their values.
	Room Rooms[ROOMSNo];
	SetRooms(Rooms);
	int Location = Reception; //Setting start location
	std::cout << "You wake up in " << Rooms[Location].Description << std::endl;

	//Create any words needed for parsing input.
	Word Directions[DIRECTIONSNo];
	SetDirections(Directions);
	Word Verbs[VERBSNo];
	SetVerbs(Verbs);
	Noun Nouns[NOUNSNo];
	SetNouns(Nouns);

	std::string Input, Word1, Word2;
	while (Word1 != "QUIT")
	{
		Input.clear();
		std::cout << "What next o' wise "<< Player.GetCharName() << " ?\n";
		std::getline(std::cin, Input);
		Word1.clear();
		Word2.clear();
		GetCommand(Input, Word1, Word2);

		Parse(Location, Word1, Word2, Directions, Verbs, Nouns, Rooms, Player);
	}
	return 0;
}

void GameIntro()
{
	std::cout << "Welcome to Laurk, totally not a rip-off of anything\n";
	std::cout << "Would you like to begin a new adventure?\n"; //TODO add save game resource file
}

//Splits input by space stored in 'delim', stores in vector and then outputs to words1,2.

void SetRooms(Room* Room)
{
	Room[Hangar].Name.assign("a cavernous hangar.");
	Room[Hangar].Description.assign("a huge hangar with a couple of disued helicopters, there is an opening in the roof.");
	Room[Hangar].Exits[North] = NONE;
	Room[Hangar].Exits[East] = NONE;
	Room[Hangar].Exits[South] = CorridoorN;
	Room[Hangar].Exits[West] = NONE;

	Room[Freezer].Name.assign("a walk-in freezer.");
	Room[Freezer].Description.assign("the walk-in freezer, brimming with food.");
	Room[Freezer].Exits[North] = NONE;
	Room[Freezer].Exits[East] = Kitchen;
	Room[Freezer].Exits[South] = NONE;
	Room[Freezer].Exits[West] = NONE;

	Room[Kitchen].Name.assign("an industrial scale kitchen.");
	Room[Kitchen].Description.assign("a wide kitchen, stocked with everything needed to feed an army.");
	Room[Kitchen].Exits[North] = NONE;
	Room[Kitchen].Exits[East] = CorridoorN;
	Room[Kitchen].Exits[South] = NONE;
	Room[Kitchen].Exits[West] = Freezer;

	Room[CorridoorN].Name.assign("the corridoor.");
	Room[CorridoorN].Description.assign("the northen end of a long corridoor.");
	Room[CorridoorN].Exits[North] = Hangar;
	Room[CorridoorN].Exits[East] = NONE;
	Room[CorridoorN].Exits[South] = CorridoorS;
	Room[CorridoorN].Exits[West] = Kitchen;
	
	Room[Office].Name.assign("an office.");
	Room[Office].Description.assign("a grand office with a large mahogany desk.");
	Room[Office].Exits[North] = NONE;
	Room[Office].Exits[East] = Reception;
	Room[Office].Exits[South] = NONE;
	Room[Office].Exits[West] = NONE;

	Room[Reception].Name.assign("the reception hall.");
	Room[Reception].Description.assign("a previously well-decorated reception, now lying in disrepair.");
	Room[Reception].Exits[North] = NONE;
	Room[Reception].Exits[East] = AmmoStoreN;
	Room[Reception].Exits[South] = NONE;
	Room[Reception].Exits[West] = Office;

	Room[AmmoStoreN].Name.assign("a dark warehouse.");
	Room[AmmoStoreN].Description.assign("the northern end of a long warehouse stacked with boxes of rifles and armour.");
	Room[AmmoStoreN].Exits[North] = NONE;
	Room[AmmoStoreN].Exits[East] = CorridoorS;
	Room[AmmoStoreN].Exits[South] = AmmoStoreS;
	Room[AmmoStoreN].Exits[West] = Reception;

	Room[CorridoorS].Name.assign("the corridoor.");
	Room[CorridoorS].Description.assign("the southern end of a long corridoor.");
	Room[CorridoorS].Exits[North] = CorridoorN;
	Room[CorridoorS].Exits[East] = NONE;
	Room[CorridoorS].Exits[South] = Dorm;
	Room[CorridoorS].Exits[West] = AmmoStoreN;

	Room[MaintRoom].Name.assign("a maintenance room.");
	Room[MaintRoom].Description.assign("a sweltering maintenance room full of steam and whirring machines.");
	Room[MaintRoom].Exits[North] = NONE;
	Room[MaintRoom].Exits[East] = AmmoStoreS;
	Room[MaintRoom].Exits[South] = NONE;
	Room[MaintRoom].Exits[West] = NONE;

	Room[AmmoStoreS].Name.assign("a dark warehouse.");
	Room[AmmoStoreS].Description.assign("the southern end of a long warehouse filled with crates of ammo and munitions.");
	Room[AmmoStoreS].Exits[North] = AmmoStoreN;
	Room[AmmoStoreS].Exits[East] = NONE;
	Room[AmmoStoreS].Exits[South] = LOCKED;
	Room[AmmoStoreS].Exits[West] = MaintRoom;

	Room[Dorm].Name.assign("a cramped dormitory.");
	Room[Dorm].Description.assign("a dorm lined with bunks with a row of lockers at the end of the room.");
	Room[Dorm].Exits[North] = CorridoorS;
	Room[Dorm].Exits[East] = NONE;
	Room[Dorm].Exits[South] = NONE;
	Room[Dorm].Exits[West] = NONE;

	Room[Lab].Name.assign("a well hidden laboratory.");
	Room[Lab].Description.assign("a laboratory brimming with equipment and secrets.");
	Room[Lab].Exits[North] = LOCKED;
	Room[Lab].Exits[East] = NONE;
	Room[Lab].Exits[South] = NONE;
	Room[Lab].Exits[West] = NONE;
}

void SetDirections(Word* Direction)
{
	Direction[North].Code = North;
	Direction[North].word = "NORTH";
	Direction[East].Code = East;
	Direction[East].word = "EAST";
	Direction[South].Code = South;
	Direction[South].word = "SOUTH";
	Direction[West].Code = West;
	Direction[West].word = "WEST";
}

void SetVerbs(Word* Verbs)
{
	Verbs[Inventory].Code = Inventory;
	Verbs[Inventory].word = "INVENTORY";
	Verbs[Look].Code = Look;
	Verbs[Look].word = "LOOK";
	Verbs[Use].Code = Use;
	Verbs[Use].word = "USE";
	Verbs[Get].Code = Get;
	Verbs[Get].word = "GET";
	Verbs[Drop].Code = Drop;
	Verbs[Drop].word = "DROP";
	Verbs[Open].Code = Open;
	Verbs[Open].word = "OPEN";
	Verbs[Close].Code = Close;
	Verbs[Close].word = "CLOSE";
	Verbs[Attack].Code = Attack;
	Verbs[Attack].word = "ATTACK";
	Verbs[Help].Code = Help;
	Verbs[Help].word = "HELP";
}

void SetNouns(Noun* Nouns)
{
	Nouns[LabDoor].CanOpen = true;
	Nouns[LabDoor].CanCarry = false;
	Nouns[LabDoor].Location = AmmoStoreS;
	Nouns[LabDoor].Code = LabDoor;
	Nouns[LabDoor].Description = "A heavy-set door hidden in the darkest corner.";
	Nouns[LabDoor].IsWeapon = false;
	Nouns[LabDoor].Weight = 100;
	Nouns[LabDoor].Word = "DOOR";

	Nouns[Tape].CanOpen = false;
	Nouns[Tape].CanCarry = true;
	Nouns[Tape].Code = Tape;
	Nouns[Tape].Location = Dorm;
	Nouns[Tape].Description = "A roll of duct tape.";
	Nouns[Tape].IsWeapon = false;
	Nouns[Tape].Weight = 5;
	Nouns[Tape].Word = "TAPE";

	Nouns[Knife].CanOpen = false;
	Nouns[Knife].CanCarry = true;
	Nouns[Knife].Code = Knife;
	Nouns[Knife].Location = Kitchen;
	Nouns[Knife].Description = "A honed kitchen blade.";
	Nouns[Knife].IsWeapon = true;
	Nouns[Knife].Weight = 5;
	Nouns[Knife].Word = "KNIFE";

	Nouns[BrokenLever].CanOpen = false;
	Nouns[BrokenLever].CanCarry = false;
	Nouns[BrokenLever].Code = BrokenLever;
	Nouns[BrokenLever].Location = Hangar;
	Nouns[BrokenLever].Description = "A snapped lever.";
	Nouns[BrokenLever].IsWeapon = false;
	Nouns[BrokenLever].Weight = 100;
	Nouns[BrokenLever].Word = "LEVER";

	Nouns[Wrench].CanOpen = false;
	Nouns[Wrench].CanCarry = true;
	Nouns[Wrench].Code = Wrench;
	Nouns[Wrench].Location = MaintRoom;
	Nouns[Wrench].Description = "A worn torque wrench.";
	Nouns[Wrench].IsWeapon = true;
	Nouns[Wrench].Weight = 15;
	Nouns[Wrench].Word = "WRENCH";

	Nouns[OfficeDrawer].CanOpen = true;
	Nouns[OfficeDrawer].CanCarry = false;
	Nouns[OfficeDrawer].Code = OfficeDrawer;
	Nouns[OfficeDrawer].Location = Office;
	Nouns[OfficeDrawer].Description = "A finely crafted mahogany drawer.";
	Nouns[OfficeDrawer].IsWeapon = false;
	Nouns[OfficeDrawer].Weight = 100;
	Nouns[OfficeDrawer].Word = "DRAWER";

	Nouns[Battery].CanOpen = false;
	Nouns[Battery].CanCarry = true;
	Nouns[Battery].Code = Battery;
	Nouns[Battery].Location = Lab;
	Nouns[Battery].Description = "A gently humming battery.";
	Nouns[Battery].IsWeapon = false;
	Nouns[Battery].Weight = 20;
	Nouns[Battery].Word = "BATTERY";
}

bool GetCommand(std::string Input, std::string& OUTWord1, std::string& OUTWord2)
{
	std::string Buffer;
	std::vector<std::string> Words;
	char Delim = ' ';
	size_t i, j;

	for (i = 0; i < Input.size(); i++)
	{
		if (Input.at(i) != Delim)
		{
			Buffer.insert(Buffer.end(), Input.at(i));
		}
		if (i == Input.size() - 1)
		{
			Words.push_back(Buffer);
			Buffer.clear();
		}
		if (Input.at(i) == Delim)
		{
			Words.push_back(Buffer);
			Buffer.clear();
		}
	}

	//TODO work out removal of 1st character being space
	///Removes blank invalid strings
	for (i = Words.size() - 1; i > 0; i--)
	{
		if (Words.at(i) == "")
		{
			Words.erase(Words.begin() + i);
		}
	}

	//Convert to UPPER
	for (i = 0; i < Words.size(); i++)
	{
		for (j = 0; j < Words.at(i).size(); j++)
		{
			if (islower(Words.at(i).at(j)))
			{
				Words.at(i).at(j) = toupper(Words.at(i).at(j));
			}
		}
	}

	if (Words.size() == 0)
	{
		std::cout << "No command given...\n";
		return false;
	}
	if (Words.size() == 1)
	{
		OUTWord1 = Words.at(0);
		return true;
	}
	if (Words.size() == 2)
	{
		OUTWord1 = Words.at(0);
		OUTWord2 = Words.at(1);
		return true;
	}
	if (Words.size() > 2)
	{
		std::cout << "Your command is too long or started with a space,\nplease break it down into 1 or 2 word commands, if youre struggling type help.\n";
		return false;
	}

	return true;
}

bool Parse(int& OUTLocation, std::string Word1, std::string Word2, Word* Directions, Word* Verbs, Noun* Nouns, Room* Rooms, Character& Player)
{
	//Move player
	if(Word1 == "GO" || Word1 == "MOVE") { Word1 = Word2; }
	for (int i = 0; i < DIRECTIONSNo; i++) 
	{
		if (Word1 == Directions[i].word) 
		{
			if (Rooms[OUTLocation].Exits[Directions[i].Code] > NONE) 
			{
				OUTLocation = Rooms[OUTLocation].Exits[Directions[i].Code];
				std::cout << "You find yourself ";
				LookAround(OUTLocation, Rooms, Directions, Nouns);
				return true;
			}
			else if (Rooms[OUTLocation].Exits[Directions[i].Code] == LOCKED)
			{ 
				std::cout << "The way is locked.\n"; 
				return true;
			}
			else
			{ 
				std::cout << "There is no exit that way...\n";
				return true;
			}
		}
	}

	//Search Word one for valid verb and encode.
	int VerbCode = NONE;
	for (int i = 0; i < VERBSNo; i++) 
	{
		if (Word1 == Verbs[i].word) 
		{
			VerbCode = Verbs[i].Code;
			break;
		}
	}
	//Search Word2 for valid noun and encode. (Nouns must be Word2)
	int NounCode = NONE;
	if (Word2 != "")
	{
		for (int i = 0; i < NOUNSNo; i++) 
		{
			if (Word2 == Nouns[i].Word) 
			{
				NounCode = Nouns[i].Code;
				break;
			}
		}
	}

	if (VerbCode == Look) 
	{
		std::cout << "You are ";
		LookAround(OUTLocation, Rooms, Directions, Nouns);
		return true;
	}
	if (VerbCode == Open) 
	{
		if (NounCode == NONE)
		{
			std::cout << "What do you want to open?\n";
			std::getline(std::cin, Word2);
			//Capitalise word.
			for (unsigned int i = 0; i < Word2.size(); i++)
			{
				if (islower(Word2.at(i)))
				{ Word2.at(i) = toupper(Word2.at(i)); }
			}
			//Check if noun.
			for (int i = 0; i < NOUNSNo; i++)
			{
				if (Word2 == Nouns[i].Word)
				{
					NounCode = Nouns[i].Code;
					break;
				}
			}
		}
		if (NounCode == LabDoor) 
		{
			if (OUTLocation == AmmoStoreS || OUTLocation == Lab)
			{
				if (Nouns[LabDoor].CanOpen == true)
				{
					std::cout << "The heavy door swings open in a whirl of dust, revealing an array of blinking lights in the gloom.\n";
					Nouns[LabDoor].CanOpen = false;
					Nouns[LabDoor].Description = "The laboratory door.\n";
					Rooms[Lab].Exits[North] = AmmoStoreS;
					Rooms[AmmoStoreS].Exits[South] = Lab;
				}
				else { std::cout << "The door is already open...\n"; }
			}
			else { std::cout << "I cant see a door anywhere..\n"; }
			return true;
		}
		if (NounCode == OfficeDrawer) 
		{
			if (OUTLocation == Office) 
			{
				if (Nouns[OfficeDrawer].CanOpen == true)
				{
					std::cout << "You slide the drawer open to reveal a hastily scrawled note.\n";
					Nouns[OfficeDrawer].CanOpen = false;
					Nouns[OfficeDrawer].Description = "An open drawer with the code 420Bi4tch written inside.\n";
				}
				else { std::cout << "The drawer is already open...\n"; }
			}
			else { std::cout << "I cant see a drawer anywhere..\n"; }
			return true;
		}
		else { std::cout << "I dont think you can open that...\n"; }
		return true;
	}
	if (VerbCode == Help)
	{
		std::cout << "This is Laurk, a text based adventure.\n";
		std::cout << "Interact with the world around you using basic verbs and nouns,\n";
		std::cout << "using a maximum of two words.\n";
		std::cout << "VERBS:\n";
		for (int i = 0; i < VERBSNo; i++)
		{ std::cout << Verbs[i].word << std::endl; }
		return true;
	}
	std::cout << "No valid command recognised, type help if youre stuck.\n";
	return false;
}

void LookAround(int Location, Room* Rooms, Word* Directions, Noun* Nouns)
{
	//"You find yourself" after moving, "You are" when look(around) evoked by player
	std::cout << "standing in " << Rooms[Location].Description << std::endl;
	int NounCount = 0;
	std::cout << "You look around and see:\n";
	for (int i = 0; i < NOUNSNo; i++) 
	{
		if (Location == Nouns[i].Location)
		{
			std::cout << Nouns[i].Description << std::endl;
			NounCount++;
		}
	}
	if (NounCount == 0)
	{ std::cout << "Nothing interesting...\n\n"; }
	else { std::cout << std::endl; }
	std::cout << "There is an exit:\n";
	int LockedDirection = 0;
	for (int i = 0; i < DIRECTIONSNo; i++)
	{
		if (Rooms[Location].Exits[i] > NONE)
		{
			//Capitalise direction
			std::cout << Directions[i].word[0];
			for (unsigned int j = 1; j < Directions[i].word.size(); j++)
			{
				char Lower = tolower(Directions[i].word[j]);
				std::cout << Lower;
			}
			std::cout << " to " << Rooms[Rooms[Location].Exits[i]].Name << std::endl;
		}
		else if (Rooms[Location].Exits[i] == LOCKED)
		{ LockedDirection = Directions[i].Code; }
	}
	//Checking for locked doors, if multiple needed, use a LockedDirection array.
	if (LockedDirection > 0)
	{
		std::cout << "The way ";
		for (unsigned int j = 0; j < Directions[LockedDirection].word.size(); j++)
		{
			char Lower = tolower(Directions[LockedDirection].word[j]);
			std::cout << Lower;
		}
		std::cout << " is locked\n";
		std::cout << std::endl;
	}
}
