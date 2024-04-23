#include "Hex.h"
#include <iostream>
#include <fstream>
using namespace std;

Hex::Hex() {
}

void Hex::setPlayerSymbol(char s, const short& line, const short& cell) {
	
}

bool Hex::get_IS_BOARD_CORRECT(ofstream& file) {
	if (BLUE_PAWNS + 1 == RED_PAWNS || BLUE_PAWNS == RED_PAWNS) {
		IS_BOARD_CORRECT = true;
		//cout << "YES" << endl;
	}
	else {
		IS_BOARD_CORRECT = false;
		if (file.is_open()) {
			file << "NO" << endl << endl;
		}
		//cout << "NO" << endl << endl;
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

bool Hex::beforeDFS(vector<vector<Cell>>& board, const short& state) {
	// dla czerwonego gracza z gornego do dolnego
	// pseudo win:
	// 0 - nic
	// 1 - red win (w rzecywistosci wygral niebieski gracz)
	// 2 - blue win (w rzecywistosci wygral czerwony gracz)
	bool changed = false;
	if (state != 1) {
		for (auto c : board[0]) {
			if (c.symbol == 'r') {
				changed = true;
				if (DFS(&c, true)) {
					whoWon = 1;
					resetVisited();
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
			if (board[i][0].symbol == 'b') {
				changed = true;
				if (DFS(&board[i][0], false)) {
					whoWon = 2;
					resetVisited();
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
	}
	whoWon = 0;
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

bool Hex::IS_GAME_OVER(const short& state, ofstream& file) {
	if (get_IS_BOARD_CORRECT(file)) {
		return beforeDFS(board, state);
	}
	return false;
}

void Hex::IS_BOARD_POSSIBLE(ofstream& file, const short& state) {
	//uzyc is_game_over

	if (PAWNS_NUMBER == 0) {
		if (file.is_open()) {
			file << "YES" << endl << endl;
		}
		//cout << "YES" << endl;
		return;
	}
	if (IS_GAME_OVER(state, file)) {
		//if (!beforeDFS(board, state)) {
		//	if (file.is_open()) {
		//		file << "YES" << endl << endl;
		//	}
		//	//cout << "YES" << endl;
		//	return;
		//}

		switch (whoWon) {
		case 1: { // RED
			if (BLUE_PAWNS + 1 == RED_PAWNS) {
				vector<bool> afterDFS;
				for (int i = 0; i < lineCounter / 2; ++i) {
					for (int j = 0; j < lineCounter / 2; ++j) {
						if (board[i][j].symbol == 'r') {
							board[i][j].symbol = ' ';
							short st = 2;
							afterDFS.push_back(beforeDFS(board, st));
							board[i][j].symbol = 'r';
						}
					}
				}
				for (auto b : afterDFS) {
					if (b == false) {
						if (file.is_open()) {
							file << "YES" << endl << endl;
						}
						//cout << "YES" << endl << endl;
						return;
					}
				}
				if (file.is_open()) {
					file << "NO" << endl << endl;
					return;
				}
				//cout << "NO" << endl << endl;
			}
			break;
		}
		case 2: {// BLUE
			if (BLUE_PAWNS + 1 == RED_PAWNS) {
				if (file.is_open()) {
					file << "NO" << endl << endl;
				}
				//cout << "NO" << endl;
				return;
			}
			else if (BLUE_PAWNS == RED_PAWNS) {
				vector<bool> afterDFS;
				for (int i = 0; i < lineCounter / 2; ++i) {
					for (int j = 0; j < lineCounter / 2; ++j) {
						if (board[i][j].symbol == 'b') {
							board[i][j].symbol = ' ';
							short st = 1;
							afterDFS.push_back(beforeDFS(board, st));
							board[i][j].symbol = 'b';
						}
					}
				}
				for (auto b : afterDFS) {
					if (b == false) {
						if (file.is_open()) {
							file << "YES" << endl << endl;
						}
						//cout << "YES" << endl << endl;
						return;
					}
				}
				if (file.is_open()) {
					file << "NO" << endl << endl;
					return;
				}
				//cout << "NO" << endl << endl;
			break;
		}
		}
	}
	}
	else {
		if (whoWon == -1) {
			return;
		}
		if (file.is_open()) {
			file << "YES" << endl << endl;
		}
		//cout << "YES" << endl << endl;
		return;
	}
}