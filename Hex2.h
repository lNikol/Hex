#pragma once
#include "Pawn.h"
#include "Board.h"
using namespace std;

struct Hex2 {
	Board board;

	bool isMaxOldSet = false;
	bool isSecondPart = false;
	short oldTags = 0, maxOldTags = 0;
	short lineCounter = 0;
	bool CAN_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT(const short& state, const char& player, bool isRed, short emptyCounter);
	bool CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT(const short& state, short emptyCounter);
	bool CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT(const short& state, short emptyCounter);
	
	bool CAN_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT(const short& state, const char& player, bool isRed, short emptyCounter);
	bool CAN_RED_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT(const short& state, short emptyCounter);
	bool CAN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT(const short& state, short emptyCounter);

	bool CAN_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT(const short& state, const char& player, bool isRed, const short& emptyCounter_);
	bool CAN_RED_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT(const short& state);
	bool CAN_BLUE_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT(const short& state);

	void CAN_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT(short afterDFS[], const short& state, const char& player);
	bool CAN_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT_2(const short& state, const char& player, bool isRed);
	bool CAN_RED_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT(const short& state);
	bool CAN_BLUE_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT(const short& state);

};
