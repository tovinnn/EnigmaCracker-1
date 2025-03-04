#pragma once
#include "Plugboard.h"
#include "Rotor.h"

class RotorManager
{
private:
	//class definitions
	Rotor rotor[5];
	Rotor reflector[3];
	int rotorsUsed[3];
	int reflectorNum;

public:
	//constructor
	RotorManager();
	//destructor
	~RotorManager();

	//functions
	char encrypt(char);
	void setRotors();
	void addRotor(int, int);
	int getRotor(int);
	void intSetPos(int, int); //this is just a passthough
	void setReflector(int);
	void setRotorOffset(int, int);

};

