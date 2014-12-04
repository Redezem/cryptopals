#include "basesixtyfour.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct baseMatcher* GenerateMatchingArray()
{
	struct baseMatcher* baseString=(struct baseMatcher*)malloc(sizeof(struct baseMatcher)*64);
	int i = 0;
	char base = 0;
	for(i=0;i<64;i++)
	{
		if(i<26)
		{
			if(i==0)
			{
				base='A';
			}else{
				base++;
			}
		}else if(i<52){
			if(i==26)
			{
				base='a';
			}else{
				base++;
			}
		}else if(i<62){
			if(i==52)
			{
				base='0';
			}else{
				base++;
			}
		}else{
			if(i==62){
				base = '+';
			}
			if(i==63){
				base = '/';
			}
		}
		baseString[i].matchInt = i;
		baseString[i].matchChar = base;
	}
	return baseString;
}
char* ConvertByteStr(char* byteString, struct baseMatcher* matchArr)
{
	int strLen = strlen(byteString)+1;
	char* finalByteStr = (char*)calloc(strLen,sizeof(char));
	char* returnEncStr;
	if(strLen%3!=0)
	{
		if(strLen%3==2)
		{
			free(finalByteStr);
			finalByteStr = (char*)calloc((strLen+2),sizeof(char));
		}
		if(strLen%3==1)
		{
			free(finalByteStr);
			finalByteStr = (char*)calloc((strLen+1),sizeof(char));
		}
	}
	strcpy(finalByteStr,byteString); //Woah, ram magic
	returnEncStr = (char*)calloc(((strlen(finalByteStr)/3)*4),sizeof(char));
	int k = 0;
	for(int i=0; i<strlen(finalByteStr); i=i+3)
	{
		char* encStr=EncodeStr(finalByteStr[i],finalByteStr[i+1],finalByteStr[i+2],matchArr);
		for(int j = 0; j<4; j++)
		{
			returnEncStr[k]=encStr[j];
			k++;
			//and this will all work because of those mathematical preconditions we put up there with the modulo operator
		}
	}

	return returnEncStr;
}
char* ConvertCodeStr(char* codeString, struct baseMatcher* matchArr)
{
	int strLen = (strlen(codeString)+1)*3;
	char* finalByteStr = (char*)calloc(strLen,sizeof(char));
	
}
char* EncodeStr(char one, char two, char three, struct baseMatcher* matchArr) //Unwound by hand cause why not
{
	unsigned int magicInt = 0; //blank number for transposition
	unsigned int patchInt = 63; // is equal to 111111
	char* finalArr = (char*)calloc(4,sizeof(char)); //get me an array of 4 chars
	magicInt = magicInt ^ one;
	magicInt = magicInt << 8;
	magicInt = magicInt ^ two;
	magicInt = magicInt << 8;
	magicInt = magicInt ^ three;
	finalArr[0] = FindTheMatch(magicInt & patchInt, matchArr);
	magicInt = magicInt >> 6;
	finalArr[1] = FindTheMatch(magicInt & patchInt, matchArr);
	magicInt = magicInt >> 6;
	finalArr[2] = FindTheMatch(magicInt & patchInt, matchArr);
	magicInt = magicInt >> 6;
	finalArr[3] = FindTheMatch(magicInt & patchInt, matchArr);
	return finalArr;
}
char* DecodeStr(char one, char two, char three, char four, struct baseMatcher* matchArr) //A reverse of above
{
	unsigned int magicInt = 0;
	unsigned int patchInt = 255; // equal to 11111111
	char* finalArr = (char*)calloc(3,sizeof(char));
	magicInt = magicInt ^ ReverseMatch(one, matchArr);
	magicInt = magicInt << 6;
	magicInt = magicInt ^ ReverseMatch(two, matchArr);
	magicInt = magicInt << 6;
	magicInt = magicInt ^ ReverseMatch(three, matchArr);
	magicInt = magicInt << 6;
	magicInt = magicInt ^ ReverseMatch(four, matchArr);
	finalArr[0] = magicInt & patchInt;
	magicInt = magicInt >> 8;
	finalArr[1] = magicInt & patchInt;
	magicInt = magicInt >> 8;
	finalArr[2] = magicInt & patchInt;
	magicInt = magicInt >> 8;
	return finalArr;
}
char FindTheMatch(int inInt, struct baseMatcher* matchArr)
{
	for(int i=0; i<64; i++)
	{
		if(matchArr[i].matchInt == inInt)
		{
			return matchArr[i].matchChar; //Trapdoors and loltastic logic
		}
	}
	return 0; //yeeeaaaah problems
}
int ReverseMatch(char matchChar, struct baseMatcher* matchArr)
{
	for(int i = 0; i < 64; i++)
	{
		if(matchArr[i].matchChar == matchChar)
		{
			return matchArr[i].matchInt;
		}
	}
	return 0;
}