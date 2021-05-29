
#include "q4.h"
#include "utilities.h"

chessPosList* findknightPathCoveringAllBoard(pathTree* path_tree)
{
    int counter = 0; /* size of the arr that contain the path */
    chessPosCell arr[BOARDSIZE * BOARDSIZE]; /* arr that contain the path */

    chessPosList* lst;

    findknightPathCoveringAllBoard_Helper(path_tree->root, arr, &counter);

#ifdef DEBUG4
    for (int i = 0; i < BOARDSIZE * BOARDSIZE; ++i)
    {
        printf("%c%c -> ", arr[i].position[0], arr[i].position[1]);
    }
    printf("\n\n\n");
#endif


    if (counter == BOARDSIZE * BOARDSIZE)/* we found path that contain all the cell in the board */
    {
        lst = makeListFromArr(arr, counter); /* make list from the arr */

#ifdef DEBUG4
        printList(lst);
#endif
        return lst;
    }
    else
        return NULL; /* not found */
}

void findknightPathCoveringAllBoard_Helper(treeNode* root, chessPosCell arr[], int* count)
{
    treeNodeListCell* ptr;
    bool skip = false;

    ptr = root->next_possible_positions;

    if (root->next_possible_positions == NULL)
    { /* leaf */
        if (*count != BOARDSIZE * BOARDSIZE) ///////////////////////////////////////
        {
            arr[*count].position[0] = root->position[0];
            arr[*count].position[1] = root->position[1];
            *count = *count + 1;
        }
    }

    while (ptr != NULL)
    {
        if (skip == false)
        {
            if (*count != BOARDSIZE * BOARDSIZE) 
            { /* not found path yet */
                arr[*count].position[0] = root->position[0];
                arr[*count].position[1] = root->position[1];
                *count = *count + 1;
            }
        }
        skip = false;

        findknightPathCoveringAllBoard_Helper(ptr->node, arr, count);

        if (*count != BOARDSIZE * BOARDSIZE)//////////////////////////////////////////////////
        {
            *count = *count - 1;
            skip = true; /* skip on the put root in the arr */
        }
        ptr = ptr->next;
    }
}

chessPosList* makeListFromArr(chessPosCell arr[], int size)
{/* make chessPosList from arr */
    chessPosList* path;
    int i;
    path = (chessPosList*)malloc(sizeof(chessPosList*)); /* list of path */
    checkMemoryAllocation(path);
    makeEmptyList(path);

    for (i = 0; i < size; ++i)
    {
        insertDataToEndList(path, arr[i].position);
    }
    return path;
}