#pragma once

struct Cell {
	char symbol;
	short line, pos;
	bool visited = false;
	//bool toBeVisited = false;
	Cell(char s, short l, short pos_in_vector) {
		symbol = s;
		line = l;
		pos = pos_in_vector;
	}
};