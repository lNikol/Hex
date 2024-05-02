#pragma once
#include "Pawn.h"
#include "Board.h"
using namespace std;

struct Hex {
	Board board;

	bool isMaxOldSet = false;
	bool isSecondPart = false;
	short oldTags = 0, maxOldTags = 0;
	short lineCounter = 0;
	Player CAN_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT(const short& state, const Player& player, bool isRed, short emptyCounter);
	Player CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT(const short& state, short emptyCounter);
	Player CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT(const short& state, short emptyCounter);

	Player CAN_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT(const short& state, const Player& player, bool isRed, short emptyCounter);
	Player CAN_RED_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT(const short& state, short emptyCounter);
	Player CAN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT(const short& state, short emptyCounter);

	Player CAN_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT(const short& state, const Player& player, bool isRed, short emptyCounter);

	Player Perfect3(Player toFind, Player player, short emptyCounter);

	void CAN_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT(Player toFind, Player afterDFS[], const Player& player, short emptyCounter);
	Player CAN_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT_2(const short& state, const Player& player, bool isRed, short emptyCounter);
	Player CAN_RED_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT(const short& state, short emptyCounter);
	Player CAN_BLUE_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT(const short& state, short emptyCounter);

};
