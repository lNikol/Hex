#pragma once
#include <vector>
#include <string>
#include "Cell.h"
using namespace std;
const size_t SIZE = 11;

struct Hex {
	vector<vector<Cell>> board = vector<vector<Cell>>(SIZE);
	bool isMaxOldSet = false;
	short oldTags = 0, maxOldTags = 0;
	short whoWon = -1; //0 - tie, 1 - red, 2 - blue
	short lineCounter = 0;
	short size = 0, empty_places = 0;
	short turns = 0, redTurns = 0, blueTurns = 0;
	short BOARD_SIZE = 0;
	short PAWNS_NUMBER = 0;
	short RED_PAWNS = 0;
	short BLUE_PAWNS = 0;
	bool IS_BOARD_CORRECT = false;


	Hex();
	void setPlayerSymbol(char s, const short& line, const short& cell);
	bool get_IS_BOARD_CORRECT(ofstream& file);
	void resetVisited();
	vector<Cell*> getNeighbors(const Cell* cell);
	bool beforeDFS(vector<vector<Cell>>& board, const short& state);
	bool DFS(Cell* cell, bool isRed);
	bool IS_GAME_OVER(const short& state, ofstream& file);
	bool IS_BOARD_POSSIBLE(ofstream& file, const short& state);
	bool CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT(ofstream& file, const short& state);
	void countNaiveTurns(const short& N, bool isRed);
};