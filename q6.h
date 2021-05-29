#ifndef Q6
#define Q6
#include "q5.h"

#define FULL 4 // in full 3 bytes we have room for 4 chessPos
#define FULLBYTE 3

int checkAndDisplayPathFromeFile(char* file_name);
chessPosList makeLstFromFile(FILE* fp);
void getPositionsToList(FILE* fp, int len, chessPosList* lst);
void getDecotedData(BYTE* data, chessPos* decData, int sizeToGet);
bool checkIfPossiblePath(chessPosList lst, chessPosArray*** possibleMovesMat);
bool ifExictInArr(chessPos pos, chessPosArray* arr);
#endif