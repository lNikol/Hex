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
			for (short int i = 0; i < line.size(); i++) {
				switch (line[i])
				{
				case 'r': {
					hex.RED_PAWNS++;
					hex.PAWNS_NUMBER++;
					break;
				}
				case 'b': {
					hex.BLUE_PAWNS++;
					hex.PAWNS_NUMBER++;
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
		}

	}
	file.close();
}
