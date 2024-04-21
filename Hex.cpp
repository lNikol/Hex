#include "Hex.h"
#include <iostream>
#include <fstream>
using namespace std;

Hex::Hex() {
}

void Hex::setHexBoardSize(const short& size) {

}

void Hex::setPlayerSymbol(char s, const short& line, const short& cell) {
	
}

bool Hex::get_IS_BOARD_CORRECT() {
	if (BLUE_PAWNS + 1 == RED_PAWNS || BLUE_PAWNS == RED_PAWNS) {
		IS_BOARD_CORRECT = true;
		//cout << "YES" << endl;
	}
	else {
		IS_BOARD_CORRECT = false;
		//cout << "NO" << endl;
	}
	return IS_BOARD_CORRECT;
}

void Hex::drawHex() {

}

void Hex::resetVisited() {
	short size = lineCounter / 2;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			board[i][j].visited = false;
			board[i][j].toBeVisited = false;
		}
	}
}

vector<Cell*> Hex::getNeighbors(const Cell* cell) { 
	// Cell:board[cell.line][board[cell.line].size() - board[cell.line].pos], // nie do konca jest poprawne
	// col: board[cell.line].size() - board[cell.line].pos;
	vector<Cell*> neighbors;
	short size = lineCounter / 2;
	// (-1,0),(-1,+1),(0,+1),(+1,0),(+1,-1),(0,-1)
	short dLines[] = { -1, 0, 1, 1, 0, -1 };
	short dPoses[] = { -1, -1, 0, 1, 1, 0 };
	
	for (short i = 0; i < 6; i++) {
		short newRow = cell->line + dLines[i];
		short newCol = cell->pos + dPoses[i];
		if (newRow >= 0 && newRow < size && newCol >= 0 && newCol < size) {
			neighbors.insert(neighbors.begin(), &board[newRow][newCol]);
		}
	}



	/*
	for game_is_over:
	if (board[newRow][newCol].symbol == cell.symbol && cell.symbol!=' ') {
		neighbors.insert(neighbors.begin(), board[newRow][newCol]);
	}
	jesli jakis gracz wygral, to nie setowac isVisited=false,
	bo bedzie nowy hex i nie ma sensu tego robic
	*/

	return neighbors;
}


bool Hex::beforeDFS(ofstream& file) {
	// dla czerwonego gracza z gornego do dolnego
	bool changed = false;
	for (auto c : board[0]) {
		if (c.symbol == 'r' && DFS(&c, true)) {
			changed = true; 
			if (file.is_open()) {
				file << "YES RED" << endl << endl;
			}
			//cout << "YES RED" << endl;
			return true;
		}
		else {
			if (changed) {
				resetVisited();
			}
		}
	}
	changed = false;
	for (int i = 0; i < lineCounter / 2; i++) {
		if (board[i][0].symbol == 'b' && DFS(&board[i][0], false)) {
			changed = true;
			if (file.is_open()) {
				file << "YES BLUE" << endl << endl;
			}
			//cout << "YES BLUE" << endl;
			return true;
		}
		else {
			if (changed) {
				resetVisited();
			}
		}
	}
	if (file.is_open()) {
		file << "NO" << endl << endl;
	}
	//cout << "NO" << endl;
	return false;
}

bool Hex::DFS(Cell* cell, bool isRed) {
	// przed wywolaniem dfs, zrobic for, ktory bedzie chodzil po wszystkim komorkach
	// i jesli dfs = false wywolac kolejny dfs dla kolejnej komorki, ale przed tym wywolac resetVisited
	cell->visited = true;
	vector<Cell*> neighbors = getNeighbors(cell);
	for (auto* c : neighbors) {
		if (c->symbol == cell->symbol && c->visited == false && c->symbol!=' ') {
			c->visited = true;
			if (c->line == (lineCounter) / 2 - 1 && isRed) {
				// ten warunek dla gracza czerwonego od lewej granicy do prawej
				// czerwony gracz
				return true;
			}
			else if (c->pos == (lineCounter) / 2 - 1 && !isRed) {
				// niebieski gracz
				return true;
			}
			if (DFS(c, isRed)) {
				return true;
			}
		}
	}
	if (lineCounter / 2 - 1 == 0) {
		if (isRed) {
			return true;
		}
		else {
			return false;
		}
	}
	return false;

}