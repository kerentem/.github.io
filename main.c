#include "q4.h"
#include "q3.h"
#include "q2.h"
#include "q1.h"
#include "q5.h"
#include "q6.h"
#include "q7.h"
void main()
{
    menu();
}
/*void main()
{
	//main q1
	chessPosArray*** res = validKnightMoves();
   // need to to free to q1
	//main q2
    chessPosList lst;
    chessPosCell* node1 = (chessPosCell*)malloc(sizeof(chessPosCell));
    chessPosCell* node2 = (chessPosCell*)malloc(sizeof(chessPosCell));
    chessPosCell* node3 = (chessPosCell*)malloc(sizeof(chessPosCell));
    node3->next = NULL;
    node3->position[0] = 'A';
    node3->position[1] = '2';

    node2->next = node3;
    node2->position[0] = 'A';
    node2->position[1] = '2';

    node1->next = node2;
    node1->position[0] = 'A';
    node1->position[1] = '2';

    lst.head =node1;
    lst.tail = node3;
    // display(&lst);
   // free(node1);

    //main q3
/*
    pathTree pathT;
    chessPos p;
    p[0] = 'A';
    p[1] = '2';

    pathT = findAllPossibleKnightPaths(&p);
    //freePathTree(pathT);

    //main q4
   // findLongestPath(pathT.root);*/

    //main 5
   // saveListToBinFile("res.bin", &lst);
    //main 6
  //  checkAndDisplayPathFromeFile("res.bin");
   
//}