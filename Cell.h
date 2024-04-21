#pragma once

struct Cell {
	char symbol;
	bool visited = false;
	bool toBeVisited = false;
	Cell(char s) {
		symbol = s;
	}
};