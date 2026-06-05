#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//Основные фунции

//Конвертация строки в булев вектор
unsigned char* StrToVec(char* str, size_t* cells)
{
    unsigned char *vec = NULL;
    
    if (str && cells && strlen(str))
    {
        size_t bits = strlen(str);        
        *cells = ((bits - 1) / 8) + 1;

        vec = (unsigned char*)calloc(*cells, sizeof(unsigned char));

        if (vec)
        {
            size_t k = 0;

            for (size_t i = 0; i < *cells; i++)
            {
                for (size_t j = 0; j < 8 && k < bits; j++)
                {
                    if (str[k] != '0')
                    {
                        vec[i] |= (1 << (7 - j));
                    }

                    k++;
                }
            }
        }
    }

    return vec;
}

//Конвертация вектора в строку
char* VecToStr(unsigned char* vec, size_t cells)
{
    char* str = NULL;

    if (vec && cells > 0)
    {
        size_t bits = 8 * cells;
        str = (char*)calloc(bits + 1, sizeof(char));

        if (str)
        {
            unsigned char mask;
            size_t k = 0;

            for (size_t i = 0; i < cells; i++)
            {
                mask = 1;
                mask = mask << 7;

                for (size_t j = 0; (j < 8) && (k < bits); j++)
                {
                    if (vec[i] & mask)
                    {
                        str[k] = '1';
                    }
                    else
                    {
                        str[k] = '0';
                    }
                    
                    k++;
                    mask = mask >> 1;
                }
            }
        }
    }

    return str;
}

//Вывод вектора в консоль
bool printVec(unsigned char* vec, size_t bits)
{
    bool res = false;

    if (vec && bits)
    {
        size_t cells = ((bits - 1) / 8) + 1;

        unsigned char mask;
        size_t k = 0;
        
        for (size_t i = 0; i < cells; i++)
        {
            mask = 1 << 7;

            for (size_t j = 0; (j < 8) && (k < bits); j++)
            {
                if (vec[i] & mask)
                {
                    printf("1");
                }
                else
                {
                    printf("0");
                }

                mask = mask >> 1;
                k++;
            }

            printf(" ");
        }
        
        printf("\n");
        res = true;
    }

    return res;
}

//Операции с булевыми векторами

//Установка k-го разряда
void set1(unsigned char* vec, size_t bits, size_t k)
{
    if (vec && bits && k < bits)
    {
        size_t cell = k / 8;
        size_t bit = k % 8;

        unsigned char mask = 1 << 7;
        mask = mask >> bit;

        vec[cell] = vec[cell] | mask;
    }
}

//Сброс k-го разряда
void set0(unsigned char* vec, size_t bits, size_t k)
{
    if (vec && bits && k < bits)
    {
        size_t cell = k / 8;
        size_t bit = k % 8;

        unsigned char mask = 1 << 7;
        mask = mask >> bit;
        mask = ~mask;

        vec[cell] = vec[cell] & mask;
    }
}

int main()
{
    char str_1[32] = "asv00itrgnnfnbfls;e000043994098\0";
    char str_2[17] = "1101001100011100\0";
    char str_3[2] = "0\0";
    
    size_t cells;

    char *str_new = NULL;

    unsigned char *vec_1 = StrToVec(str_1, &cells);
    printVec(vec_1, 31);
    set1(vec_1, 31, 28);
    printVec(vec_1 , 31);

    printf("\n");

    unsigned char *vec_2 = StrToVec(str_2, &cells);
    printVec(vec_2, 16);
    set0(vec_2, 16, 1);
    printVec(vec_2 , 16);

    printf("\n");

    unsigned char *vec_3 = StrToVec(str_3, &cells);
    printVec(vec_3, 1);
    set1(vec_3, 1, 0);
    printVec(vec_3 , 1);

    free(vec_1);
    free(vec_2);
    free(vec_3);
    vec_1 = NULL;
    vec_2 = NULL;
    vec_3 = NULL;
    
    return 0;
}