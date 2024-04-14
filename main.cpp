#include <iostream>
#include "Hex.h"
using namespace std;

int main()
{
	Hex hex;
	short checkCounter = 0;
	char check[4];
	char request[46];
	short reqCounter = 0;
	char s = 'q';
	char container[6];
	bool wasSymbol = false;
	while (cin.get(s)) {
		if (s == '<') {
			wasSymbol = true;
			for (int i = 0; i < 5; ++i) {
				container[i] = s;
				cin.get(s);
			}
			hex.hex[hex.lineCounter][hex.symbolCounter] = container[2];
			hex.symbolCounter++;
			hex.elementsCounter++;
			switch (container[2])
			{
			case 'r': {
				hex.RED_PAWNS++;
				hex.PAWNS_NUMBER++;
				break;
			}
			case 'b': {
				hex.BLUE_PAWNS++;
				hex.PAWNS_NUMBER++;
				break;
			}
			default:
				break;
			}
			for (int i = 0; i < 5; ++i) {
				container[i] = '0';
			}
		}
		if (s == '\n' && wasSymbol) {
			hex.lineCounter++;
			hex.symbolCounter = 0;
			wasSymbol = false;
			for (int i = 0; i < 4; i++) {
				check[i] = '0';
			}
			checkCounter = 0;
		}
		if (s == '-' && hex.lineCounter != 0 && !wasSymbol) {
			check[checkCounter++] = s;
		}
		if (checkCounter >= 3) {
			while (cin >> s) {
				request[reqCounter++] = s;
			}
			if (strncmp(request, "BOARD_SIZE", reqCounter) == 0) {
				hex.BOARD_SIZE = hex.lineCounter / 2 + 1;
				hex.lineCounter = 0;
				hex.symbolCounter = 0;
				cout << hex.BOARD_SIZE << endl;
				
				for (int i = 0; i < 4; i++) {
					check[i] = '0';
				}
				checkCounter = 0;
			}
			else if (strncmp(request, "PAWNS_NUMBER", reqCounter) == 0) {
				if (hex.BLUE_PAWNS == hex.RED_PAWNS) {
					cout << "YES" << endl;
				}
				else {
					cout << "NO" << endl;
				}
			}
			else if (strncmp(request, "IS_BOARD_CORRECT", reqCounter) == 0) {
				cout << hex.PAWNS_NUMBER << endl;
			}
			
			for (int i = 0; i < reqCounter; i++) {
				request[i] = 0;
			}
			reqCounter = 0;
			hex = Hex();
		}
	}
}
