#pragma once

struct Cell {
	char symbol;
	short line, pos;
	bool visited = false;
	Cell(char s, short l, short p) {
		symbol = s;
		line = l;
		pos = p;
	}
};