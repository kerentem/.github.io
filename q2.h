
#ifndef Q2
#define Q2
#include "utilities.h"
#include "q1.h"
typedef struct chessPosCell
{
    chessPos position;
    struct chessPosCell* next;
}chessPosCell;

typedef struct chessPosList
{
    chessPosCell* head;
    chessPosCell* tail;
}chessPosList;



void print_board(int count_array[BOARDSIZE][BOARDSIZE]);
void print_cell_line(int line, int count_array[BOARDSIZE][BOARDSIZE]);
void print_line();
void print_line_of_number();


void display(chessPosList* lst);


void delete_double_node(chessPosList* lst, int count_array[][BOARDSIZE]);
void delete_node(chessPosList* lst, chessPosCell* delete_node, chessPosCell* prev);


void insertNodeToEndList(chessPosList* lst, chessPosCell* tail);
void insertDataToEndList(chessPosList* lst, chessPos position);
chessPosCell* createNode(chessPos new_position, chessPosCell* next);
void makeEmptyList(chessPosList* lst);
bool isEmptyList(chessPosList* lst);
void freeChessPosList(chessPosList** lst);


#endif //_2_QUESTION_2_H

