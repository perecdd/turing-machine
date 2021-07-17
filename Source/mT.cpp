#include <iostream>
#include "database.h"
#include <fstream>

int main() {
	
	try {
		std::string file0_string;
		std::string file1_string;
		
		std::cout << "Please, enter program file name: ";
		std::getline(std::cin, file0_string);
		std::fstream file0(file0_string.c_str());
		if (!file0) throw std::invalid_argument("Could not open the file with the machine's program");

		database bd;
		file0 >> bd;

		std::cout << "Please, enter tape file name: ";
		std::getline(std::cin, file1_string);
		std::fstream file1(file1_string.c_str());
		if (!file1) throw std::invalid_argument("Could not open the file with the machine's tape");

		tape tape_;

		std::string initial_state;
		std::cout << "Please, enter initial state: ";
		std::cin >> initial_state;


		std::ofstream tmp("log.txt");
		
		while (file1 >> tape_) {

			tmp << "Input:";
			tape_.Output(tmp);
			tmp << '\n';
			
			emulate(bd, tape_, initial_state, tmp);

			tmp << "Output:";
			tape_.Output(tmp);
			tmp << "\n\n";
		}
		std::cout << "The program has successfully completed its work\n";
	}

	catch (const std::exception& ex)
	{
		std::cout << ex.what();
	}
	std::cin.get();
	return 0;
}
