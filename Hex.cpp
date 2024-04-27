#include "Hex.h"
#include <iostream>
#include <fstream>
using namespace std;

Hex::Hex() {
}

void Hex::setPlayerSymbol(char s, const short& line, const short& cell) {

}


void Hex::updateStats(const char& player, const short& n) {
	if (player == 'r') {
		if (RED_PAWNS + n >= 0) {
			testNumber = RED_PAWNS + n;
		}
		else {
			testNumber = RED_PAWNS;
		}
	}
	else if (player == 'b' && BLUE_PAWNS + n >= 0) {
		testNumber = BLUE_PAWNS + n;
		if (BLUE_PAWNS + n >= 0) {
			testNumber = BLUE_PAWNS + n;
		}
		else {
			testNumber = BLUE_PAWNS;
		}
	}
}

bool Hex::get_IS_BOARD_CORRECT() {
	if (BLUE_PAWNS == RED_PAWNS - 1 || BLUE_PAWNS == RED_PAWNS) {
		IS_BOARD_CORRECT = true;
	}
	else {
		IS_BOARD_CORRECT = false;
	}
	return IS_BOARD_CORRECT;
}

void Hex::resetVisited(const char& player) {
	short temp = 0;
	for (short i = 0; i < size; ++i) {
		for (short j = 0; j < size; ++j) {
			if (board[i][j].symbol != player) continue;
			board[i][j].visited = false;
			++temp;
			if (temp >= testNumber) return;
		}
	}
}

vector<Cell*> Hex::getNeighbors(const Cell* cell) {
	vector<Cell*> neighbors;

	short dLines[] = { -1, 0, 1, 1, 0, -1 };
	short dPoses[] = { -1, -1, 0, 1, 1, 0 };

	for (short i = 0; i < 6; ++i) {
		short newRow = cell->line + dLines[i];
		short newCol = cell->pos + dPoses[i];
		if (newRow >= 0 && newRow < size && newCol >= 0 && newCol < size) {
			if (board[newRow][newCol].symbol == cell->symbol) neighbors.push_back(&board[newRow][newCol]);
		}
	}

	return neighbors;
}

bool Hex::beforeDFS(const short& state) {
	// dla czerwonego gracza z gornego do dolnego
	// pseudo win:
	// 0 - nic
	// 1 - red win (w rzecywistosci wygral niebieski gracz)
	// 2 - blue win (w rzecywistosci wygral czerwony gracz)

	if (state != 1) {
		if (state == 0) {
			testNumber = RED_PAWNS;
		}
		for (short i = 0; i < size; ++i) {
			if (board[0][i].symbol == 'r') {
				if (DFS(&board[0][i], true)) {
					whoWon = 1;
					resetVisited('r');
					return true;
				}
				resetVisited('r');
			}
		}
	}

	if (state != 2) {
		if (state == 0) {
			testNumber = BLUE_PAWNS;
		}
		for (short i = 0; i < size; ++i) {
			if (board[i][0].symbol == 'b') {
				if (DFS(&board[i][0], false)) {
					whoWon = 2;
					resetVisited('b');
					return true;
				}
				resetVisited('b');
			}
		}
	}
	whoWon = 0;
	return false;
}

bool Hex::DFS(Cell* cell, bool isRed) {
	cell->visited = true; // usunac
	vector<Cell*> neighbors = getNeighbors(cell);
	for (auto* c : neighbors) {
		if (c->visited == false) {
			if (c->line == size - 1 && isRed) {
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

bool Hex::IS_GAME_OVER(const short& state) {
	if (get_IS_BOARD_CORRECT()) {
		return beforeDFS(state);
	}
	return false;
}

void Hex::checkPositions(vector<bool>& afterDFS, const short& st, const char& player, const char& symbol) {
	// player może być r, b lub ' '
	// ta funkcja jest używana w naive i is_board_possible
	if (player == ' ') {
		for (short i = 0; i < emptyPlaces.size(); ++i) {
			short y = emptyPlaces[i].first;
			short x = emptyPlaces[i].second;
			board[y][x].symbol = symbol;
			updateStats(symbol, 1);
			afterDFS.push_back(beforeDFS(st));
			updateStats(symbol, -1);
			board[y][x].symbol = player;
		}
		return;
	}

	updateStats(player, 1);
	for (short i = 0; i < size; ++i) {
		for (short j = 0; j < size; ++j) {
			if (board[i][j].symbol == player) {
				board[i][j].symbol = symbol;
				afterDFS.push_back(beforeDFS(st));
				board[i][j].symbol = player;
			}
		}
	}
	updateStats(player, -1);
}

bool Hex::IS_BOARD_POSSIBLE(const short& state) {
	if (IS_GAME_OVER(state)) {
		switch (whoWon) {
		case 1: { // RED
			if (BLUE_PAWNS == RED_PAWNS - 1) {
				vector<bool> afterDFS;
				checkPositions(afterDFS, 2, 'r', ' ');
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
				checkPositions(afterDFS, 1, 'b', ' ');
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
		return false;
	}
	else {
		if (whoWon == -1) {
			return false;
		}
		return true;
	}
}

void Hex::countNaiveTurns(const short& N, bool isRed) {
	if (N == 1) {
		if (isRed) {
			if (RED_PAWNS == BLUE_PAWNS) {
				redTurns = 1;
				turns = 1;
			}
			else if (BLUE_PAWNS == RED_PAWNS - 1) {
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
			else if (BLUE_PAWNS == RED_PAWNS - 1) {
				// tura niebieskiego
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
			else if (BLUE_PAWNS == RED_PAWNS - 1) {
				redTurns = 1;
				blueTurns = 2;
				turns = 3;
			}
		}
	}
}

bool Hex::CAN_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT(const short& state, const char& player, bool isRed) {
	if (IS_BOARD_POSSIBLE(state)) {
		if (whoWon == 1 || whoWon == 2) {
			return false;
		}
		else {
			countNaiveTurns(1, isRed);
			if (turns <= emptyPlaces.size()) {
				vector<bool> afterDFS;
				short st = player == 'r' ? 2 : 1;
				checkPositions(afterDFS, st, ' ', player);
				for (auto b : afterDFS) {
					if (b) {
						return true;
					}
				}
				return false;
				// mini-max
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

bool Hex::CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT(const short& state) {
	return CAN_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT(state, 'r', true);
}

bool Hex::CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT(const short& state) {
	return CAN_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT(state, 'b', false);
}

bool Hex::CAN_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT(const short& state, const char& player, bool isRed) {
	if (IS_BOARD_POSSIBLE(state)) {
		if (whoWon == 1 || whoWon == 2) {
			return false;
		}
		else {
			countNaiveTurns(2, isRed);
			if (turns <= emptyPlaces.size()) {
				vector<bool> afterDFS;
				for (short i = 0; i < emptyPlaces.size(); ++i) {
					short y1 = 0, x1 = 0, y2 = 0, x2 = 0;
					y1 = emptyPlaces[i].first;
					x1 = emptyPlaces[i].second;
					for (short j = i + 1; j < emptyPlaces.size(); ++j) {
						y2 = emptyPlaces[j].first;
						x2 = emptyPlaces[j].second;
						board[y1][x1].symbol = player;
						board[y2][x2].symbol = player;
						short st = player == 'r' ? 2 : 1;
						updateStats(player, 2);
						if (beforeDFS(st)) {
							updateStats(player, -1);

							board[y1][x1].symbol = ' ';
							bool first = beforeDFS(st);
							board[y1][x1].symbol = player;
							bool second;

							if (first) {
								board[y2][x2].symbol = ' ';
								second = beforeDFS(st);
								board[y2][x2].symbol = player;
							}
							else {
								second = true;
							}

							if (first && second) {
								afterDFS.push_back(false);
							}
							else {
								afterDFS.push_back(true);
							}
							updateStats(player, -1);
						}
						else {
							updateStats(player, -2);
						}
						board[y1][x1].symbol = ' ';
						board[y2][x2].symbol = ' ';
					}

				}
				for (auto b : afterDFS) {
					if (b) {
						return true;
					}
				}
				return false;
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

bool Hex::CAN_RED_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT(const short& state) {
	return CAN_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT(state, 'r', true);
}

bool Hex::CAN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT(const short& state) {
	return CAN_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT(state, 'b', false);
}
