#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "basesixtyfour.h"
#include "hexConverter.h"

//Everything is Awesome~~~
//Everything is Coool when you're part of a Team~~~
//Everything is Awesome~~~
//When we're living our Dreeeeaaams~~~~~

//But only in this file.

//Matasano's CryptoPals
//Intro Program Thing
//By Lady Redezra


int main(int argc, char** argv)
{
	//I'ma assume that the first arg was your string
	int i;
	if (argc != 2)
	{
		printf("ERROR: NEED ONE STRINGS \n");
		exit(EXIT_FAILURE);
	}
	char* strOne = argv[1];
	//char* strTwo = argv[2];

	unsigned char* newStr = HexToBytes(strOne);
	/*
	for(i = 0; i < strlen(newStr); i++)
	{
		printf("%d ",(int)newStr[i]);
	}
	printf("\n");
	*/
	struct baseMatcher* baseMatcher;
	baseMatcher = GenerateMatchingArray();
	/*
	for(i=0;i<64;i++)
	{
		printf("%c, %d\n",baseMatcher[i].matchChar,baseMatcher[i].matchInt);
	}
	*/

	char* magicReturnArray = ConvertByteStr(newStr, baseMatcher);

	printf("%s\n",magicReturnArray);

	free(baseMatcher);
	free(newStr);
	return 0;
}
