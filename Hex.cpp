#include "Hex.h"
#include <iostream>
using namespace std;

Player Hex::CAN_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT(const short& state, const Player& player, bool isRed, short emptyCounter) {
	if (board.get_IS_BOARD_CORRECT()) {
		if (board.getWinner(state) != NONE) {
			return INCORRECT;
		}
		board.countPlayersTurns(1, isRed);
		// tutaj najpierw sprawdzam czy wytarczy graczowi ruchow do zakonczenia gry
		// jesli nie, to INCORRECT (nie moze wygrac)
		if ((player == BLUE && (board.BLUE_PAWNS + board.blueTurns) < board.size) || (player == RED && (board.RED_PAWNS + board.redTurns) < board.size)) {
			return INCORRECT;
		}
		if (board.turns <= emptyCounter) {
			Player* afterDFS = new Player[board.emptyCounter]{ INCORRECT };
			board.checkPositions(player, afterDFS, false, player == RED ? 2 : 1, EMPTY, player, nullptr);
			for (short k = 0; k < board.emptyCounter; ++k) {
				// jesli chociaby w jednej grze gracz wygral, to zwracam gracza
				if (afterDFS[k] == player) {
					delete[] afterDFS;
					return player;
				}
			}
			delete[] afterDFS;
			return INCORRECT;
		}
		else {
			return INCORRECT;
		}
	}
	else {
		return INCORRECT;
	}
}

Player Hex::CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT(const short& state, short emptyCounter) {
	return CAN_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT(state, RED, true, emptyCounter);
}

Player Hex::CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT(const short& state, short emptyCounter) {
	return CAN_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT(state, BLUE, false, emptyCounter);
}

Player Hex::CAN_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT(const short& state, const Player& player, bool isRed, short emptyCounter) {
	if (board.get_IS_BOARD_CORRECT()) {
		if (board.getWinner(state) != NONE) {
			return INCORRECT;
		}

		board.countPlayersTurns(2, isRed);
		if ((player == BLUE && (board.BLUE_PAWNS + board.blueTurns) < board.size) || (player == RED && (board.RED_PAWNS + board.redTurns) < board.size)) {
			return INCORRECT;
		}
		if (board.turns <= emptyCounter) {
			Player* afterDFS = new Player[emptyCounter * emptyCounter]{ INCORRECT };
			short k = 0;
			short st = player == RED ? 2 : 1;
			for (short i = 0; i < emptyCounter; ++i) {
				for (short j = i + 1; j < emptyCounter; ++j) {
					board.emptyPlaces[i]->symbol = player;
					board.emptyPlaces[j]->symbol = player;
					if (board.getWinner(st) == player) {
						board.emptyPlaces[i]->symbol = EMPTY;
						Player first = board.getWinner(st);
						board.emptyPlaces[i]->symbol = player;
						Player second;

						if (first == player) {
							board.emptyPlaces[j]->symbol = EMPTY;
							second = board.getWinner(st);
							board.emptyPlaces[j]->symbol = player;
						}
						else {
							second = player;
						}

						if (first == player && second == player) {
							afterDFS[k++] = INCORRECT;
						}
						else {
							board.emptyPlaces[i]->symbol = EMPTY;
							board.emptyPlaces[j]->symbol = EMPTY;
							delete[] afterDFS;
							return player;
						}
					}
					board.emptyPlaces[i]->symbol = EMPTY;
					board.emptyPlaces[j]->symbol = EMPTY;
				}
			}
			delete[] afterDFS;
			return INCORRECT;
		}
		else {
			return INCORRECT;
		}
	}
	else {
		return INCORRECT;
	}
}

Player Hex::CAN_RED_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT(const short& state, short emptyCounter) {
	return CAN_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT(state, RED, true, emptyCounter);
}

Player Hex::CAN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT(const short& state, short emptyCounter) {
	return CAN_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT(state, BLUE, false, emptyCounter);
}

Player Hex::CAN_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT(const short& state, const Player& player, bool isRed, short emptyCounter) {

	/* Logika:
	* w zależności od ilości tur:
	* jeśli turns == 1, to sprawdzić czyja jest teraz tura
	* jeśli czerwonego, to naive dla czerwonego
	* jeśli niebieski, to naive dla niebieskiego
	*
	* w zależności od tego, kto teraz ma więcej tur, tego i tura
	* blueTurns>redTurns -> blue ma turę, jęsli blueTruns==redTurns to w zależności od isRed

	*/

	if (board.get_IS_BOARD_CORRECT()) {
		board.countPlayersTurns(1, isRed);
		// tutaj najpierw sprawdzam czy wytarczy graczowi ruchow do zakonczenia gry
		// jesli nie, to INCORRECT (nie moze wygrac)
		if ((player == BLUE && (board.BLUE_PAWNS + board.blueTurns) < board.size) || (player == RED && (board.RED_PAWNS + board.redTurns) < board.size)) {
			return INCORRECT;
		}
		if (board.turns <= emptyCounter) {
			if (board.turns == 1) {
				if (board.PAWNS_NUMBER == 0 && board.size > 1) {
					return INCORRECT;
				}
				else if (board.redTurns > board.blueTurns) {
					return CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT(state, emptyCounter);
				}
				else if (board.redTurns < board.blueTurns) {
					return CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT(state, emptyCounter);
				}
			}
			else {
				Player pl = NONE;
				if (board.PAWNS_NUMBER != 0 || board.size > 1) {
					pl = board.getWinner(state);
				}
				if (pl != NONE) {
					return INCORRECT;
				}
				else {
					Player* afterDFS = new Player[board.emptyCounter]{ INCORRECT };
					Pawn* possiblePerfectMoves[2] = { nullptr };
					// sprawdzam ilosc dostepnych miejsc do wygrania gracza
					// jesli == 2, to gracz nie moze przegrac z perfect,
					// bo przez jedna turze nie zablokuje dwoch miejsc wygranych gracza
					board.checkPositions(player, afterDFS, true, player == RED ? 2 : 1, EMPTY, player, possiblePerfectMoves);

					if (possiblePerfectMoves[0] != nullptr && possiblePerfectMoves[1] != nullptr) {
						possiblePerfectMoves[0] = nullptr;
						possiblePerfectMoves[1] = nullptr;
						delete[] afterDFS;
						return player;
					}
					else {
						possiblePerfectMoves[0] = nullptr;
						possiblePerfectMoves[1] = nullptr;
						delete[] afterDFS;
						return INCORRECT;
					}
				}
			}
			return INCORRECT;
		}
		return INCORRECT;
	}
	else {
		return INCORRECT;
	}
}

void Hex::CAN_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT(Player toFind, Player afterDFS[], const Player& player, short emptyCounter) {
	--emptyCounter;
	board.updateStats(player, 1);
	for (short i = 0; i < board.emptyCounter; ++i) {
		if (board.emptyPlaces[i]->symbol != EMPTY) {
			*(afterDFS + i) = INCORRECT;
			continue;
		}

		board.emptyPlaces[i]->symbol = player;
		Player b = CAN_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT(player == RED ? 2 : 1, player, player == RED, emptyCounter);
		*(afterDFS + i) = b;
		if (b == toFind || b == NONE) {
			board.updateStats(player, -1);
			board.emptyPlaces[i]->symbol = EMPTY;
			return;
		}
		board.emptyPlaces[i]->symbol = EMPTY;
	}
	board.updateStats(player, -1);
}

Player Hex::Perfect3(Player toFind, Player player, short emptyCounter) {
	Player* afterDFS = new Player[board.emptyCounter]{ EMPTY };
	CAN_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT(toFind, afterDFS, player, emptyCounter);
	for (short k = 0; k < board.emptyCounter; ++k) {
		if (afterDFS[k] == toFind) {
			delete[] afterDFS;
			return toFind;
		}
	}
	delete[] afterDFS;
	return INCORRECT;
}

Player Hex::CAN_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT_2(const short& state, const Player& player, bool isRed, short emptyCounter) {
	if (board.get_IS_BOARD_CORRECT()) {
		if (board.getWinner(state) != NONE) {
			return INCORRECT;
		}
		else {
			board.countPlayersTurns(2, isRed);
			// tutaj najpierw sprawdzam czy wytarczy graczowi ruchow do zakonczenia gry
			// jesli nie, to INCORRECT (nie moze wygrac)
			if ((player == BLUE && (board.BLUE_PAWNS + board.blueTurns) < board.size) || (player == RED && (board.RED_PAWNS + board.redTurns) < board.size)) {
				return INCORRECT;
			}
			if (board.turns <= emptyCounter) {
				short emptyPlaces = board.emptyCounter;
				if (board.turns == 3) {
					return Perfect3(player, player, emptyCounter);
				}
				else if (board.turns == 4) {
					--emptyCounter;
					Player* afterDFS = new Player[emptyPlaces]{ EMPTY };
					short count = 0;
					if (isRed) {
						for (short i = 0; i < emptyPlaces; ++i) {
							if (board.emptyPlaces[i]->symbol != EMPTY) continue;
							// najpierw wstawiam pion przeciwnika
							// pozniej sprawdzam wygrana dla gracza
							// w zaleznosci od wynikow mam return z tej funkcji
							board.emptyPlaces[i]->symbol = BLUE;
							board.updateStats(BLUE, 1);

							board.countPlayersTurns(2, isRed);
							afterDFS[count++] = Perfect3(RED, player, emptyCounter);

							board.updateStats(BLUE, -1);
							board.emptyPlaces[i]->symbol = EMPTY;

							if (afterDFS[count - 1] != RED) {
								delete[] afterDFS;
								return INCORRECT;
							}
						}
						delete[] afterDFS;
						return player; // tutaj zawsze będzie RED
					}
					else {
						for (short i = 0; i < emptyPlaces; ++i) {
							if (board.emptyPlaces[i]->symbol != EMPTY) continue;
							// najpierw wstawiam pion przeciwnika
							// pozniej sprawdzam wygrana dla gracza
							// w zaleznosci od wynikow mam return z tej funkcji
							board.emptyPlaces[i]->symbol = RED;
							board.updateStats(RED, 1);

							board.countPlayersTurns(2, isRed);
							afterDFS[count++] = Perfect3(BLUE, player, emptyCounter);

							board.updateStats(RED, -1);
							board.emptyPlaces[i]->symbol = EMPTY;

							if (afterDFS[count - 1] != BLUE) {
								delete[] afterDFS;
								return INCORRECT;
							}
						}
						delete[] afterDFS;
						return player; // tutaj zawsze będzie BLUE
					}
				}
			}
			else {
				return INCORRECT;
			}
		}
		return INCORRECT;
	}
	else {
		return INCORRECT;
	}
}

Player Hex::CAN_RED_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT(const short& state, short emptyCounter) {
	return CAN_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT_2(state, RED, true, emptyCounter);
}

Player Hex::CAN_BLUE_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT(const short& state, short emptyCounter) {
	return CAN_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT_2(state, BLUE, false, emptyCounter);
}