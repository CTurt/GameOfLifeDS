#include "memory.h"

void setupState(void) {
	unsigned short *v = (unsigned short *)nextState;
	
	v[100 + (100 * 256)] = 31;
	v[101 + (100 * 256)] = 31;
	v[101 + (98 * 256)] = 31;
	v[103 + (99 * 256)] = 31;
	v[104 + (100 * 256)] = 31;
	v[105 + (100 * 256)] = 31;
	v[106 + (100 * 256)] = 31;
}

int getNeighbours(int i) {
	int n = 0;
	
	int x, y;
	for(x = -1; x < 2; x++) {
		for(y = -1 * 256; y < 2 * 256; y += 256) {
			if(!x && !y) continue;
			if(((unsigned short *)currentState)[i + x + y]) n++;
		}
	}
	
	return n;
}

void emulate(void) {
	int i;
	for(i = 0; i < 256 * 192; i++) {
		int n = getNeighbours(i);
		
		switch(n) {
			case 0:
			case 1:
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
			((unsigned short *)nextState)[i] = 0;
			break;
			
			case 3:
			((unsigned short *)nextState)[i] = 31;
			break;
		}
	}
}
