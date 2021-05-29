#ifndef Q7
#define Q7

#include "utilities.h"

#include "q1.h"
#include "q2.h"
#include "q3.h"
#include "q4.h"
#include "q5.h"
#include "q6.h"

void menu();
void print_menu();
void vaild_location(chessPos* pos);
char* getNameFile();

void option_one(chessPos* pos);
pathTree option_two(chessPos* pos, bool* location);
chessPosList* option_3(chessPos* pos, pathTree* PathTree, bool* location, bool* tree, bool* listPath);
void option_4(chessPos* pos, pathTree* PathTree, chessPosList** path, bool* location, bool* tree, bool* listPath);
void option_5();

#endif //Q7
