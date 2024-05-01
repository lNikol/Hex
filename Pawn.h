#pragma once
#include "Player.h"
struct Pawn {
	Player symbol;
	short x, y;
	bool visited = false;
	Pawn(char s, short yy, short xx) {
		symbol = (s == 'r' ? RED : s == 'b' ? BLUE : EMPTY);
		y = yy;
		x = xx;
	}
};