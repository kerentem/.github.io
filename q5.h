#ifndef Q5
#define Q5
#include "q1.h"
#include "q2.h"
#include "utilities.h"
typedef unsigned char BYTE;

void saveListToBinFile(char* fileName, chessPosList* posList);
short countListCells(chessPosCell* head);
void writeToFile4Pos(FILE* fp, chessPos posArr[4]);
void writeToFile1Pos(FILE* fp, chessPos pos);
void writeToFile2Pos(FILE* fp, chessPos pos[2]);
void writeToFile3Pos(FILE* fp, chessPos pos[3]);
#endif
