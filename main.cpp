#include <iostream>
#include <string>
#include <fstream>
#include "Hex.h"
using namespace std;

int main()
{
	ofstream file("temp.txt");
	Hex hex;
	string line;
	short state = 0;
	while (getline(cin, line)) {
		if (line == "BOARD_SIZE") {
			file << (hex.lineCounter + 1) / 2 << endl << endl;
			//printf("%d\n\n", (hex.lineCounter + 1) / 2);
			hex.~Hex(); 
			hex = Hex();
		}
		else if (line == "PAWNS_NUMBER") {
			file << hex.PAWNS_NUMBER << endl << endl;
			//printf("%d\n\n", hex.PAWNS_NUMBER);
			hex.~Hex(); 
			hex = Hex();
		}
		else if (line == "IS_BOARD_CORRECT") {
			if (hex.get_IS_BOARD_CORRECT()) {
				file << "YES\n\n";
				//printf("YES\n\n");
			}
			else {
				file << "NO\n\n";
				//printf("NO\n\n");
			}
			hex.~Hex(); hex = Hex();
		}
		else if (line == "IS_GAME_OVER") {
			if (hex.IS_GAME_OVER(state)) {
				switch (hex.whoWon) {
				case 0:
					file << "NO\n\n";
					//printf("NO\n\n");
					break;
				case 1: {
					file << "YES RED\n\n";
					//printf("YES RED\n\n");
					break;
				}
				case 2: {
					file << "YES BLUE\n\n";
					//printf("YES BLUE\n\n");
					break;
				}
				}
			}
			else {
				file << "NO\n\n";
				//printf("NO\n\n");
			}
			hex.~Hex(); 
			hex = Hex();
		}
		else if (line == "IS_BOARD_POSSIBLE") {
			if (hex.PAWNS_NUMBER == 0) {
				file << "YES\n\n";
				//printf("YES\n\n");
			}
			else {
				if (hex.IS_BOARD_POSSIBLE(state)) {
					file << "YES\n\n";
					//printf("YES\n\n");
				}
				else {
					file << "NO\n\n";
					//printf("NO\n\n");
				}
			}
			hex.~Hex(); 
			hex = Hex();
		}
		
		else if (line == "CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT") {
			if (hex.CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT(state)) {
				file << "YES\n";
				//printf("YES\n");
			}
			else {
				file << "NO\n";
				//printf("NO\n");
			}
			hex.whoWon = -1;
		}
		else if (line == "CAN_RED_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT") {
			if (hex.CAN_RED_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT(state)) {
				file << "YES\n";
				//printf("YES\n");
			}
			else {
				file << "NO\n";
				//printf("NO\n");
			}
			hex.whoWon = -1;
		}
		else if (line == "CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT") {
			if (hex.CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT(state)) {
				file << "YES\n";
				//printf("YES\n");
			}
			else {
				file << "NO\n";
				//printf("NO\n");
			}
			hex.whoWon = -1;
		}
		else if (line == "CAN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT") {
			if (hex.CAN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT(state)) {
				file << "YES\n\n";
				//printf("YES\n\n");
			}
			else {
				file << "NO\n\n";
				//printf("NO\n\n");
			}
			hex.~Hex(); 
			hex = Hex();
		}
		
		else if (line == "CAN_RED_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT") {

			if (hex.CAN_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT(state, 'r', true, hex.emptyCounter)) {
				file << "YES\n";
				//printf("YES\n");
			}
			else {
				file << "NO\n";
				//printf("NO\n");
			}
			hex.whoWon = -1;
		}
		else if (line == "CAN_BLUE_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT") {
			if (hex.CAN_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT(state, 'b', false, hex.emptyCounter)) {
				file << "YES\n";
				//printf("YES\n");
			}
			else {
				file << "NO\n";
				//printf("NO\n");
			}
			hex.whoWon = -1;
		}
		else if (line == "CAN_RED_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT") {

			if (hex.CAN_RED_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT(state)) {
				file << "YES\n";
				//printf("YES\n");
			}
			else {
				file << "NO\n";
				//printf("NO\n");
			}
			hex.whoWon = -1;
		}
		else if (line == "CAN_BLUE_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT") {
			if (hex.CAN_BLUE_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT(state)) {
				file << "YES\n\n";
				//printf("YES\n\n");
			}
			else {
				file << "NO\n\n";
				//printf("NO\n\n");
			}
			hex.~Hex();
			hex = Hex();
		}		
		else {
			if (line == "" || line.find("---") != string::npos) {
				continue;
			}
			short tagCounter = 0; 
			if (line[0] == '<' || line[1] == '<') {
				hex.isSecondPart = true;
			}
			if (hex.isSecondPart) {
				for (char c : line) { if (c == '<') ++tagCounter; }
			}
			short counter; // liczy linii i dzieki niemu 
			// odpowiednio dodaje Cell do hex 11x11, ktory jest tablica
			if (hex.oldTags > tagCounter && hex.isSecondPart) {
				if (!hex.isMaxOldSet) {
					hex.maxOldTags = hex.oldTags;
					hex.isMaxOldSet = true;
				}
				counter = hex.maxOldTags - tagCounter;
			}
			else {
				counter = 0;
			}
			for (short i = 0; i < line.size(); ++i) {
				switch (line[i])
				{
				case ' ': {
					continue;
				}
				case '<': {
					char cell[5];
					for (short j = 0; j < 5; ++j) {
						cell[j] = line[i + j];
					}
					i += 4; // symbol '>' in line

					switch (cell[2]) {
					case 'r': {
						hex.board[counter][hex.indexes[counter]++] = new Cell(cell[2], counter, hex.indexes[counter]);
						++hex.RED_PAWNS;
						++hex.PAWNS_NUMBER;
						break;
					}
					case 'b': {
						hex.board[counter][hex.indexes[counter]++] = new Cell(cell[2], counter, hex.indexes[counter]);
						++hex.BLUE_PAWNS;
						++hex.PAWNS_NUMBER;
						break;
					}
					case ' ': {
						short size_ = hex.indexes[counter]++;
						hex.board[counter][size_] = new Cell(cell[2], counter, size_);
						hex.emptyPlaces[hex.emptyCounter++] = hex.board[counter][size_];
					}
					default: {  
						break;
					}
					}
					++counter;
					break;
				}
				default: {
					break;
				}
				}
			}
			++hex.lineCounter;
			hex.size = (hex.lineCounter + 1) / 2;
			hex.emptyCounter2 = hex.emptyCounter;
			hex.oldTags = counter;
		}
	}
  	file.close();
}