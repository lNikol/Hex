#include "Hex.h"

Hex::Hex() {
}

void Hex::setHexBoardSize(const short& size) {

}

void Hex::setPlayerSymbol(char s, const short& line, const short& cell) {
	hex[line][cell] = s;
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