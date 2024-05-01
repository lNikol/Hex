#include <iostream>
#include <string>
#include <fstream>
#include "Hex2.h"
using namespace std;

int main()
{
	ofstream file("temp.txt");
	Hex2 hex;
	short emptyCounter = hex.board.emptyCounter;
	string line;
	short state = 0;
	while (getline(cin, line)) {
		if (line == "BOARD_SIZE") {
			// JESLI NIE DZIALA, TO MUSI BYC LINECOUNTER/2, A NIE (LINECOUNTER+1)/2
			file << hex.board.size << endl << endl;
			//printf("%d\n\n", (hex.board.size);
			hex.board.~Board();
			hex = Hex2();
		}
		else if (line == "PAWNS_NUMBER") {
			file << hex.board.PAWNS_NUMBER << endl << endl;
			//printf("%d\n\n", hex.board.PAWNS_NUMBER);
			hex.board.~Board();
			hex = Hex2();
		}
		else if (line == "IS_BOARD_CORRECT") {
			if (hex.board.get_IS_BOARD_CORRECT()) {
				file << "YES\n\n";
				//printf("YES\n\n");
			}
			else {
				file << "NO\n\n";
				//printf("NO\n\n");
			}
			hex.board.~Board();
			hex = Hex2();
		}
		else if (line == "IS_GAME_OVER") {
			switch (hex.board.IS_GAME_OVER(state)) {
			case INCORRECT:
			case NONE:
				file << "NO\n\n";
				//printf("NO\n\n");
				break;
			case RED: {
				file << "YES RED\n\n";
				//printf("YES RED\n\n");
				break;
			}
			case BLUE: {
				file << "YES BLUE\n\n";
				//printf("YES BLUE\n\n");
				break;
			}
			}
			hex.board.~Board();
			hex = Hex2();
		}
		else if (line == "IS_BOARD_POSSIBLE") {
			if (hex.board.IS_BOARD_POSSIBLE(state)) {
				file << "YES\n\n";
				//printf("YES\n\n");
			}
			else {
				file << "NO\n\n";
				//printf("NO\n\n");
			}
			hex.board.~Board();
			hex = Hex2();
		}
		else if (line == "CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT") {
			emptyCounter = hex.board.emptyCounter;
			if (hex.CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT(state, emptyCounter) == RED) {
				file << "YES\n";
				//printf("YES\n");
			}
			else {
				file << "NO\n";
				//printf("NO\n");
			}
		}
		else if (line == "CAN_RED_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT") {
			if (hex.CAN_RED_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT(state, emptyCounter) == RED) {
				file << "YES\n";
				//printf("YES\n");
			}
			else {
				file << "NO\n";
				//printf("NO\n");
			}
		}
		else if (line == "CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT") {
			if (hex.CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT(state, emptyCounter) == BLUE) {
				file << "YES\n";
				//printf("YES\n");
			}
			else {
				file << "NO\n";
				//printf("NO\n");
			}
		}
		else if (line == "CAN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT") {
			if (hex.CAN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT(state, emptyCounter) == BLUE) {
				file << "YES\n\n";
				//printf("YES\n\n");
			}
			else {
				file << "NO\n\n";
				//printf("NO\n\n");
			}
			hex.board.~Board();
			hex = Hex2();
		}	
		else if (line == "CAN_RED_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT") {
			emptyCounter = hex.board.emptyCounter;
			if (hex.CAN_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT(state, RED, true, emptyCounter) == RED) {
				file << "YES\n";
				//printf("YES\n");
			}
			else {
				file << "NO\n";
				//printf("NO\n");
			}
		}
		else if (line == "CAN_BLUE_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT") {
			if (hex.CAN_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT(state, BLUE, false, emptyCounter) == BLUE) {
				file << "YES\n";
				//printf("YES\n");
			}
			else {
				file << "NO\n";
				//printf("NO\n");
			}
		}
		else if (line == "CAN_RED_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT") {
			if (hex.CAN_RED_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT(state, emptyCounter) == RED) {
				file << "YES\n";
				//printf("YES\n");
			}
			else {
				file << "NO\n";
				//printf("NO\n");
			}
		}
		else if (line == "CAN_BLUE_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT") {
			if (hex.CAN_BLUE_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT(state, emptyCounter) == BLUE) {
				file << "YES\n\n";
				//printf("YES\n\n");
			}
			else {
				file << "NO\n\n";
				//printf("NO\n\n");
			}
			hex.board.~Board();
			hex = Hex2();
		}		
		else {
			if (line == "") {
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
			// odpowiednio dodaje pawn do hex 11x11, ktory jest tablica
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
					char pawn = line[i + 2]; // +2 pobieram symbol z < >
					i += 4; // symbol '>' in line

					switch (pawn) {
					case 'r': {
						hex.board.board[counter][hex.board.indexes[counter]++] = new Pawn(pawn, counter, hex.board.indexes[counter]);
						++hex.board.RED_PAWNS;
						++hex.board.PAWNS_NUMBER;
						break;
					}
					case 'b': {
						hex.board.board[counter][hex.board.indexes[counter]++] = new Pawn(pawn, counter, hex.board.indexes[counter]);
						++hex.board.BLUE_PAWNS;
						++hex.board.PAWNS_NUMBER;
						break;
					}
					case ' ': {
						short size_ = hex.board.indexes[counter]++;
						hex.board.board[counter][size_] = new Pawn(pawn, counter, size_);
						hex.board.emptyPlaces[hex.board.emptyCounter++] = hex.board.board[counter][size_];
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
			hex.board.size = hex.lineCounter / 2;
			hex.oldTags = counter;
		}
 	}
  	file.close();
}