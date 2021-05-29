#ifndef Q3
#define Q3
//#define DEBUG3

#include "q1.h"
#include "q2.h"

typedef struct _treeNodeListCell treeNodeListCell; //forward decleration

typedef struct _treeNode {
    chessPos position;
    treeNodeListCell* next_possible_positions;
}treeNode;

typedef struct _treeNodeListCell {
    treeNode* node;
    struct treeNodeListCell* next;
}treeNodeListCell;

typedef struct _pathTree {
    treeNode* root;
}pathTree;
pathTree findAllPossibleKnightPaths(chessPos* startingPosition);
treeNode* findAllPossibleKnightPathsHelper(chessPos* startingPosition, chessPosArray*** allPossibleMovesMat, bool prevPath[][BOARDSIZE]);
chessPosList arrToLst(chessPosArray* arr, bool prevPath[][BOARDSIZE]);
void freePathTree(pathTree tr);
void freePathTreeHelper(treeNode* root);
#endif