#include "Hex2.h"
#include <iostream>
using namespace std;


bool Hex2::CAN_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT(const short& state, const char& player, bool isRed, short emptyCounter) {
	if (board.get_IS_BOARD_CORRECT()) {
		switch (board.getWinner(state)) {
		case BLUE:
		case RED:
			return false;
		}
		board.countPlayersTurns(1, isRed);
		if ((player == 'b' && (board.BLUE_PAWNS + board.blueTurns) < board.size) || (player == 'r' && (board.RED_PAWNS + board.redTurns) < board.size)) {
			return false;
		}
		if (board.turns <= emptyCounter) {
			Player* afterDFS = new Player[board.emptyCounter]{ EMPTY };
			short st = player == 'r' ? 2 : 1;
			board.checkPositions(player == 'r' ? RED : BLUE, afterDFS, false, st, ' ', player, nullptr);
			for (short k = 0; k < board.emptyCounter; ++k) {
				if (afterDFS[k] == (player == 'r' ? RED : BLUE)) {
					delete[] afterDFS;
					return true;
				}
				else if (afterDFS[k] == EMPTY) {
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
	else {
		return false;
	}
}

bool Hex2::CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT(const short& state, short emptyCounter) {
	return CAN_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT(state, 'r', true, emptyCounter);
}

bool Hex2::CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT(const short& state, short emptyCounter) {
	return CAN_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT(state, 'b', false, emptyCounter);
}

bool Hex2::CAN_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT(const short& state, const char& player, bool isRed, short emptyCounter) {
	if (board.get_IS_BOARD_CORRECT()) {
		switch (board.getWinner(state)) {
		case BLUE:
		case RED:
			return false;
		}

		board.countPlayersTurns(2, isRed);
		if ((player == 'b' && (board.BLUE_PAWNS + board.blueTurns) < board.size) || (player == 'r' && (board.RED_PAWNS + board.redTurns) < board.size)) {
			return false;
		}
		if (board.turns <= emptyCounter) {
			Player* afterDFS = new Player[emptyCounter * emptyCounter]{ EMPTY };
			short k = 0;
			short st = player == 'r' ? 2 : 1;
			Player pl = (player == 'r' ? RED : BLUE);
			for (short i = 0; i < emptyCounter; ++i) {
				for (short j = i + 1; j < emptyCounter; ++j) {
					board.emptyPlaces[i]->symbol = player;
					board.emptyPlaces[j]->symbol = player;
					if (board.getWinner(st) == pl) {
						board.emptyPlaces[i]->symbol = ' ';
						Player first = board.getWinner(st);
						board.emptyPlaces[i]->symbol = player;
						Player second;

						if (first == pl) {
							board.emptyPlaces[j]->symbol = ' ';
							second = board.getWinner(st);
							board.emptyPlaces[j]->symbol = player;
						}
						else {
							second = pl;
						}

						if (first == pl && second == pl) {
							afterDFS[k++] = INCORRECT;
						}
						else {
							board.emptyPlaces[i]->symbol = ' ';
							board.emptyPlaces[j]->symbol = ' ';
							delete[] afterDFS;
							return true;
						}
					}
					board.emptyPlaces[i]->symbol = ' ';
					board.emptyPlaces[j]->symbol = ' ';
				}
			}
			delete[] afterDFS;
			return false;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

bool Hex2::CAN_RED_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT(const short& state, short emptyCounter) {
	return CAN_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT(state, 'r', true, emptyCounter);
}

bool Hex2::CAN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT(const short& state, short emptyCounter) {
	return CAN_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT(state, 'b', false, emptyCounter);
}
