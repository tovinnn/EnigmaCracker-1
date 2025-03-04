#include "RotorManager.h"

RotorManager::RotorManager() {
	
}

RotorManager::~RotorManager() {

}

char RotorManager::encrypt(char letter) {
	char temp;
	//Rotate rotors
	for (int i = 2; i >= 0; --i) {
		rotor[rotorsUsed[i]].incPos();
		//if next rotor needs rotated
		if (rotor[i].getRotate()) {
			//the second rotor "double steps" when turning the slowest rotor in a real enigma machine
			if (i == 1) {
				rotor[1].incPos();
			}
			continue;
		}
		else {
			//stop rotating
			break;
		}
	}

	//encode forward
	for (int i = 0; i < 3; ++i) {
		temp = rotor[rotorsUsed[i]].encode(letter, false);
		letter = temp;
	}

	//reflect letter back - this means encoding/decoding can use same "wires"
	temp = reflector[reflectorNum].encode(letter, false);
	letter = temp;

	//encode backwards
	for (int i = 2; i >= 0; --i) {
		temp = rotor[rotorsUsed[i]].encode(letter, true);
		letter = temp;
	}

	return letter;
}

void RotorManager::setRotors() {
	//all this rotor spaghetti wiring was found on wikipedia - (08/05/2021)
	//https://en.wikipedia.org/wiki/Enigma_rotor_details
	//This uses "Enigma 1" and "M3 Army" rotor details
	//debug  fillerfiller("ABCDEFGHIJKLMNOPQRSTUVWXYZ", notchPos);
	rotor[0].setSpaghetti("EKMFLGDQVZNTOWYHXUSPAIBRCJ", 17); //R
	rotor[1].setSpaghetti("AJDKSIRUXBLHWTMCQGZNPYFVOE", 5); //F
	rotor[2].setSpaghetti("BDFHJLCPRTXVZNYEIWGAKMUSQO", 22); //W
	rotor[3].setSpaghetti("ESOVPZJAYQUIRHXLNFTGKDCMWB", 10); //K
	rotor[4].setSpaghetti("VZBRGITYUPSDNHLXAWMJQOFECK", 0); //A

	//reflector information found here
	//https://www.cryptomuseum.com/crypto/enigma/wiring.htm#12 - (10/05/2021)
	reflector[0].setSpaghetti("EJMZALYXVBWFCRQUONTSPIKHGD", -1); //this never rotates
	reflector[1].setSpaghetti("YRUHQSLDPXNGOKMIEBFZCWVJAT", -1); //this never rotates
	reflector[2].setSpaghetti("FVPJIAOYEDRZXWGCTKUQSBNMHL", -1); //this never rotates
}

void RotorManager::addRotor(int i, int num) {
	rotorsUsed[i] = num;
}

int RotorManager::getRotor(int i) {
	return rotorsUsed[i];
}

//this just calls a small
void RotorManager::intSetPos(int i, int pos) {
	rotor[i].setPos(pos);
}

void RotorManager::setReflector(int num) {
	reflectorNum = num;
}

void RotorManager::setRotorOffset(int notch, int i) {
	rotor[rotorsUsed[i]].setOffset(notch);
}