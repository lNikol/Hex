#include "Hex.h"
#include <iostream>
#include <fstream>
using namespace std;

Hex::Hex() {

}


Hex::~Hex() {
	for (short i = 0; i < ARR_SIZE; ++i) {
		for (short j = 0; j < ARR_SIZE; ++j) {
			delete board[i][j];
		}
	}
	for (short i = 0; i < emptyCounter; ++i) {
		emptyPlaces[i] = nullptr;
		delete emptyPlaces[i];
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

void Hex::resetVisited() {
	for (short i = 0; i < size; ++i) {
		for (short j = 0; j < size; ++j) {
			board[i][j]->visited = false;
		}
	}
}

void Hex::getNeighbors(Cell** neighbors, const Cell* cell, short& count) {
	count = 0;
	short dLines[] = { -1, 0, 1, 1, 0, -1 };
	short dPoses[] = { -1, -1, 0, 1, 1, 0 };

	for (short i = 0; i < 6; ++i) {
		short newRow = cell->line + dLines[i];
		short newCol = cell->pos + dPoses[i];
		if (newRow >= 0 && newRow < size && newCol >= 0 && newCol < size) {
			if (board[newRow][newCol]->symbol == cell->symbol) {
				neighbors[count++] = board[newRow][newCol];
			}
		}
	}
}

bool Hex::beforeDFS(const short& state) {
	// state odpowiada za blokowanie sprawdzenie dfs dla graczy
	// 1 blokuje sprawdzenie czerwonego
	// 2 blokuje sprawdzenie niebieskiego
	// 0 sprawdza piony dwoch graczy

	if (state != 1) {
		for (short i = 0; i < size; ++i) {
			if (board[0][i]->symbol == 'r') {
				if (DFS(board[0][i], true)) {
					whoWon = 1;
					resetVisited();
					return true;
				}
				resetVisited();
			}
		}
	}

	if (state != 2) {
		for (short i = 0; i < size; ++i) {
			if (board[i][0]->symbol == 'b') {
				if (DFS(board[i][0], false)) {
					whoWon = 2;
					resetVisited();
					return true;
				}
				resetVisited();
			}
		}
	}
	whoWon = 0;
	return false;
}

bool Hex::DFS(Cell* cell, bool isRed) {
	if (size - 1 == 0) {
		if (isRed) {
			return true;
		}
		else {
			return false;
		}
	}
	cell->visited = true;
	short count = 0;
	Cell* neighbors[6] = { nullptr };
	getNeighbors(neighbors, cell, count);

	for (short i = 0; i < count; ++i) {
		if (neighbors == nullptr || neighbors[i] == nullptr) {
			for (short l = 0; l < count; ++l) {
				neighbors[l] = nullptr;
			}
			break;
		}
		if (neighbors != nullptr && neighbors[i]->visited == false) {
			if (neighbors[i]->line == size - 1 && isRed) {
				// ten warunek dla gracza czerwonego od lewej granicy do prawej
				// czerwony gracz
				return true;
			}
			else if (neighbors[i]->pos == size - 1 && !isRed) {
				// niebieski gracz
				return true;
			}
			if (DFS(neighbors[i], isRed)) {
				return true;
			}
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

void Hex::checkPositions(short afterDFS[], bool isPerfect, const short& st, const char& player, const char& symbol, Cell** perfectPlayerTurns = nullptr) {
	// player może być r, b lub ' '
	// ta funkcja jest używana w naive i is_board_possible
	short k = 0;
	if (player == ' ') {
		for (short i = 0; i < emptyCounter2; ++i) {
			if (emptyPlaces[i]->symbol != ' ') {
				*(afterDFS + i) = 3;
				continue;
			}
			emptyPlaces[i]->symbol = symbol;
			bool b = beforeDFS(st);
			*(afterDFS + i) = b;
			emptyPlaces[i]->symbol = player;
			if (isPerfect && b) {
				if (perfectPlayerTurns != nullptr) {
					*(perfectPlayerTurns + k++) = emptyPlaces[i];
					if (k == 2) {
						return;
					}
				}
			}
		}
		return;
	}

	short count = 0;
	for (short i = 0; i < size; ++i) {
		for (short j = 0; j < size; ++j) {
			if (board[i][j]->symbol == player) {
				board[i][j]->symbol = symbol;
				*(afterDFS + count++) = beforeDFS(st);
				board[i][j]->symbol = player;
			}
		}
	}
}

bool Hex::IS_BOARD_POSSIBLE(const short& state) {
	if (IS_GAME_OVER(state)) {
		switch (whoWon) {
		case 1: { // RED
			if (BLUE_PAWNS == RED_PAWNS - 1) {
				short* afterDFS = new short[RED_PAWNS] {2};
				checkPositions(afterDFS, false, 2, 'r', ' ');
				for (short k = 0; k < RED_PAWNS; ++k) {
					if (*(afterDFS+k) == 0) {
						whoWon = 1;
						delete[] afterDFS;
						return true;
					}
				}
				delete[] afterDFS;
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
				short* afterDFS = new short[BLUE_PAWNS] {2};
				checkPositions(afterDFS, false, 1, 'b', ' ');
				for (short k = 0; k < BLUE_PAWNS; ++k) {
					if (afterDFS[k] == 0) {
						whoWon = 2;
						delete[] afterDFS;
						return true;
					}
				}
				delete[] afterDFS;
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

void Hex::countPlayersTurns(const short& N, bool isRed) {
	turns = 0;
	redTurns = 0;
	blueTurns = 0;

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
				// tura czerwonego
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
				// tura czerwonego
				redTurns = 2;
				blueTurns = 2;
				turns = 4;
			}
			else if (BLUE_PAWNS == RED_PAWNS - 1) {
				// tura niebieskiego
				redTurns = 1;
				blueTurns = 2;
				turns = 3;
			}
		}
	}
}

void Hex::updateStats(const char& s, const short& n) {
	switch (s) {
	case 'r': {
		RED_PAWNS += n;
		break;
	}
	case 'b': {
		BLUE_PAWNS += n;
		break;
	}
	}
	PAWNS_NUMBER += n;
}

bool Hex::CAN_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT(const short& state, const char& player, bool isRed) {
	if (get_IS_BOARD_CORRECT()) {
		beforeDFS(state);
		if (whoWon == 1 || whoWon == 2) {
			return false;
		}
		else {
			countPlayersTurns(1, isRed);
			if ((player == 'b' && (BLUE_PAWNS + blueTurns) < size) || (player == 'r' && (RED_PAWNS + redTurns) < size)) {
				return false;
			}
			if (turns <= emptyCounter) {	
				short* afterDFS = new short[emptyCounter2] {2};
				short st = player == 'r' ? 2 : 1;
				checkPositions(afterDFS, false, st, ' ', player);
				for (short k = 0; k < emptyCounter2; ++k) {
					if (afterDFS[k] == 1) {
						delete[] afterDFS;
						return true;
					}
					else if (afterDFS[k] == 2) {
						delete[] afterDFS;
						return false;
					}
				}
				delete[] afterDFS;
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

bool Hex::CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT(const short& state) {
	return CAN_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT(state, 'r', true);
}

bool Hex::CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT(const short& state) {
	return CAN_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT(state, 'b', false);
}

bool Hex::CAN_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT(const short& state, const char& player, bool isRed) {
	if (get_IS_BOARD_CORRECT()) {
		beforeDFS(state); 
		if (whoWon == 1 || whoWon == 2) {
			return false;
		}
		else {
			countPlayersTurns(2, isRed);
			if ((player == 'b' && (BLUE_PAWNS + blueTurns) < size) || (player == 'r' && (RED_PAWNS + redTurns) < size)) {
				return false;
			}
			if (turns <= emptyCounter) {
				short* afterDFS = new short[emptyCounter * emptyCounter] {2};
				short k = 0;
				for (short i = 0; i < emptyCounter; ++i) {
					for (short j = i + 1; j < emptyCounter; ++j) {
						emptyPlaces[i]->symbol = player;
						emptyPlaces[j]->symbol = player;
						short st = player == 'r' ? 2 : 1;
						if (beforeDFS(st)) {
							emptyPlaces[i]->symbol = ' ';
							bool first = beforeDFS(st);
							emptyPlaces[i]->symbol = player;
							bool second;

							if (first) {
								emptyPlaces[j]->symbol = ' ';
								second = beforeDFS(st);
								emptyPlaces[j]->symbol = player;
							}
							else {
								second = true;
							}

							if (first && second) {
								afterDFS[k++] = 0;
							}
							else {
								afterDFS[k++] = 1;
							}
						}
						emptyPlaces[i]->symbol = ' ';
						emptyPlaces[j]->symbol = ' ';
					}
				}
				for (short l = 0; l < k; ++l) {
					if (afterDFS[l] == 1) {
						delete[] afterDFS;
						return true;
					}
				}
				delete[] afterDFS;
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

bool Hex::CAN_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT(const short& state, const char& player, bool isRed, const short& emptyCounter_) {

	/* Logika:
	* w zależności od ilości tur:
	* jeśli turns == 1, to sprawdzić czyja jest teraz tura
	* jeśli czerwonego, to naive dla czerwonego
	* jeśli niebieski, to naive dla niebieskiego
	*
	* zrobić coś podobnego dla dwóch tur, gdzie w zależności od
	* gracza wywołuję odpowiednie funkcje
	*
	*
	* w zależności od tego, kto teraz ma więcej tur, tego i tura
	* blueTurns>redTurns -> blue ma turę, jęsli blueTruns==redTurns to w zależności od isRed

	*/

	if (get_IS_BOARD_CORRECT()) {
		countPlayersTurns(1, isRed);
		if ((player == 'b' && (BLUE_PAWNS + blueTurns) < size) || (player == 'r' && (RED_PAWNS + redTurns) < size)) {
			return false;
		}
		if (turns <= emptyCounter_) {
			if (turns == 1) {
				if (PAWNS_NUMBER == 0 && size > 1) {
					return false;
				}
				if (redTurns > blueTurns) {
					return CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT(state);
				}
				else if (redTurns < blueTurns) {
					return CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT(state);
				}
			}
			else {
				if (PAWNS_NUMBER != 0 || size > 1) {
					beforeDFS(state);
				}
				if (whoWon == 1 || whoWon == 2) {
					return false;
				}
				else {
					short* afterDFS = new short[emptyCounter2] {2};
					short st = player == 'r' ? 2 : 1;
					Cell* perfectPlayerTurns[2] = { nullptr };
					checkPositions(afterDFS, true, st, ' ', player, perfectPlayerTurns);
					if (perfectPlayerTurns[0] != nullptr && perfectPlayerTurns[1] != nullptr) {
						delete[] afterDFS;
						return true;
					}
					else {
						delete[] afterDFS;
						return false;
					}
					delete[] afterDFS;
					return false;
				}
				return false;
			}
			return false;
		}
		return false;
	}
	else {
		return false;
	}
}


bool Hex::CAN_RED_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT(const short& state) {
	return CAN_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT(state, 'r', true, emptyCounter);
}

bool Hex::CAN_BLUE_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT(const short& state) {
	return CAN_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT(state, 'b', false, emptyCounter);
}

void Hex::CAN_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT(short afterDFS[], const short& state, const char& player) {
	short tempRed = player == 'r' ? redTurns - 1 : redTurns, tempBlue = player == 'b' ? blueTurns - 1 : blueTurns;
	--emptyCounter;
	updateStats(player, 1);
	for (short i = 0; i < emptyCounter2; ++i) {
		if (emptyPlaces[i]->symbol != ' ') {
			*(afterDFS + i) = 3;
			continue;
		}

		emptyPlaces[i]->symbol = player;
		if (tempRed > tempBlue) {
			bool b = CAN_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT(2, player, true, emptyCounter);
			*(afterDFS + i) = b;
			if (b) {
				updateStats(player, -1);
				emptyPlaces[i]->symbol = ' ';
				++emptyCounter;
				return;
			}
		}
		else if (tempRed < tempBlue) {
			bool b = CAN_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT(1, player, false, emptyCounter);
			*(afterDFS + i) = b;
			if (b) {
				updateStats(player, -1); 
				emptyPlaces[i]->symbol = ' ';
				++emptyCounter;
				return;
			}
		}
		else {
			bool b = CAN_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT(player == 'r' ? 2 : 1, player, player == 'r', emptyCounter);
			*(afterDFS + i) = b;
			if (b) {
				updateStats(player, -1); 
				emptyPlaces[i]->symbol = ' ';
				++emptyCounter;
				return;
			}
		}
		emptyPlaces[i]->symbol = ' ';
	}
	updateStats(player, -1);
	++emptyCounter;
}

bool Hex::CAN_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT_2(const short& state, const char& player, bool isRed) {
	if (get_IS_BOARD_CORRECT()) {
		beforeDFS(state);
		if (whoWon == 1 || whoWon == 2) {
			return false;
		}
		else {
			countPlayersTurns(2, isRed);
			if ((player == 'b' && (BLUE_PAWNS + blueTurns) < size) || (player == 'r' && (RED_PAWNS + redTurns) < size)) {
				return false;
			}
			if (turns <= emptyCounter) {
				if (turns == 3) {
					short* afterDFS = new short[emptyCounter2 * emptyCounter2] {2};
					CAN_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT(afterDFS, state, player);
					for (short k = 0; k < emptyCounter2 * emptyCounter2; ++k) {
						if (afterDFS[k] == 1) {
							delete[] afterDFS;
							return true;
						}
						else if (afterDFS[k] == 2) {
							delete[] afterDFS;
							return false;
						}
					}
					delete[] afterDFS;
					return false;
				}
				else if (turns == 4) {
					/*
					* Zmienic logike i nazwy zmiennych
					* Sprawdzic czy poprawnie sprawdzam stan perfect4
					*/

					--emptyCounter;
					if (isRed) {
						short* afterPerfect = new short[emptyCounter2 * emptyCounter2] {2};
						short count = 0;

						for (int i = 0; i < emptyCounter2; ++i) {
							short* afterDFS = new short[emptyCounter2] {2};
							if (emptyPlaces[i]->symbol != ' ') continue;
							emptyPlaces[i]->symbol = 'b';
							updateStats('b', 1);
							countPlayersTurns(2, isRed);
							CAN_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT(afterDFS, state, 'r');
							updateStats('b', -1);
							emptyPlaces[i]->symbol = ' ';
							bool wasTrue = false;
							for (short k = 0; k < emptyCounter2; ++k) {
								if (afterDFS[k] == 1) {
									wasTrue = true;
									delete[] afterDFS;
									break;
								}
								else if (afterDFS[k] == 2) {
									wasTrue = false;
									break;
								}
							}
							if (!wasTrue) {
								delete[] afterDFS;
								delete[] afterPerfect;
								return false;
							}

							afterPerfect[count++] = wasTrue;
						}
						for (short l = 0; l < count; ++l) {
							if (afterPerfect[l] == 0) {
								++emptyCounter;
								delete[] afterPerfect;
								return false;
							}
						}
						++emptyCounter;
						delete[] afterPerfect;
						return true;
					}
					else {
						short* afterPerfect = new short[emptyCounter2 * emptyCounter2] {2};
						short count = 0;

						for (int i = 0; i < emptyCounter2; ++i) {
							short* afterDFS = new short[emptyCounter2] {2};
							emptyPlaces[i]->symbol = 'r';
							updateStats('r', 1);
							countPlayersTurns(2, isRed);
							CAN_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT(afterDFS, state, 'b');
							updateStats('r', -1);
							emptyPlaces[i]->symbol = ' ';
							bool wasTrue = false;

							for (short k = 0; k < emptyCounter2; ++k) {
								if (afterDFS[k] == 1) {
									wasTrue = true;
									delete[] afterDFS;
									break;
								}
								else if (afterDFS[k] == 2) {
									wasTrue = false;
									break;
								}
							}
							if (!wasTrue) {
								delete[] afterDFS;
								delete[] afterPerfect;
								return false;
							}
							afterPerfect[count++] = wasTrue;
						}
						for (short l = 0; l < count; ++l) {
							if (afterPerfect[l] == 0) {
								++emptyCounter;
								delete[] afterPerfect;
								return false;
							}
						}
						++emptyCounter;
						delete[] afterPerfect;
						return true;
					}
				}
			}
			else {
				return false;
			}
		}
		return false;
	}
	else {
		return false;
	}
}

bool Hex::CAN_RED_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT(const short& state) {
	return CAN_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT_2(state, 'r', true);
}

bool Hex::CAN_BLUE_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT(const short& state) {
	return CAN_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT_2(state, 'b', false);
}