#include "Hex.h"
#include <iostream>
#include <fstream>
using namespace std;

Hex::Hex() {
}

void Hex::setHexBoardSize(const short& size) {

}

void Hex::setPlayerSymbol(char s, const short& line, const short& cell) {
	
}

bool Hex::get_IS_BOARD_CORRECT() {
	if (BLUE_PAWNS + 1 == RED_PAWNS || BLUE_PAWNS == RED_PAWNS) {
		IS_BOARD_CORRECT = true;
		//cout << "YES" << endl;
	}
	else {
		IS_BOARD_CORRECT = false;
		//cout << "NO" << endl;
	}
	return IS_BOARD_CORRECT;
}

void Hex::resetVisited() {
	short size = lineCounter / 2;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			board[i][j].visited = false;
			board[i][j].toBeVisited = false; // zastanowic sie nad tym czy warto zostawic
		}
	}
}

vector<Cell*> Hex::getNeighbors(const Cell* cell) { 
	vector<Cell*> neighbors;
	short size = lineCounter / 2;

	short dLines[] = { -1, 0, 1, 1, 0, -1 };
	short dPoses[] = { -1, -1, 0, 1, 1, 0 };
	
	for (short i = 0; i < 6; i++) {
		short newRow = cell->line + dLines[i];
		short newCol = cell->pos + dPoses[i];
		if (newRow >= 0 && newRow < size && newCol >= 0 && newCol < size) {
			neighbors.insert(neighbors.begin(), &board[newRow][newCol]);
		}
	}

	return neighbors;
}

bool Hex::beforeDFS(vector<vector<Cell>>& board_, const short& state, short& whoWon_) {
	// dla czerwonego gracza z gornego do dolnego
	// pseudo win:
	// 0 - nic
	// 1 - red win (w rzecywistosci wygral niebieski gracz)
	// 2 - blue win (w rzecywistosci wygral czerwony gracz)
	bool changed = false;
	if (state != 1) {
		for (auto c : board_[0]) {
			if (c.symbol == 'r') {
				changed = true;
				if (DFS(&c, true)) {
					whoWon_ = 1;
					return true;
				}
			}
			else {
				if (changed) {
					resetVisited();
					changed = false;
				}
			}
		}
		changed = false;
	}
	if (state != 2) {
		for (int i = 0; i < lineCounter / 2; i++) {
			if (board_[i][0].symbol == 'b') {
				changed = true;
				if (DFS(&board_[i][0], false)) {
					whoWon_ = 2;
					return true;
				}
			}
			else {
				if (changed) {
					resetVisited();
					changed = false;
				}
			}
		}
		whoWon_ = 0;
	}
	return false;
}

bool Hex::DFS(Cell* cell, bool isRed) {
	// przed wywolaniem dfs, zrobic for, ktory bedzie chodzil po wszystkim komorkach
	// i jesli dfs = false wywolac kolejny dfs dla kolejnej komorki, ale przed tym wywolac resetVisited
	cell->visited = true;
	vector<Cell*> neighbors = getNeighbors(cell);
	for (auto* c : neighbors) {
		if (c->symbol == cell->symbol && c->visited == false && c->symbol!=' ') {
			c->visited = true;
			if (c->line == (lineCounter) / 2 - 1 && isRed) {
				// ten warunek dla gracza czerwonego od lewej granicy do prawej
				// czerwony gracz
				return true;
			}
			else if (c->pos == (lineCounter) / 2 - 1 && !isRed) {
				// niebieski gracz
				return true;
			}
			if (DFS(c, isRed)) {
				return true;
			}
		}
	}
	if (lineCounter / 2 - 1 == 0) {
		if (isRed) {
			return true;
		}
		else {
			return false;
		}
	}
	return false;

}

void Hex::IS_BOARD_POSSIBLE(ofstream& file, const short& state) {
	if (get_IS_BOARD_CORRECT()) {
		if (PAWNS_NUMBER == 0) {
			if (file.is_open()) {
				file << "YES" << endl << endl;
			}
			//cout << "YES" << endl;
			return;
		}
		if (!beforeDFS(board, state, whoWon)) {
			if (file.is_open()) {
				file << "YES" << endl << endl;
			}
			//cout << "YES" << endl;
			return;
		}
		Hex temp = *this;

		switch (whoWon) {
		case 0: { // TIE
			if (file.is_open()) {
				//file << "NO" << endl << endl;
			}
			//cout << "NO" << endl;
			break;
		}
		case 1: { // RED
			if (BLUE_PAWNS + 1 == RED_PAWNS) {
				bool isEnd = false;
				/*if (file.is_open()) {
					file << "YES" << endl << endl;
				}*/

				for (int i = 0; i < temp.lineCounter / 2; ++i) {
					for (int j = 0; j < temp.lineCounter / 2; ++j) {
						if (temp.board[i][j].symbol == 'r' && !isEnd) {
							temp.board[i][j].symbol = ' ';
							if (!temp.beforeDFS(temp.board, 2, temp.whoWon)) {
								if (file.is_open()) {
									file << "YES" << endl << endl;
								}
								isEnd = true;
								//cout << "YES" << endl;
							}
							temp.resetVisited();
						}
					}
				}

				if (file.is_open() && !isEnd) {
					file << "NO" << endl << endl;
				}
				//cout << "NO" << endl;
			}
			break;
		}
		case 2: {// BLUE
			if (BLUE_PAWNS + 1 == RED_PAWNS) {
				if (file.is_open()) {
					file << "NO" << endl << endl;
				}
				//cout << "NO" << endl;
			}
			else if (BLUE_PAWNS == RED_PAWNS) {
				bool isEnd = false;
				/*if (file.is_open()) {
					file << "YES" << endl << endl;
				}*/

				for (int i = 0; i < temp.lineCounter / 2; ++i) {
					for (int j = 0; j < temp.lineCounter / 2; ++j) {
						if (temp.board[j][i].symbol == 'b' && !isEnd) {
							temp.board[j][i].symbol = ' ';
							if (!temp.beforeDFS(temp.board, 1, temp.whoWon)) {
								if (file.is_open()) {
									file << "YES" << endl << endl;
								}
								isEnd = true;
								//cout << "YES" << endl;
								break;
							}
							temp.resetVisited();
						}
					}
				}

				if (file.is_open() && !isEnd) {
					file << "NO" << endl << endl;
				}
				//cout << "NO" << endl;
			}
			break;
		}
		}
	}
	else {
		if (file.is_open()) {
			file << "NO" << endl << endl;
		}
		//cout << "NO" << endl;
	}
}