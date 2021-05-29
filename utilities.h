#ifndef UTILITIES
#define UTILITIES
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE 

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#define BOARDSIZE 5
#define UPPER_LIMIT 'A'
#define LOWER_LIMIT 'E'
#define RIGHT_LIMIT '5'
#define LEFT_LIMIT '1'

void makeFalseArr(bool prevPath[][BOARDSIZE]);
void reset_arr(int count_array[][BOARDSIZE]);
void checkMemoryAllocation(void* ptr);

#endif

