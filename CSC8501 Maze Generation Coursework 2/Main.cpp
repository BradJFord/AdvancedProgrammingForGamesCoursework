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
			cout << "3. Read And Print Player Progress From File" << endl;
			cout << "4. Generate 100 mazes in a size range" << endl;
			cout << "5. Exit" << endl;

			cin >> option;

			if (option == 1) {
				optionSelected = true;
				interface.generateRandomMaze();

				if (interface.getMaze().players.size() > 0) {

					if (interface.playGame()) {
						interface.getMaze().playerManager();
						interface.printProgress();
					}
				}
			}
			else if (option == 2) {
				optionSelected = true;
				interface.readMaze();
			}
			else if (option == 3) {
				optionSelected = true;
				interface.readPlayerProgressFile();

			}
			else if (option == 4) {
				optionSelected = true;
				interface.generateOneHundredMazes();
			}
			else if (option == 5) {
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
