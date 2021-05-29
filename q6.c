#include "q2.h"
#include "q3.h"
#include "q4.h"
#include "q5.h"
#include "q1.h"
#include "q6.h"
/*Question 6-
get a binary file name , that respresenting a chessPos list
return -1 if the file doesnt exict
		1 if not possible path
		2 if covers all board
		3 otherwise*/
int checkAndDisplayPathFromeFile(char* file_name)
{
	FILE* fp= fopen(file_name, "rb");
	if (!fp)//if file doesnt exict - return -1
		return -1;
	chessPosList lst = makeLstFromFile(fp);//make a chesspos list out of file
	
	chessPosCell* ptr = lst.head;
	printf("\n\n-6\n\n");
	while (ptr != NULL)
	{
		printf("%c%c ", ptr->position[0], ptr->position[1]);
		ptr = ptr->next;
	}
	printf("\n");







	chessPosArray*** possibleMovesMat = validKnightMoves();
	
	if (!checkIfPossiblePath(lst, possibleMovesMat))
		return 1;
	//need to delete doubles and print board
	display(&lst);
	if (countListCells(lst.head) == BOARDSIZE * BOARDSIZE)
		return 2;
	return 3;

}
chessPosList makeLstFromFile(FILE* fp)//gets a file pointer, return a chessPosList from it's data
{
	chessPosList lst;
	chessPosCell* head,*curr;
	short len;
	chessPos* arr;
	fread(&len, sizeof(short), 1, fp);
	makeEmptyList(&lst);
	getPositionsToList(fp, len, &lst);
	return lst;
}
void getPositionsToList(FILE* fp, int len, chessPosList* lst)// get a file pointer ,length and list , puts the chess positons from file to lst
{
	BYTE tempData[FULLBYTE];	//we read 3 bytes each time
	chessPos convertedData[FULL]; //and we convert them to 4 chessPos
	short leftover;
	chessPos temp;
	//fp is after the short number
	for (int i = 0; i < len/FULL; i ++)   //we read 3 bytes at a time
	{
		fread(tempData, sizeof(BYTE), FULLBYTE, fp);
		getDecotedData(tempData, convertedData,FULL);
		for (int j = 0;j < FULL;j++)
		{
			temp[0]= convertedData[j][0];
			temp[1]= convertedData[j][1];
			insertDataToEndList(lst,temp);
		}
	}
	//deal with leftovers 0/1/2/3
	leftover = len % 4;
	if (leftover == 0)
		return;
	fread(tempData, sizeof(BYTE), leftover, fp);
	getDecotedData(tempData, convertedData, leftover);
	for (int j = 0;j < leftover;j++)
	{
		temp[0] = convertedData[j][0];
		temp[1] = convertedData[j][1];
		insertDataToEndList(lst, temp);
	}
}
void getDecotedData(BYTE* data, chessPos* decData , int sizeToGet)//get sizeToGet chessPos from data and put into decData
{
	BYTE mask1 = 0xE0;	//11100000  byte 1 (most significant byte - the left most one)
	BYTE mask2 = 0x1C;	//00011100  byte 1
	BYTE mask3a = 0x03, mask3b = 0x80;	//0000001110000000 bytes 1+2 
	BYTE mask4 = 0x70;	//01110000  byte 2
	BYTE mask5 = 0x0E;	//00001110  byte 2
	BYTE mask6a = 0x01, mask6b = 0xC0;	//0000000111000000 bytes 2+3
	BYTE mask7 = 0x38;	//00111000  byte 3 (least significant byte)
	BYTE mask8 = 0x07;	//00000111	byte 3 
	
	decData[0][0] = ((data[0] & mask1) >> 5)+'A';
	decData[0][1] = ((data[0] & mask2) >> 2) + '1' ;
	if (sizeToGet == 1)
		return;
	decData[1][0] = ((data[0] & mask3a) << 1) | ((data[1] & mask3b) >> 7) + 'A';
	decData[1][1] = ((data[1] & mask4) >> 4) + '1' ;
	if (sizeToGet == 2)
		return;
	decData[2][0] = ((data[1] & mask5) >> 1) + 'A' ;
	decData[2][1] = ((data[1] & mask6a) << 2) | ((data[2] & mask6b) >> 6) + '1';
	if (sizeToGet == 3)
		return;
	decData[3][0] = ((data[2] & mask7) >> 3) + 'A';
	decData[3][1] = (data[2] & mask8) + '1' ;
}
bool checkIfPossiblePath(chessPosList lst, chessPosArray*** possibleMovesMat)//get a list , and the possibleMovesMat from q1 , return true if list represents possible path , false otherwise
{
	chessPosCell* curr = lst.head;

	while (curr->next != NULL)
	{
		chessPosArray* optionalCurrMoves = possibleMovesMat[curr->position[0]-'A'][curr->position[1]-'1'];
		if(!ifExictInArr(curr->next->position ,optionalCurrMoves ))
			return false;
		curr = curr->next;
	}
	return true;
}
bool ifExictInArr(chessPos pos, chessPosArray* arr)
{
	if (pos[0] == 'B' && pos[1] == '1')
	{
		printf("111111 ");
	}
	for (int i = 0;i < (*arr).size; i++)
	{
		if (pos[0] == 'B' && pos[1] == '1')
		{
			printf("%c%c ", (*arr).positions[i][0] , (*arr).positions[i][1]);
		}

		if ((*arr).positions[i][0] == pos[0] && (*arr).positions[i][1] == pos[1])
			return true;
	}
	return false;
}
