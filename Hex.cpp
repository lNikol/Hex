#include "Hex.h"
#include <iostream>
#include <fstream>
using namespace std;

Hex::Hex() {
}

void Hex::setPlayerSymbol(char s, const short& line, const short& cell) {
	
}

bool Hex::get_IS_BOARD_CORRECT(ofstream& file) {
	size = lineCounter / 2;
	empty_places = (size * size) - PAWNS_NUMBER;
	if (BLUE_PAWNS == RED_PAWNS - 1 || BLUE_PAWNS == RED_PAWNS) {
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
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			board[i][j].visited = false;
			board[i][j].toBeVisited = false; // zastanowic sie nad tym czy warto zostawic
		}
	}
}

vector<Cell*> Hex::getNeighbors(const Cell* cell) { 
	vector<Cell*> neighbors;

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
	if (state != 1) {
		for (auto c : board[0]) {
			if (c.symbol == 'r') {
				if (DFS(&c, true)) {
					whoWon = 1;
					resetVisited();
					return true;
				}
			}
		}
	}
	if (state != 2) {
		for (int i = 0; i < size; i++) {
			if (board[i][0].symbol == 'b') {
				if (DFS(&board[i][0], false)) {
					whoWon = 2;
					resetVisited();
					return true;
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
			else if (c->pos == size - 1 && !isRed) {
				// niebieski gracz
				return true;
			}
			if (DFS(c, isRed)) {
				return true;
			}
		}
	}
	if (size - 1 == 0) {
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

bool Hex::IS_BOARD_POSSIBLE(ofstream& file, const short& state) {
	if (IS_GAME_OVER(state, file)) {
		switch (whoWon) {
		case 1: { // RED
			if (BLUE_PAWNS == RED_PAWNS - 1) {
				vector<bool> afterDFS;
				for (int i = 0; i < size; ++i) {
					for (int j = 0; j < size; ++j) {
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
						return true;
					}
				}
				return false;
			}
			else if (BLUE_PAWNS == RED_PAWNS) {
				return false;
			}
			break;
		}
		case 2: {// BLUE
			if (BLUE_PAWNS == RED_PAWNS - 1) {
				return false;
			}
			else if (BLUE_PAWNS == RED_PAWNS) {
				vector<bool> afterDFS;
				for (int i = 0; i < size; ++i) {
					for (int j = 0; j < size; ++j) {
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
						return true;
					}
				}
				return false;
			}
			break;

		}
		}
		if (file.is_open()) {
			file << "poza if w is_board_possible\n";
		}
		return false;
	}
	else {
		if (whoWon == -1) {
			return false;
		}
		return true;
	}
}

bool Hex::CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT(ofstream& file, const short& state) {
	if (IS_BOARD_POSSIBLE(file, state)) {
		if (whoWon == 1 || whoWon == 2) {
			return false;
		}
		else {
			countNaiveTurns(1, true);
			if (turns <= empty_places) {
				// zrobic dla kazdego przypadku kontainer, ktory bedzie 
				// zbieral wyniki dfsa (line_length piona) dla gracza, ktory chce wygrac
				// jesli gracz nie wygrywa, to sprawdzic caly kontainer na maksymalna liczbe line_length
				// i dodac do tego miejsca pion 
				// jesli kilka maksymalnych line_length, to wybrac pierwszy
			}
			else {
				return false;
			}
		}
	}
	else {
		return false;
	}
}

void Hex::countNaiveTurns(const short& N, bool isRed) {
	short turns = 0;
	if (N == 1) {
		if (isRed) {
			if (RED_PAWNS == BLUE_PAWNS) {
				redTurns = 1;
				turns = 1;
			}
			else if (BLUE_PAWNS - 1 == RED_PAWNS) {
				redTurns = 1;
				blueTurns = 1;
				turns = 2;
			}
		}
		else {
			if (RED_PAWNS - 1 == BLUE_PAWNS) {
				blueTurns = 1;
				turns = 1;
			}
			else if (BLUE_PAWNS == RED_PAWNS) {
				redTurns = 1;
				blueTurns = 1;
				turns = 2;
			}
		}
	}
	else if (N == 2) {
		if (isRed) {
			if (RED_PAWNS == BLUE_PAWNS) {
				redTurns = 2;
				blueTurns = 1;
				turns = 3;
			}
			else if (BLUE_PAWNS - 1 == RED_PAWNS) {
				redTurns = 2;
				blueTurns = 2;
				turns = 4;
			}
		}
		else {
			if (RED_PAWNS == BLUE_PAWNS) {
				redTurns = 2;
				blueTurns = 2;
				turns = 4;
			}
			else if (BLUE_PAWNS - 1 == RED_PAWNS) {
				redTurns = 1;
				blueTurns = 2;
				turns = 3;
			}
		}
	}
}