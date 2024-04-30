#pragma once
struct Pawn {
	char symbol;
	short x, y;
	bool visited = false;
	Pawn(char s, short yy, short xx) {
		symbol = s;
		y = yy;
		x = xx;
	}
};