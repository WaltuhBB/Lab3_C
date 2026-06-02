#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//Основные фунции

//Конвертация строки в булев вектор
unsigned char* StrToVec(char* str, size_t* cells)
{
    if (str && cells)
    {
        size_t bits = strlen(str);
        *cells = ((bits - 1) / 8) + 1;
    }
}

int main()
{
    
    
    return 0;
}