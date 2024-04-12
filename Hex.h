#pragma once
// PAWNS_NUMBER ilość r i b w hexie

struct Hex {
	char hex[21][12]; 
	short lineCounter = 0;
	short symbolCounter = 0;
	short elementsCounter = 0;
	short BOARD_SIZE = 0;
	short PAWNS_NUMBER = 0;
	short RED_PAWNS = 0;
	short BLUE_PAWNS = 0;
	bool IS_BOARD_POSSIBLE = false;
	bool CAN_RED_WIN_IN_N_MOVE_WITH_NAIVE_OPPONENT = false;
	bool CAN_RED_WIN_IN_N_MOVE_WITH_PERFECT_OPPONENT = false;
	char IS_GAME_OVER[9];


	Hex();
	void setHexBoardSize(const short& size);
	void setPlayerSymbol(char s, const short& line, const short& cell);
	void drawHex();

};