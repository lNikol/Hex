#pragma once
#include <vector>
#include <string>
#include "Cell.h"
// PAWNS_NUMBER ilość r i b w hexie
using namespace std;
const size_t SIZE = 11;

struct Hex {
	vector<vector<Cell>> board = vector<vector<Cell>>(SIZE);
	bool isMaxOldSet = false;
	short oldTags = 0, maxOldTags = 0;
	short whoWon = -1; //0 - tie, 1 - red, 2 - blue
	short lineCounter = 0;
	short BOARD_SIZE = 0;
	short PAWNS_NUMBER = 0;
	short RED_PAWNS = 0;
	short BLUE_PAWNS = 0;
	bool IS_BOARD_CORRECT = false;


	Hex();
	void setHexBoardSize(const short& size);
	void setPlayerSymbol(char s, const short& line, const short& cell);
	bool get_IS_BOARD_CORRECT();
	void resetVisited();
	vector<Cell*> getNeighbors(const Cell* cell);
	bool beforeDFS(vector<vector<Cell>>& board_, const short& state, short& whoWon_);
	bool DFS(Cell* cell, bool isRed);
	void IS_BOARD_POSSIBLE(ofstream& file, const short& state);
};