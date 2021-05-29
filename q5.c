
#include "q5.h"

/*question 5 
get a file name and chessPos list
write in the binary file the chess pos list acording to instructions:
First , short number with the length of the list , then the list itself without waste of memory */

void saveListToBinFile(char* fileName, chessPosList* posList)
{
	FILE* fp;
	chessPosCell* curr = posList->head;
	short size , leftover;
	//open binary file
	fp = fopen(fileName, "wb");
	if (!fp)
		exit(2);

	//count the length of the list and write to file
	size = countListCells(posList->head);
	fwrite(&size, sizeof(short), 1, fp);

	//each time we take 4 chessPoss and convert them to 3 bytes
	chessPos position[4];

	for (int i = 0;i < size;i+=4)
	{
		if (size < 4||i+4>size)
			break;
		for (int j = 0;j < 4;j++)//put positions into array
		{
			position[j][0] = curr->position[0];
			position[j][1] = curr->position[1];
			curr = curr->next;
		}
		writeToFile4Pos(fp, position);
	}
	//deal with leftovers-0/1/2/3
	leftover = size % 4;
	switch (leftover)
	{
		case 1:
			writeToFile1Pos(fp, curr->position);
			break;
		case 2:
			for (int j = 0;j < 2;j++)//put positions into array
			{
				position[j][0] = curr->position[0];
				position[j][1] = curr->position[1];
				curr = curr->next;
			}
			writeToFile2Pos(fp, position);
			break;
		case 3:
			for (int j = 0;j < 3;j++)//put positions into array
			{
				position[j][0] = curr->position[0];
				position[j][1] = curr->position[1];
				curr = curr->next;
			}
			writeToFile3Pos(fp, position);
			break;
		default:
			break;
	}
	fclose(fp);
	
}
short countListCells(chessPosCell* head)//gets a list head , return the list length
{
	short count = 0;
	while (head != NULL)
	{
		count++;
		head = head->next;
	}
	return count;
}
void writeToFile4Pos(FILE* fp, chessPos posArr[4]) // print to fp the array of chessPos sized 4
{
	BYTE mask1 = 0xE0;	//11100000  byte 1 (most significant byte - the left most one)
	BYTE mask2 = 0x1C;	//00011100  byte 1
	BYTE mask3a = 0x03, mask3b = 0x80;	//00000011 10000000 bytes 1+2 
	BYTE mask4 = 0x70;	//01110000  byte 2
	BYTE mask5 = 0x0E;	//00001110  byte 2
	BYTE mask6a = 0x01, mask6b = 0xC0;	//00000001 11000000 bytes 2+3
	BYTE mask7 = 0x38;	//00111000  byte 3 (least significant byte)
	BYTE mask8 = 0x07;	//00000111	byte 3 
	BYTE data[3];//the 3 BYTE output

	data[0]=(((posArr[0][0] - 'A') << 5) & mask1)|(((posArr[0][1] - '1') << 2)& mask2);
	//[1][0] is divided
	data[0] = data[0] | (((posArr[1][0] - 'A') >> 1)& mask3a );
	data[1] = (((posArr[1][0] - 'A')<< 7 )& mask3b );
	//
	data[1]= data[1] | (((posArr[1][1] - '1') << 4) & mask4) | (((posArr[2][0] - 'A') << 1)& mask5);
	//[2][1] is divided
	data[1] = data[1] | ((posArr[2][1] - '1') >> 2)& mask6a ;
	data[2] = (((posArr[2][1] - '1')<< 6) & mask6b );
	//
	data[2]= data[2]|(((posArr[3][0] - 'A') << 3) & mask7) | ((posArr[3][1] - '1')& mask8);
	fwrite(data, sizeof(BYTE), 3, fp);
}
void writeToFile1Pos(FILE* fp, chessPos pos)// print to fp 1 chessPos 
{
	BYTE mask1 = 0xE0;	//11100000  byte 1 (most significant byte - the left most one)
	BYTE mask2 = 0x1C;	//00011100  byte 1

	BYTE res= (((pos[0] - 'A') << 5) & mask1) | (((pos[1] - '1') << 2) & mask2);
	fwrite(&res, sizeof(BYTE), 1, fp);
}
void writeToFile2Pos(FILE* fp, chessPos pos[2])// print to fp the array of chessPos sized 2
{
	BYTE mask1 = 0xE0;	//11100000  byte 1 (most significant byte - the left most one)
	BYTE mask2 = 0x1C;	//00011100  byte 1
	BYTE mask3a = 0x03, mask3b = 0x80;	//00000011 10000000 bytes 1+2 
	BYTE mask4 = 0x70;	//01110000  byte 2
	BYTE res[2];
	
	res[0]= ((((pos[0][0] - 'A') << 5) & mask1) | ((pos[0][1] - '1') << 2) & mask2);
	//[1][0] is divided
	res[0] = res[0] | (((pos[1][0] - 'A') >> 1) & mask3a);
	res[1] = (((pos[1][0] - 'A') << 7) & mask3b);
	//
	res[1] = res[1] | (((pos[1][1] - '1') << 4) & mask4);
	fwrite(res, sizeof(BYTE), 2, fp);
}
void writeToFile3Pos(FILE* fp, chessPos pos[3])// print to fp the array of chessPos sized 3
{
	BYTE mask1 = 0xE0;	//11100000  byte 1 (most significant byte - the left most one)
	BYTE mask2 = 0x1C;	//00011100  byte 1
	BYTE mask3a = 0x03, mask3b = 0x80;	//00000011 10000000 bytes 1+2 
	BYTE mask4 = 0x70;	//01110000  byte 2
	BYTE mask5 = 0x0E;	//00001110  byte 2
	BYTE mask6a = 0x01, mask6b = 0xC0;	//00000001 11000000 bytes 2+3
	BYTE res[3];

	res[0] = ((((pos[0][0] - 'A') << 5) & mask1) | ((pos[0][1] - '1') << 2) & mask2);
	//[1][0] is divided
	res[0] = res[0] | (((pos[1][0] - 'A') >> 1) & mask3a);
	res[1] = (((pos[1][0] - 'A') << 7) & mask3b);
	//
	res[1] = res[1] | (((pos[1][1] - '1') << 4) & mask4) | (((pos[2][0] - 'A') << 1) & mask5);
	//[2][1] is divided
	res[1] = res[1] | ((pos[2][1] - '1') >> 2) & mask6a;
	res[2] = (((pos[2][1] - '1') << 6) & mask6b);
	//
	fwrite(res, sizeof(BYTE), 3, fp);
}