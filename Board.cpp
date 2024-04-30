#include "Board.h"
using namespace std;

//void Board::createCell(const short& y, const char& s) {
//	if (s == ' ') {
//		board[y][indexes[y]++] = new Cell(s, y, indexes[y]);
//		emptyPlaces[emptyCounter++] = board[y][indexes[y] - 1];
//	}
//	else {
//		board[y][indexes[y]++] = new Cell(s, y, indexes[y]);
//	}
//}

bool Board::get_IS_BOARD_CORRECT() {
	if (BLUE_PAWNS == RED_PAWNS - 1 || BLUE_PAWNS == RED_PAWNS) {
		IS_BOARD_CORRECT = true;
	}
	else {
		IS_BOARD_CORRECT = false;
	}
	return IS_BOARD_CORRECT;
}

void Board::resetVisited() {
	for (short i = 0; i < size; ++i) {
		for (short j = 0; j < size; ++j) {
			board[i][j]->visited = false;
		}
	}
}

void Board::getNeighbors(Pawn** neighbors, const Pawn* pawn, short& count) {
	count = 0;
	short dLines[] = { -1, 0, 1, 1, 0, -1 };
	short dPoses[] = { -1, -1, 0, 1, 1, 0 };

	for (short i = 0; i < 6; ++i) {
		short newRow = pawn->y + dLines[i];
		short newCol = pawn->x + dPoses[i];
		if (newRow >= 0 && newRow < size && newCol >= 0 && newCol < size) {
			if (board[newRow][newCol]->symbol == pawn->symbol) {
				neighbors[count++] = board[newRow][newCol];
			}
		}
	}
}

Player Board::DFS(Pawn* pawn, bool isRed) {
	if (size - 1 == 0) {
		if (isRed) {
			return RED;
		}
		else {
			return NONE;
		}
	}
	pawn->visited = true;
	short count = 0;
	Pawn* neighbors[6] = { nullptr };
	getNeighbors(neighbors, pawn, count);

	for (short i = 0; i < count; ++i) {
		if (neighbors == nullptr || neighbors[i] == nullptr) {
			for (short l = 0; l < count; ++l) {
				neighbors[l] = nullptr;
			}
			break;
		}
		if (neighbors != nullptr && neighbors[i]->visited == false) {
			if (neighbors[i]->y == size - 1 && isRed) {
				for (short l = 0; l < count; ++l) {
					neighbors[l] = nullptr;
				}
				// ten warunek dla gracza czerwonego od lewej granicy do prawej
				// czerwony gracz
				return RED;
			}
			else if (neighbors[i]->x == size - 1 && !isRed) {
				// niebieski gracz
				for (short l = 0; l < count; ++l) {
					neighbors[l] = nullptr;
				}
				return BLUE;
			}
			Player p = DFS(neighbors[i], isRed);
			if (p != NONE) {
				return p;
			}
		}
	}
	return NONE;
}

Player Board::getWinner(const short& state) {
	// state odpowiada za blokowanie sprawdzenie dfs dla graczy
	// 1 blokuje sprawdzenie czerwonego
	// 2 blokuje sprawdzenie niebieskiego
	// 0 sprawdza piony dwoch graczy
	if (state != 1) {
		for (short i = 0; i < size; ++i) {
			if (board[0][i]->symbol == 'r') {
				if (DFS(board[0][i], true) == RED) {
					resetVisited();
					return RED;
				}
				resetVisited();
			}
		}
	}
	if (state != 2) {
		for (short i = 0; i < size; ++i) {
			if (board[i][0]->symbol == 'b') {
				if (DFS(board[i][0], false) == BLUE) {
					resetVisited();
					return BLUE;
				}
				resetVisited();
			}
		}
	}
	return NONE;
}

Player Board::IS_GAME_OVER(const short& state) {
	if (get_IS_BOARD_CORRECT()) {
		return getWinner(state);
	}
	return INCORRECT;
}

void Board::checkPositions(Player toFind, Player afterDFS[], bool isPerfect, const short& st, const char& player, const char& symbol, Pawn** possiblePerfectMoves = nullptr) {
	// player może być r, b lub ' '
	// ta funkcja jest używana w naive i is_board_possible
	short k = 0;
	if (player == ' ') {
		for (short i = 0; i < emptyCounter; ++i) {
			if (emptyPlaces[i]->symbol != ' ') {
				*(afterDFS + i) = EMPTY;
				continue;
			}
			emptyPlaces[i]->symbol = symbol;
			Player p = getWinner(st);
			*(afterDFS + i) = p;
			emptyPlaces[i]->symbol = player;
			/*if (isPerfect && b) {
				if (possiblePerfectMoves != nullptr) {
					*(possiblePerfectMoves + k++) = emptyPlaces[i];
					if (k == 2) {
						return;
					}
				}
			}*/
			if (p == toFind) {
				return;
			}
		}
		return;
	}

	short count = 0;
	for (short i = 0; i < size; ++i) {
		for (short j = 0; j < size; ++j) {
			if (board[i][j]->symbol == player) {
				board[i][j]->symbol = symbol;
				*(afterDFS + count++) = getWinner(st);
				board[i][j]->symbol = player;
			}
		}
	}
}

bool Board::IS_BOARD_POSSIBLE(const short& state) {
	switch (IS_GAME_OVER(state)) {
	case RED: {
		if (BLUE_PAWNS == RED_PAWNS - 1) {
			Player* afterDFS = new Player[RED_PAWNS]{ EMPTY };
			checkPositions(BLUE, afterDFS, false, 2, 'r', ' ');
			for (short k = 0; k < RED_PAWNS; ++k) {
				if (*(afterDFS + k) != RED) {
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
	case BLUE: {
		if (BLUE_PAWNS == RED_PAWNS - 1) {
			return false;
		}
		else if (BLUE_PAWNS == RED_PAWNS) {
			Player* afterDFS = new Player[BLUE_PAWNS]{ EMPTY };
			checkPositions(RED, afterDFS, false, 1, 'b', ' ');
			for (short k = 0; k < BLUE_PAWNS; ++k) {
				if (afterDFS[k] != BLUE) {
					delete[] afterDFS;
					return true;
				}
			}
			delete[] afterDFS;
			return false;
		}
		break;
	}
	case NONE: {
		return true;
	}
	case INCORRECT: {
		return false;
	}
	}
	return false;
}

void Board::countPlayersTurns(const short& N, bool isRed) {
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

Board::~Board() {
	if (board[0][0] != nullptr) {
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
	
}