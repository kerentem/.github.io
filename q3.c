#include "q3.h"
#include "q2.h"
#include "q1.h"


/*Question3-
Make a pathTree acording to starting position without repeat the path and returns it*/
pathTree findAllPossibleKnightPaths(chessPos* startingPosition)
{
    pathTree pathT;
    chessPosArray*** allPossibleMovesMat = validKnightMoves();
    bool prevPath[BOARDSIZE][BOARDSIZE];
    makeFalseArr(prevPath);
    pathT.root = findAllPossibleKnightPathsHelper(startingPosition, allPossibleMovesMat, prevPath);
    return pathT;
}
/*Make a tree root to pathTree and return it
gets a starting position , the matrix of all possible moves from q1 and prevPath as a changing output parameter*/
treeNode* findAllPossibleKnightPathsHelper(chessPos* startingPosition, chessPosArray*** allPossibleMovesMat, bool prevPath[][BOARDSIZE])
{
    chessPosCell* curr; //currsur
    chessPosArray* arr; //helping type
    chessPosList possibleMoves;
    treeNode* res, * temp;
    treeNodeListCell* prevList = NULL;
    treeNodeListCell* tempList;

#ifdef DEBUG3
    printf("%c%c: ", startingPosition[0][0], startingPosition[0][1]);
    // printPath(prevPath);
#endif

    /*insert into possibleMoves all the moves that didnt appeared in prevPath*/
    arr = allPossibleMovesMat[startingPosition[0][0] - 'A'][startingPosition[0][1] - '1'];

    possibleMoves = arrToLst(arr, prevPath); ////

    /*make a new node from starting position and insert into prevPath*/
    //insertDataToEndList(prevPath, startingPosition);
    ///
    prevPath[startingPosition[0][0] - 'A'][startingPosition[0][1] - '1'] = true;

    /*next actions acording to if starting position have possible moves or not*/
    if (isEmptyList(&possibleMoves))//starting position doesnt have possible moves
    {
        // deleteTail(prevPath);
        prevPath[startingPosition[0][0] - 'A'][startingPosition[0][1] - '1'] = false;

        res = (treeNode*)malloc(sizeof(treeNode));
        checkMemoryAllocation(res);
        res->next_possible_positions = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));
        checkMemoryAllocation(res->next_possible_positions);

        res->next_possible_positions = NULL;
        res->position[0] = startingPosition[0][0];
        res->position[1] = startingPosition[0][1];
        return res;
    }

    else//starting position have possible moves
    {
        res = (treeNode*)malloc(sizeof(treeNode));
        checkMemoryAllocation(res);
        res->next_possible_positions = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));
        checkMemoryAllocation(res->next_possible_positions);

        res->position[0] = startingPosition[0][0];
        res->position[1] = startingPosition[0][1];


        curr = possibleMoves.head;

        while (curr != NULL)
        {
            temp = findAllPossibleKnightPathsHelper(curr->position, allPossibleMovesMat, prevPath);
            tempList = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));
            ///
            tempList->node = temp;
            tempList->next = NULL;


            if (prevList == NULL)
            {
                res->next_possible_positions = tempList;
            }

            else
            {
                prevList->next = tempList;
            }
            prevList = tempList;
            curr = curr->next;
        }
        //deleteTail(prevPath);
        prevPath[startingPosition[0][0] - 'A'][startingPosition[0][1] - '1'] = false;
    }
    return res;
}

chessPosList arrToLst(chessPosArray* arr, bool prevPath[][BOARDSIZE])
{/*take the arr of possible moves , delete the items that appear in prevPath and turn it to a list*/
    int i;
    chessPosList pos;
    chessPos p;
    makeEmptyList(&pos);
    if (arr != NULL)
    {
        for (i = 0; i < arr->size; i++)
        {
            p[0] = arr->positions[i][0];
            p[1] = arr->positions[i][1];
            if (prevPath[p[0] - 'A'][p[1] - '1'] == false)
            {
#ifdef DEBUG3
                printf("%c%c  ", arr->positions[i][0], arr->positions[i][1]);
#endif
                insertDataToEndList(&pos, p);
            }
        }
#ifdef DEBUG3
        printf(" \n");
#endif
    }
    return pos;
}

void freePathTree(pathTree tr)
{/*free a pathTree*/
    freePathTreeHelper(tr.root);
}
void freePathTreeHelper(treeNode* root)
{
    treeNode* curr, * tmp;
    if (root == NULL)
        return;
    if (root->next_possible_positions == NULL)
        free(root);
    else//not a leaf
    {
        curr = root->next_possible_positions->node;
        while (curr != NULL)
        {
            tmp = curr->next_possible_positions;
            freePathTreeHelper(curr);
            curr = tmp;
        }
    }
}