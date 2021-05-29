#include "q1.h"

/*Question1 -
return a pointer to Two-dimensional array of chess slots aaray.
To every slot match an array with optional moving slots*/
chessPosArray*** validKnightMoves()
{
	/*memory allocation*/
	chessPosArray*** res = (chessPosArray***)malloc(sizeof(chessPosArray**) * BOARDSIZE);
	checkMemoryAllocation(res);
	for (int i = 0;i < BOARDSIZE;i++)
	{
		res[i] = (chessPosArray**)malloc(sizeof(chessPosArray*) * BOARDSIZE);
		checkMemoryAllocation(res[i]);
	}


	chessPos slot;

	for (int i = 0; i < BOARDSIZE; i++)
	{
		for (int j = 0;j < BOARDSIZE;j++)
		{
			slot[0] = UPPER_LIMIT + i;
			slot[1] = LEFT_LIMIT + j;
			res[i][j] = createKnightPossibleMovesArrayP(slot);
		}
	}
	return res;
}
/*get a chessPos , returns a array of all the possible moves*/
chessPosArray* createKnightPossibleMovesArrayP(chessPos slot)
{
	chessPosArray* res = (chessPosArray*)malloc(sizeof(chessPosArray));
	checkMemoryAllocation(res);
	int count = 0;/*counting how many of the options available*/
	chessPos* positions = (chessPos*)malloc(sizeof(chessPos) * BOARDSIZE); /* max options */
	checkMemoryAllocation(positions);
	/*updating currsor*/
	chessPos optionalPos;
	optionalPos[0] = slot[0];
	optionalPos[1] = slot[1];

	/*2 down 1 right*/
	optionalPos[0] += 2;
	optionalPos[1]++;
	if (ifOptionalSlot(optionalPos))
	{
		copySlotToPointer(positions, optionalPos, count);
		count++;
	}
	/*2 down 1 left*/
	optionalPos[1] -= 2;
	if (ifOptionalSlot(optionalPos))
	{
		copySlotToPointer(positions, optionalPos, count);
		count++;
	}
	/*2 up 1 left*/
	optionalPos[0] -= 4;
	if (ifOptionalSlot(optionalPos))
	{
		copySlotToPointer(positions, optionalPos, count);
		count++;
	}
	/*2 up 1 right*/
	optionalPos[1] += 2;
	if (ifOptionalSlot(optionalPos))
	{
		copySlotToPointer(positions, optionalPos, count);
		count++;
	}
	/*1 up 2 right*/
	optionalPos[1] ++;
	optionalPos[0] ++;
	if (ifOptionalSlot(optionalPos))
	{
		copySlotToPointer(positions, optionalPos, count);
		count++;
	}
	/*1 down 2 right*/
	optionalPos[0] += 2;
	if (ifOptionalSlot(optionalPos))
	{
		copySlotToPointer(positions, optionalPos, count);
		count++;
	}
	/*1 down 2 left*/
	optionalPos[1] -= 4;
	if (ifOptionalSlot(optionalPos))
	{
		copySlotToPointer(positions, optionalPos, count);
		count++;
	}
	/*1 up 2 left*/
	optionalPos[0] -= 2;
	if (ifOptionalSlot(optionalPos))
	{
		copySlotToPointer(positions, optionalPos, count);
		count++;
	}

	positions = realloc(positions, count * (sizeof(chessPos)));
#ifdef DEBUG
for (int i = 0;i < count;i++)
		printf("%c%c\n", positions[i][0], positions[i][1]);
#endif // DEBUG

	res->positions = positions;
	res->size = count;
	return res;
}
/*gets a chess slot , return if its in the game board range*/
bool ifOptionalSlot(chessPos slot) 
{
	if (slot[0] > LOWER_LIMIT || slot[0] < UPPER_LIMIT || slot[1]>RIGHT_LIMIT || slot[1] < LEFT_LIMIT)
		return false;
	return true;
}
/*gets chessPos array, a chessPos and an index , copies slot into array in the index's place */
void copySlotToPointer(chessPos* pointer, chessPos slot, int index)
{
	pointer[index][0] = slot[0];
	pointer[index][1] = slot[1];
}
void freeMat(chessPosArray*** mat)
{
	for (int i = 0;i < BOARDSIZE;i++)
	{
		for (int j = 0;j < BOARDSIZE;j++)
		{
			free(mat[i][j]);
		}
		free(mat[i]);
	}
	free(mat);
}


