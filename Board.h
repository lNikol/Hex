#pragma once
#include "Pawn.h"
#include "Player.h"
const short ARR_SIZE = 11;

struct Board {
	short indexes[ARR_SIZE] = { 0 };
	Pawn* board[ARR_SIZE][ARR_SIZE] = { nullptr };
	short size = 0;
	short turns = 0, redTurns = 0, blueTurns = 0;
	short PAWNS_NUMBER = 0;
	short RED_PAWNS = 0;
	short BLUE_PAWNS = 0;

	bool IS_BOARD_CORRECT = false;
	Pawn* emptyPlaces[ARR_SIZE * ARR_SIZE] = { nullptr };
	short emptyCounter = 0;//, emptyCounter2 = 0
	
	bool get_IS_BOARD_CORRECT();

	void resetVisited();
	void getNeighbors(Pawn** neighbors, const Pawn* pawn, short& count);
	Player getWinner(const short& state);
	Player DFS(Pawn* pawn, bool isRed);
	Player IS_GAME_OVER(const short& state);
	
	void checkPositions(Player toFind, Player afterDFS[], bool isPerfect, const short& st, const char& player, const char& symbol, Pawn** possiblePerfectMoves);
	bool IS_BOARD_POSSIBLE(const short& state);
	
	void countPlayersTurns(const short& N, bool isRed);
	void updateStats(const char& s, const short& n);

	~Board();

};