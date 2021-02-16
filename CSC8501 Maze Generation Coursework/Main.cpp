#include "UserInterface.h"
int main() {
	srand(time(NULL));
	bool endFlag = false;
	UserInterface interface;
	while (!endFlag) {
		bool optionSelected = false;
		while (!optionSelected) {
			int option;
			cout << "1. Randomly Generate Maze" << endl;
			cout << "2. Read Maze From File" << endl;
			cout << "3. Exit" << endl;

			cin >> option;

			if (option == 1) {
				optionSelected = true;
				interface.generateRandomMaze();
			}
			else if (option == 2) {
				optionSelected = true;
				interface.readMaze();
			}
			else if (option == 3) {
				endFlag = true;
				optionSelected = true;
			}
			else {
				cout << "Please enter a valid option." << endl;
				cout << '/n' << endl;
			}

		}
	}
	return 0;
}