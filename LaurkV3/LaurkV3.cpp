// LaurkV3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//Game loop and main functions.
void GameIntro();

//User input handling
bool Parse(std::string, std::string&, std::string&);

int main()
{
	GameIntro();
	std::string Input, Word1, Word2;
	while (Word1 != "QUIT")
	{
		Input.clear();
		std::cout << "What next o wise one?\n";
		std::getline(std::cin, Input);
		std::cout << "Your raw input was: " << Input << std::endl;
		Word1.clear();
		Word2.clear();
		Parse(Input, Word1, Word2);

		std::cout << "Your parsed input is:\n" << Word1 << std::endl << Word2 << std::endl;
	}
	return 0;
}

void GameIntro()
{
	std::cout << "Welcome to Laurk, totally not a rip-off of anything\n";
	std::cout << "Would you like to begin a new adventure?\n"; //TODO add save game resource file
}

//Splits input by space stored in 'delim', stores in vector and then outputs to words1,2.
bool Parse(std::string Input, std::string& OUTWord1, std::string& OUTWord2)
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

	//Remove blank or punctuaiton invalid strings
	for (i = Words.size() - 1; 1 > 0; i--)
	{
		if (Words.at(i) == " ")
		{
			Words.at(i).erase();
		}
	}

	//Convert to UPPER
	for (i = 0; i < Words.size(); i++)
	{
		for (j = 0; j < Words.at(i).size(); j++)
		{
			if(islower(Words.at(i).at(j)))
			{ Words.at(i).at(j) = toupper(Words.at(i).at(j)); }
		}
	}

	if (Words.size() > 1)
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
		std::cout << "Command too long, please break it down into 1 or 2 word commands, if youre struggling type help.\n";
		return false;
	}

	return true;
}
