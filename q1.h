#ifndef Q1_H
#define Q1_H
#include "utilities.h"
typedef char chessPos[2]; // Chess slot

typedef struct _chessPosArray {
	unsigned int size;
	chessPos* positions;
} chessPosArray;

chessPosArray*** validKnightMoves();
chessPosArray* createKnightPossibleMovesArrayP(chessPos slot);
bool ifOptionalSlot(chessPos slot);
void copySlotToPointer(chessPos * pointer, chessPos slot, int index);
void freeMat(chessPosArray*** mat);

#endif