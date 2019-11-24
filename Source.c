#include "Header.h"


int Identificator(char* string);
int TypeSeek(char* p);

int main()
{
	setlocale(LC_ALL, "RUS");
	int identCount = 0; // счётчик идентификаторов
	int i = 0;
	char buf[256]; // буфер для чтения

	FILE* in;

	in = fopen("Testcode.c", "rt");

	if (in == NULL)
	{
		printf("File isn't found");
		
		return 0;
	}
	
	while (fgets(buf, 256, in) != NULL) 
	{
		identCount += Identificator(buf); // добавление идентификаторов из текущей строки
		
		for (i = 0; i < 256; ++i) // очистка буфера
			buf[i] = '\0';
		
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
	char j = 0;
	int i = 0;
	int s = 0;
	int identCount = 0;
	while (inputString[i] != '\0' && inputString[i] != '\n') // пока не конец строки
	{
		while (!isspace(inputString[i]) && inputString[i] != '\0' && !ispunct(inputString[i])) // внести в промежуточную строку все буквы и цифры посимвольно
		{
			p[s] = inputString[i];
			s++;
			i++;
		}
		if (inputString[i] == '/' && inputString[i + 1] == '/') // если мы внутри комментария
			break;
		if (TypeSeek(p)) // если найден указатель типа 
		{
			typeFlag = 1; 
		}
		else
		{
			for (int j = 0; j < s; j++)
				if (typeFlag && (isalpha(p[j]) || p[j] == '_')) // если указатель типа найден и после него нижнее подчерк. или буква
					f = 1; 
				else f = 0;
		}
		if (f && typeFlag)
		{
			identCount++;
			printf("%s\n", p);
			if (inputString[i] == '(')   // мы внутри скобок, где идентификаторов не может быть
			{
				i++;
				while (inputString[i] != ')')
					i++;
			}
		}
		if (inputString[i] == ';')
			typeFlag = 0;
		for (int j = 0; j < 32; j++) // очистка 
			p[j] = '\0';
		s = 0;
		i++;
		f = 0;
	}
	return identCount;
}

int TypeSeek(char* p) // находим тип данных(характерный признак идентификатора)
{
	if (strcmp(p, "long") == 0) return 1;
	else if (strcmp(p, "void") == 0) return 1;
	else if (strcmp(p, "int") == 0) return 1;
	else if (strcmp(p, "short") == 0) return 1;
	else if (strcmp(p, "double") == 0) return 1;
	else if (strcmp(p, "char") == 0) return 1;
	else if (strcmp(p, "FILE") == 0) return 1;
	else if (strcmp(p, "const") == 0) return 1;
	else if (strcmp(p, "struct") == 0) return 1;
	else if (strcmp(p, "float") == 0) return 1;
	else return 0;
}