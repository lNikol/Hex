#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Hex.h"
using namespace std;

int main()
{
	ofstream file("temp.txt");
	Hex hex;
	string line;
	while (getline(cin, line)) {
		if (line == "BOARD_SIZE") {
			//cout << hex.hex.size() / 2 << endl;
			if (file.is_open()) {
				file << hex.hex.size() / 2 << endl << endl;
			}
			hex = Hex();
		}
		else if (line == "PAWNS_NUMBER") {
			//cout << hex.PAWNS_NUMBER << endl;
			if (file.is_open()) {
				file << hex.PAWNS_NUMBER << endl << endl;
			}
			hex = Hex();
		}
		else if (line == "IS_BOARD_CORRECT") {
			if (hex.get_IS_BOARD_CORRECT()) {
				if (file.is_open()) {
					file << "YES" << endl << endl;
				}
			}
			else {
				if (file.is_open()) {
					file << "NO" << endl << endl;
				}
			}
			hex = Hex();
		}
		else if (line == "IS_GAME_OVER") {
			if (hex.get_IS_BOARD_CORRECT()) {

			}
			hex = Hex();

		}
		else if (line == "IS_BOARD_POSSIBLE") {
			if (hex.get_IS_BOARD_CORRECT()) {

			}
			hex = Hex();

		}
		else if (line == "CAN_RED_WIN_IN_N_MOVE_WITH_NAIVE_OPPONENT") {
			if (hex.get_IS_BOARD_CORRECT()) {

			}
			hex = Hex();

		}
		else if (line == "CAN_RED_WIN_IN_N_MOVE_WITH_PERFECT_OPPONENT") {
			if (hex.get_IS_BOARD_CORRECT()) {

			}
			hex = Hex();

		}
		else {
			int tagCounter = 0; for (char c : line) { if (c == '<') tagCounter++; }
			short counter;
			if (hex.oldTags > tagCounter) {
				if (!hex.isMaxOldSet) {
					hex.maxOldTags = hex.oldTags;
					hex.isMaxOldSet = true;
				}
				counter = hex.maxOldTags - tagCounter;
			}
			else {
				counter = 0;
			}
			for (short int i = 0; i < line.size(); i++) {
				switch (line[i])
				{
				
				case '<': {
					char cell[5];
					for (int j = 0; j < 5; j++) {
						cell[j] = line[i + j];
					}
					i += 4; // symbol '>' in cell

					switch (cell[2]) {
					case 'r': {
						hex.map[counter].insert(hex.map[counter].begin(), Cell(cell[2]));
						hex.RED_PAWNS++;
						hex.PAWNS_NUMBER++;
						break;
					}
					case 'b': {
						hex.map[counter].insert(hex.map[counter].begin(), Cell(cell[2]));
						hex.BLUE_PAWNS++;
						hex.PAWNS_NUMBER++;
						break;
					}
					case ' ': {
						hex.map[counter].insert(hex.map[counter].begin(), Cell(cell[2]));
						break;
					}
					default: {
						break;
					}
					}
					counter++;
					break;
				}
				
				default: {
					break;
				}
				}
			}
			if (line != "") {
				hex.hex.push_back(line);
			}
			hex.oldTags = counter;
		}

	}
	file.close();
}
