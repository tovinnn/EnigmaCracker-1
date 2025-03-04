#include <iostream>
#include <string>
#include <fstream>
#include "RotorManager.h"

int main() {
	std::string input;
	std::string output = "";
	char letter;
	bool verified = false;

	//plugboard
	std::cout << "Please insert the plugboard pairs (format XXYYZZ).\n";
	while (!verified) { //Verifying input
		verified = true;
		std::getline(std::cin, input);
				
		//if greater than 10 pairs or not in pairs, reject string.
		if (input.size() == 0 || input.size() > 20) {
			std::cout << "No more than 10 pairs allowed.\n";
			verified = false;
		} else if (input.size() % 2) {
			std::cout << "Please ensure each letter has a pair.\n";
			verified = false;
		}
		else {
			for (int i = 0; i < input.size(); ++i) {
				//if not a capital letter, reject string
				if ((int)input[i] < 65 || (int)input[i] > 90) {
					std::cout << "Sorry, not a valid input (capital letters only).\n";
					verified = false;
					break;
				}
			}
		}
	}
	Plugboard board(input);
	RotorManager man;
	man.setRotors();

	for (int i = 0; i < 3; ++i) {
		verified = false;
		while (!verified) {
			verified = true;
			std::cout << "Rotor in position " << i + 1 << ": ";
			std::getline(std::cin, input);

			for (int j = 0; j < i; ++j) {
				if (std::stoi(input) < 1 || std::stoi(input) > 5){
					std::cout << "Error: You can only use rotors 1 to 5\n";
					verified = false;
					break;
				}
				else if (std::stoi(input) - 1 == man.getRotor(j)) {
					std::cout << "Error: You can't have the same rotor twice!\n";
					verified = false;
					break;
				}
			}

			if (verified) {
				man.addRotor(i, std::stoi(input) - 1);
			}
		}
	}

	for (int i = 0; i < 3; ++i) {
		verified = false;
		while (!verified) {
			verified = true;
			std::cout << "Rotor " << i + 1 << " starting position: ";
			std::getline(std::cin, input);
			if (std::stoi(input) < 1 || std::stoi(input) > 26) {
				verified = false;
				std::cout << "Error: Invalid position.\n";
			}
		}
		man.intSetPos(i, std::stoi(input) - 1);
	}
	std::cout << "Which reflector would you like to use?\nUKW-(A), (B), (C)?\n";
	verified = false;
	while (!verified) {
		std::getline(std::cin, input);
		if (input.size() > 1) {
			std::cout << "Please only inset 1 character.\n";
			continue;
		}
		else if (input[0] < 65 || input[0] > 67) {
			std::cout << "That is not A, B or C.\n";
			continue;
		}
		else {
			man.setReflector(input[0] - 65);
			verified = true;
		}
	}
	verified = false;
	std::cout << "Would you like to adjust ring settings (Yes/No)?\n";
	while (!verified) {
		std::getline(std::cin, input);
		if (input == "No") {
			break;
		}
		else if (input == "Yes") {
			for (int i = 0; i < 3; ++i) {
				verified = false;
				std::cout << "Rotor " << i + 1 << " ring setting: ";
				while (!verified) {
					verified = true;
					std::getline(std::cin, input);
					if (std::stoi(input) < 1 || std::stoi(input) > 26) {
						std::cout << "That is not a number between 1 and 26\n";
						verified = false;
						continue;
					}
					else {
						man.setRotorOffset(std::stoi(input), i);
					}
				}
			}
		}
		else {
			std::cout << "Error: Not 'Yes' or 'No'.\n";
		}
	}
	

	std::cout << "Please insert the message you would like to encrypt/decrypt.\n";
	std::getline(std::cin, input); //this is used to capture spaces

	for (int i = 0; i < input.size(); ++i) {
		
		letter = std::toupper(input[i]);

		if ((int)letter > 64 && (int)letter < 91) {
			//Functions to manipulate letters
			letter = board.swapLetters(letter);
			letter = man.encrypt(letter);
			letter = board.swapLetters(letter);
		}
		else if (letter == ' ') {
			//adds a space to the output - not accurate but looks nicer
			output.push_back(' ');
			continue;
		} else {
			//Ignore the character if not A-Z or a space
			continue;
		}

		//add new character to string
		output.push_back(letter);
	}
	
	//temp
	std::cout << "Your new message is now:" << std::endl;
	std::cout << output;

	return 0;

}