#pragma once
#include <string>
#include "Cell.h"
using namespace std;
const short ARR_SIZE = 11;

struct Hex {
	short indexes[ARR_SIZE] = { 0 };
	Cell* board[ARR_SIZE][ARR_SIZE] = { nullptr };
	
	bool isMaxOldSet = false;
	short oldTags = 0, maxOldTags = 0;
	short whoWon = -1; //0 - tie, 1 - red, 2 - blue
	short lineCounter = 0;
	short size = 0;
	short turns = 0, redTurns = 0, blueTurns = 0;
	short BOARD_SIZE = 0;
	short PAWNS_NUMBER = 0;
	short RED_PAWNS = 0;
	short BLUE_PAWNS = 0;
	short testNumber = 0;
	bool IS_BOARD_CORRECT = false;
	Cell* emptyPlaces[ARR_SIZE * ARR_SIZE] = { nullptr };
	short emptyCounter = 0, emptyCounter2 = 0;

	Hex();
	void setPlayerSymbol(char s, const short& line, const short& cell);
	bool get_IS_BOARD_CORRECT();
	void resetVisited(const char& player);
	void getNeighbors(Cell** neighbors, const Cell* cell, short& count);
	bool beforeDFS(const short& state);
	bool DFS(Cell* cell, bool isRed);
	bool IS_GAME_OVER(const short& state);
	void checkPositions(short afterDFS[], bool isPerfect, const short& st, const char& player, const char& symbol, Cell** perfectPlayerTurns);
	bool IS_BOARD_POSSIBLE(const short& state);
	void countPlayersTurns(const short& N, bool isRed);
	void updateStats(const char& s, const short& n);


	bool CAN_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT(const short& state, const char& player, bool isRed);
	bool CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT(const short& state);
	bool CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT(const short& state);
	
	bool CAN_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT(const short& state, const char& player, bool isRed);
	bool CAN_RED_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT(const short& state);
	bool CAN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT(const short& state);

	bool CAN_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT(const short& state, const char& player, bool isRed, const short& emptyCounter_);
	bool CAN_RED_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT(const short& state);
	bool CAN_BLUE_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT(const short& state);

	void CAN_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT(short afterDFS[], const short& state, const char& player);
	bool CAN_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT_2(const short& state, const char& player, bool isRed);
	bool CAN_RED_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT(const short& state);
	bool CAN_BLUE_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT(const short& state);

	~Hex();
};
