#include "Board.h"
using namespace std;

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
			break;
		}
		if (neighbors != nullptr && neighbors[i]->visited == false) {
			if (neighbors[i]->y == size - 1 && isRed) {
				// ten warunek dla gracza czerwonego od lewej granicy do prawej
				// czerwony gracz
				return RED;
			}
			else if (neighbors[i]->x == size - 1 && !isRed) {
				// ten warunek dla gracza niebieskiego od gornej granicy do dolnej
				// niebieski gracz
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
			if (board[0][i]->symbol == RED) {
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
			if (board[i][0]->symbol == BLUE) {
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

void Board::checkPositions(Player toFind, Player afterDFS[], bool isPerfect, const short& st, const Player& player, const Player& symbol, Pawn** possiblePerfectMoves = nullptr) {
	// ta funkcja jest używana w naive i is_board_possible
	if (player == EMPTY) {
		short k = 0;
		for (short i = 0; i < emptyCounter; ++i) {
			if (emptyPlaces[i]->symbol != EMPTY) {
				*(afterDFS + i) = INCORRECT;
				continue;
			}
			emptyPlaces[i]->symbol = symbol;
			Player p = getWinner(st);
			*(afterDFS + i) = p;
			emptyPlaces[i]->symbol = player;
			if (isPerfect && p == toFind) {
				// jesli wynik getWinner jest player, ktorego szukalem,
				// to odpowiednio dodaje te gre do mozliwych gier wygranych
				// jesli licba mozliwych wygranych jest == 2
				// to w perfect gracz czy przeciwnik wygra gre
				*(possiblePerfectMoves + k++) = emptyPlaces[i];
				if (k == 2) {
					return;
				}
			}
			else if (p == toFind) {
				return;
			}
		}
		return;
	}

	// sprawdzenie dla gracza (BLUE lub RED) czy zawsze wygrywa
	// tutaj zamieniam na spacje, czyli 'usuwam' tymczasowo pion gracza
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
			checkPositions(BLUE, afterDFS, false, 2, RED, EMPTY);
			for (short k = 0; k < RED_PAWNS; ++k) {
				// jesli chociazby w jednej grze gracz nie wygral,
				// to oznacza, ze board possible
				if (*(afterDFS + k) != RED) {
					delete[] afterDFS;
					return true;
				}
			}
			// w przeciwnym wypadku gracz zawsze wygrywał
			// wiec nie jest possible
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
			checkPositions(RED, afterDFS, false, 1, BLUE, EMPTY);
			for (short k = 0; k < BLUE_PAWNS; ++k) {
				// jesli chociazby w jednej grze gracz nie wygral,
				// to oznacza, ze board possible
				if (afterDFS[k] != BLUE) {
					delete[] afterDFS;
					return true;
				}
			}
			// w przeciwnym wypadku gracz zawsze wygrywał
			// wiec nie jest possible
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

void Board::updateStats(const Player& pl, const short& n) {
	switch (pl) {
	case RED: {
		RED_PAWNS += n;
		break;
	}
	case BLUE: {
		BLUE_PAWNS += n;
		break;
	}
	}
	PAWNS_NUMBER += n;
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