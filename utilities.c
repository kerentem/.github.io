#include "utilities.h"
void makeFalseArr(bool prevPath[][BOARDSIZE])
{
    int i, j;
    for (i = 0; i < BOARDSIZE; ++i)
    {
        for (j = 0; j < BOARDSIZE; ++j)
        {
            prevPath[i][j] = false;
        }
    }
}
void reset_arr(int count_array[][BOARDSIZE])
{/*  zero in all cell  */
    int i, j;
    for (i = 0; i < BOARDSIZE; i++)
    {
        for (j = 0; j < BOARDSIZE; j++)
        {
            count_array[i][j] = 0;
        }
    }
}
void checkMemoryAllocation(void* ptr)
{/* check Memory Allocation */
    if (ptr == NULL)
    {
        puts("Memory allocation failed");
        exit(1);
    }
}