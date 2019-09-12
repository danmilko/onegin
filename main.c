#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>

typedef struct
{
    char* begin;
    char* end;
} String;

const int countTests = 3;

int FGetAll(char* str, int cnt, FILE* rf);
int CountN(char* str, int cnt);
long GetSizeOfFile(char* name);
int FillBuffer(char* text, long sizeOfText, char* name);
void GetIndexes(String* index, char* text, int countText, int countStr);
void GetStringByAdresses(char* adress1, char* s);
void Swap(String* adress1, String* adress2);
void BubbleSortText(String* index, int textSize, int (*cmp)(char*, char*, char*, char*));
void OutputText(String* index, int countStrings, char* name);
int StrCmpFront(char* str1Begin, char* str2Begin, char* str1End, char* str2End);
int StrCmpBack(char* str1Begin, char* str2Begin, char* str1End, char* str2End);
void StdUse();

int main()
{
    /**
        @brief That's the main function that coordinates other functions
    */
    StdUse();
	return 0;
}

int FGetAll(char* str, int cnt, FILE* rf)
{
    /**
        @brief That's the function that reads all the text from a file and writes it in a char array.

        @param str the pointer on a char array.
        @param cnt size of the text that you need to read.
        @param rf pointer on a file stream. It should have "r" mode.
    */
	assert(str);
	assert(rf);

	for (int i = 0; i < cnt - 1; i++)
	{
		fscanf(rf, "%c", str + i);
	}
	*(str + cnt) = '\0';
	return 1;
}
int CountN(char* str, int cnt)
{
    /**
        @brief This function counts the number of the strings in a char array.

        @param str the pointer on a char array.
        @param cnt the size of the array.
    */
	assert(str);

	int countN = 0;
	for (char* ptr = str; ptr - str < cnt - 1; ptr++)
	{
		if (*ptr == '\n')
		{
			countN++;
		}
	}
	return countN + 1;
}
long GetSizeOfFile(char* name)
{
    /**
        @brief This function opens the file and returns the size of its text.

        @param name the name of the file that you want to read from
    */
	assert(name);

	FILE* f = fopen(name, "r");
	if (f == NULL)
	{
		printf("Can't open the file. Maybe you've typed an incorrect name?\n");
		return -2;
	}

	if (fseek(f, 0, 2) == 0)
	{
		long t = ftell(f);
		fclose(f);
		return t;
	}
	fclose(f);
	return -2;
}
int FillBuffer(char* text, long sizeOfText, char* name)
{
    /**
        @brief This function opens a file and calls FGetAll() to read it.

        @param text the pointer on a char array.
        @param sizeOfText size of the char array.
        @param name the name of the file (wow).
    */
	FILE* f = fopen(name, "r");
	if (f == NULL)
	{
		printf("Can't open the file. Maybe you've typed an incorrect name?\n");
		return -1;
	}
	FGetAll(text, (int)sizeOfText, f);
	fclose(f);
	return 0;
}
void GetIndexes(String* index, char* text, int countText, int countStr)
{
    /**
        @brief This function reads the text array and
        writes the adresses of the beggining
        of every string to the special array.

        @param index the pointer on a pointer array.
        @param text the pointer on a char array.
        @param countText size of the char array that you want to have read.
    */
	index[0].begin = text;
	int j = 0;
	for (int i = 0; i < countText; i++)
	{
		if (*(text + i) == '\n')
		{
			j++;
			index[j - 1].end = (text + i);
			index[j].begin = (text + i + 1);
		}
	}
	if (index[j].begin < &text[countText - 1])
	{
        index[j].end = &text[countText - 1];
	}
	else
	{
        index[j].end = index[j].begin;
	}
}
void GetStringByAdresses(char* adress1, char* s)
{
    /**
        @brief This function reads the string by a pointer

        @param adress1 the pointer on the begging of the string.
        @param s a pointer on a string to write in.
    */
    for (int i = 0; *(adress1 + i) != '\n'; i++)
    {
        s[i] = *(adress1 + i);
        if (*(adress1 + i) == '\n')
        {
            break;
        }
    }
    //printf("%s", s);
}
void Swap(String* adress1, String* adress2)
{
    /**
        @brief Changes the adresses between two pointers.

        @param adress1 the first pointer.
        @param adress2 the second pointer.
    */
    assert(adress1);
    assert(adress2);
    String temp = *adress1;
    *adress1 = *adress2;
    *adress2 = temp;
}
void BubbleSortText(String* index, int textSize, int (*cmp)(char*, char*, char*, char*))
{
    /**
        @brief This sorts an array by the bubble sorting (not effective).

        @param index the pointer on a pointer array.
        @param textSize count of the strings (and count of the pointers in the array).
    */
    assert(index);
    for (int i = 0; i < textSize - 1; i++)
    {
        for (int j = 0; j < textSize - 1; j++)
        {
            if (cmp(index[j].begin, index[j + 1].begin, index[j].end, index[j + 1].end) == 1)
            {
                Swap(&index[j], &index[j + 1]);
            }
        }
    }
}
void OutputText(String* index, int countStrings, char* name)
{
    /**
        @brief This function writes the sorted (or not, if you want to use it somewhere else :-) ) text in a file.

        @param index the pointer on a pointer array.
        @param countStrings size of the char array that you want to have read.
        @param name thw name of an output file (wow).
    */
    FILE* wf = fopen(name, "w");
	for (int i = 0; i < countStrings; i++)
	{
		for (int j = 0; index[i].begin + j <= index[i].end; j++)
		{
            if (index[i].begin == index[i].end)
            {
                continue;
            }
            fprintf(stdout, "%c", *(index[i].begin + j));
		}
	}
	fclose(wf);
}
int StrCmpFront(char* str1Begin, char* str2Begin, char* str1End, char* str2End)
{
    for (int k = 0; *(str1Begin + k) != '\n' || *(str2Begin + k) != '\n'; k++)
    {
        if (*(str1Begin + k) == *(str2Begin + k))
        {
            continue;
        }
        if (*(str1Begin + k) > *(str2Begin + k))
        {
            return 1;
        }
        if (*(str1Begin + k) < *(str2Begin + k))
        {
            return -1;
        }
    }
    return 0;
}
int isCorrectSymbol(char c)
{
    if ((c < 'a' || c > 'z') &&
        (c < 'A' || c > 'Z') &&
        (c < '0' || c > '9'))
    {
        return 0;
    }
    return 1;
}
int StrCmpBack(char* str1Begin, char* str2Begin, char* str1End, char* str2End)
{
    assert(str1Begin);
    assert(str2Begin);
    assert(str1End);
    assert(str2End);
    if (str1Begin >= str1End)
    {
        return 1;
    }
    if (str2Begin >= str2End)
    {
        return -1;
    }
    int step1 = 0;
    int step2 = 0;
    while (*(str1End - step1) == *(str2End - step2))
    {
        step1++;
        step2++;
        while (isCorrectSymbol(*(str1End - step1)) == 0 || (str1End - step1) <= str1Begin)
        {
            step1++;
        }
        while (isCorrectSymbol(*(str2End - step2)) == 0 || (str2End - step2) <= str2Begin)
        {
            step2++;
        }

    }
    if (*(str1End - step1) > *(str2End - step2))
    {
        return 1;
    }
    if (*(str1End - step1) < *(str2End - step2))
    {
        return -1;
    }
    return 0;
}

void StdUse()
{
    printf("Программа сортирует строки стиха (и просто строки) по алфавиту.\nВведите имя файла (с расширением, например name.txt) со стихом. Ограничение 50 символов: ");
	char nameOfFile[50];
	scanf("%s", nameOfFile);
	long sizeOfBuffer = GetSizeOfFile(nameOfFile) + 1;

	if (sizeOfBuffer < 0)
	{
		printf("Something went wrong. Check the file and reload the program\n");
	}

	char* buffer;
	buffer = (char*)calloc(sizeOfBuffer + 1, 1);
	FillBuffer(buffer, sizeOfBuffer, nameOfFile);
	//buffer[sizeOfBuffer] = '\n';

	int countStrings = CountN(buffer, sizeOfBuffer);
	String* index = (String*)calloc(countStrings, sizeof(String*));
	GetIndexes(index, buffer, sizeOfBuffer, countStrings);
	BubbleSortText(index, countStrings, StrCmpBack);
	printf("Введите имя файла для записи полученного стиха. Ограничение 50 символов: ");
    scanf("%s", nameOfFile);
	OutputText(index, countStrings, nameOfFile);

    free(index);
    free(buffer);
}

void TestUse()
{
    FILE* trf;
    char* in[] = { "test1.in", "test2.in", "test3.in" };
    char* out[] = { "test1.out", "test2.out", "test3.out" };
    for (int i = 0; i < countTests; i++)
    {
    }
}
