struct baseMatcher{
	char matchChar;
	int matchInt;
};

struct baseMatcher* GenerateMatchingArray();

char* ConvertByteStr(char* instr, struct baseMatcher* matchArr);
char* ConvertCodeStr(char* instr);
char* EncodeStr(char one, char two, char three, struct baseMatcher* matchArr);
char* DecodeStr(char one, char two, char three, char four, struct baseMatcher* matchArr);
char FindTheMatch(int inInt, struct baseMatcher* matchArr);
int ReverseMatch(char matchChar, struct baseMatcher* matchArr);