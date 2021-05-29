#ifndef Q4
#define Q4
#include "q3.h"
#include "q2.h"
#include "q1.h"
#include "utilities.h"
// #define DEBUG4

chessPosList* findknightPathCoveringAllBoard(pathTree* path_tree);
void findknightPathCoveringAllBoard_Helper(treeNode* root, chessPosCell arr[], int* count);
chessPosList* makeListFromArr(chessPosCell arr[], int size);

#endif

