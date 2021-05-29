#include "q2.h"


/* Deletes all the duplication node
and prints a board with the indexes of the list*/


void display(chessPosList * lst)
{
    int count_array[BOARDSIZE][BOARDSIZE];    /*  arr of the position  */
    delete_double_node(lst, count_array); /* delete duplicates */
    print_board(count_array);  /* print full board */
}



void print_board(int count_array[BOARDSIZE][BOARDSIZE])
{
    int i;
    for (i = 0; i <= BOARDSIZE * 2 + 2; ++i)
    {
        if (i % 2 == 0)
            print_line(); /* print line of border */
        else
            print_cell_line(i, count_array); /* print line of cell |num|num| with the List index */

        printf("\n");
    }
}
void print_line()
{/* print line of border */
    int i;
    for (i = 0; i <= BOARDSIZE * 4 + 4; i++)
    {
        if (i % 4 == 0)
            printf("+");
        else
            printf("-");
    }
}
void print_cell_line(int line, int count_array[BOARDSIZE][BOARDSIZE])
{ /* print line of cell |num|num|  */
    if (line == 1)
        print_line_of_number();  /* only in the first line - print line of number |1|2|3|4|... */
    else
    {
        for (int i = 0; i < BOARDSIZE * 4 + 5; i++)
        {
            if (i == 1) /* in the first col print A,B,C...  */
                printf(" %c", 'A' + (line - 2) / 2);

            else if (i != 2) /* skip on i = 2  */
            {
                if (i % 4 == 0)
                {
                    int row, col;
                    printf("|");

                    if ((line - 3) % 2 == 0)
                    {
                        row = (line - 3) / 2;
                        col = (i / 4) - 1;
                        if (count_array[row][col] != 0 && row >= 0 && col >= 0 && row < BOARDSIZE && col < BOARDSIZE)
                        { /* there is node in this location  */
                            if (count_array[row][col] > 9)
                            {/* the index of the node is two digit  */
                                printf(" %d", count_array[row][col]);
                                i = i + 3;
                            }
                            else
                            {/* the index of the node is single digit  */
                                printf(" %d", count_array[row][col]);
                                i = i + 2;
                            }
                        }
                    }
                }
                else
                {
                    printf(" ");
                }
            }
        }
    }
}
void print_line_of_number()
{/* print line of number |1|2|3|4|... */
    int x = 1;
    for (int i = 0; i < BOARDSIZE * 4 + 5; i++)
    {
        if (i == 0)
            printf("|");
        else if (i < 4)
            printf(" ");

        else if (i % 2 == 0 && x <= BOARDSIZE + 1 && i >= 4)
        {
            printf("| ");
            if (x != BOARDSIZE + 1)
                printf("%d ", x);
            x++;
        }
    }
}

/* delete duplicates and print the index on the board */
void delete_double_node(chessPosList* lst, int count_array[][BOARDSIZE])
{ /* delete duplicates and print the index on the board */

    chessPosCell* ptr, * prev = NULL;
    int row, col, index = 1;

    reset_arr(count_array); /*  0 in all cell  */

    ptr = lst->head;

    while (ptr != NULL)
    {
        row = ptr->position[0] - 'A';
        col = ptr->position[1] - '1';

        if (count_array[row][col] == 0) /*  the first position in the list node  */
        {
            count_array[row][col] = index; /* put the index in the arr */
            index++;
        }

        else /* there are more then one node - delete the node  */
        {
            delete_node(lst, ptr, prev);
            ptr = prev;
        }

        prev = ptr;
        ptr = ptr->next;
    }
}
void delete_node(chessPosList* lst, chessPosCell* delete_node, chessPosCell* prev)
{ /* delete the node (can×t be the first one) */
    if (delete_node->next == NULL) /* the last node */
    {
        prev->next = NULL;
        lst->tail = prev;
    }

    else /*middle node */
    {
        prev->next = delete_node->next;
    }
    free(delete_node);
}

/* List function */

void insertDataToEndList(chessPosList* lst, chessPos position)
{
    chessPosCell* newTail;
    newTail = createNode(position, NULL);
    insertNodeToEndList(lst, newTail);
}

void insertNodeToEndList(chessPosList* lst, chessPosCell* tail)
{
    if (isEmptyList(lst) == true)
        lst->head = lst->tail = tail;
    else
    {
        lst->tail->next = tail;
        lst->tail = tail;
    }
    tail->next = NULL;
}

void makeEmptyList(chessPosList* lst)
{
    lst->head = lst->tail = NULL;
}

chessPosCell* createNode(chessPos new_position, chessPosCell* next)
{
    chessPosCell* result;

    result = (chessPosCell*)malloc(sizeof(chessPosCell));

    result->position[0] = new_position[0];
    result->position[1] = new_position[1];
    result->next = next;

    return result;
}

bool isEmptyList(chessPosList* lst)
{
    if (lst->head == NULL)
        return true;
    else
        return false;
}
void freeChessPosList(chessPosList** lst)
{
    chessPosCell* ptr, * ptr2;

    if (isEmptyList(*lst))
        return;

    ptr = (*lst)->head;

    while (ptr->next != NULL)
    {
        ptr2 = ptr;
        ptr = ptr->next;
        free(ptr2);
    }
    free(ptr);
}