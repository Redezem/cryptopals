#include <stdlib.h>
#include <string.h>
#include "hexConverter.h"

char* HexToBytes(char* inputStr) //This is long and extremely verbose but I've got no idea how to do this otherwise
{
	char* miniChunk = (char*)malloc(sizeof(char)*2);
	unsigned char* maxiChunk = (char*)malloc(sizeof(char)*strlen(inputStr)/2+1);
	int tens, ones;
	for(int i=0;i<strlen(inputStr);i++)
	{
		miniChunk[0] = inputStr[i];
		i++;
		if(i==strlen(inputStr))
		{
			miniChunk[1] = '0';
		}
		else
		{
			miniChunk[1] = inputStr[i];
		}
		switch(miniChunk[0])
		{
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '9':
				tens = 10*(int)miniChunk[0];
				break;
			case 'A':
			case 'a':
				tens = 100;
				break;
			case 'B':
			case 'b':
				tens = 110;
				break;
			case 'C':
			case 'c':
				tens = 120;
				break;
			case 'D':
			case 'd':
				tens = 130;
				break;
			case 'E':
			case 'e':
				tens = 140;
				break;
			case 'F':
			case 'f':
				tens = 150;
				break;
			default:
				tens = 0;
				break;
		}
		switch(miniChunk[0])
		{
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '9':
				ones = (int)miniChunk[0];
				break;
			case 'A':
			case 'a':
				ones = 10;
				break;
			case 'B':
			case 'b':
				ones = 11;
				break;
			case 'C':
			case 'c':
				ones = 12;
				break;
			case 'D':
			case 'd':
				ones = 13;
				break;
			case 'E':
			case 'e':
				ones = 14;
				break;
			case 'F':
			case 'f':
				ones = 15;
				break;
			default:
				ones = 0;
				break;
		}
		maxiChunk[i/2]=(unsigned char)(ones+tens);
	}
	free(miniChunk);
	return maxiChunk;
}

