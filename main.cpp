#include <iostream>
#include "Hex.h"
using namespace std;

int main()
{
	Hex hex;
	char s = 'q';
	char container[6];
	bool wasSymbol = false;
	while (s != EOF) {
		cin.get(s);
		if (s == '<') {
			wasSymbol = true;
			for (int i = 0; i < 5; i++) {
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
			for (int i = 0; i < 5; i++) {
				container[i] = '0';
			}
		}
		if (s == '\n' && wasSymbol) {
			hex.lineCounter++;
			hex.symbolCounter = 0;
			wasSymbol = false;
		}
	}
	hex.BOARD_SIZE = hex.lineCounter / 2 + 1;
	hex.lineCounter = 0;
	hex.symbolCounter = 0;
	cout << hex.BOARD_SIZE << endl;
}
