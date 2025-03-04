#pragma once
#include <string>
class Plugboard
{
private:
	char plugPairs[10][2];
	int pairNum;

public:
	//constructor
	Plugboard(std::string);
	//destructor
	~Plugboard();

	//functions
	char swapLetters(char);

};
