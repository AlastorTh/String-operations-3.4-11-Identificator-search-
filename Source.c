#include "Header.h"


int Identificator(char* string);
int TypeSeek(char* p);

int main()
{
	setlocale(LC_ALL, "RUS");
	int identCount = 0; 
	int i = 0;
	char buf[256]; 
	FILE* in;

	in = fopen("Testcode.c", "rt");

	if (in == NULL)
	{
		printf("File isn't found");
		
		return 0;
	}
	
	while (fgets(buf, 256, in) != NULL) 
	{
		identCount += Identificator(buf); 
		
		for (i = 0; i < 256; ++i) buf[i] = '\0';
		
	}
	printf("\n\nКол-во идентификаторов в программе: %d", identCount);
	fclose(in);
	return 0;
}


int Identificator(char* inputString)
{
	char p[32] = { '\0' };
	char f = 0;
	char typeFlag = 0;
	int i = 0;
	int s = 0;
	int identCount = 0;
	while (inputString[i] != '\0' && inputString[i] != '\n') // пока не конец строки
	{
		while (!isspace(inputString[i]) && inputString[i] != '\0' && !ispunct(inputString[i])) 
		{
			p[s] = inputString[i];
			s++;
			i++;
		}
		if (inputString[i] == '/' && inputString[i + 1] == '/') 
			break;
		if (TypeSeek(p)) 
		{
			typeFlag = 1; 
		}
		else
		{
			for (int j = 0; j < s; j++)
				if (typeFlag && (isalpha(p[j]) || p[j] == '_')) 
					f = 1; 
				else f = 0;
		}
		if (f && typeFlag)
		{
			identCount++;
			printf("%s\n", p);
			if (inputString[i] == '(')   
			{
				i++;
				while (inputString[i] != ')')
					i++;
			}
		}
		if (inputString[i] == ';')
			typeFlag = 0;
		for (int j = 0; j < 32; j++) p[j] = '\0';
		s = 0;
		i++;
		f = 0;
	}
	return identCount;
}

int TypeSeek(char* p) 
{
	if (strcmp(p, "long") == 0) return 1;
	if (strcmp(p, "void") == 0) return 1;
    if (strcmp(p, "int") == 0) return 1;
    if (strcmp(p, "short") == 0) return 1;
	if (strcmp(p, "double") == 0) return 1;
	if (strcmp(p, "char") == 0) return 1;
	if (strcmp(p, "FILE") == 0) return 1;
	if (strcmp(p, "const") == 0) return 1;
	if (strcmp(p, "struct") == 0) return 1;
	if (strcmp(p, "float") == 0) return 1;
	else return 0;
}