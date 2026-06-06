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

//Сдвиг влево на k разрядов
void shiftLeft(unsigned char* vec, size_t bits, size_t k)
{
    if (vec && bits && k)
    {
        size_t cells = ((bits - 1) / 8) + 1;

        if (k >= bits)
        {
            for (size_t i = 0; i < cells; i++)
            {
                vec[i] = 0;
            }
        }
        else
        {
            size_t cells = ((bits - 1) / 8) + 1;
            size_t byte_shift = k / 8;
            size_t bit_shift = k % 8;

            if (!bit_shift)
            {
                for (size_t i = 0; i < cells - byte_shift; i++)
                {
                    vec[i] = vec[i+byte_shift];
                }
            }
            else
            {
                size_t i;
                
                for (i = 0; i < cells - byte_shift - 1; i++)
                {
                    size_t src = i + byte_shift;
                    size_t src_next = src + 1;

                    unsigned char part_1 = vec[src] << bit_shift;
                    unsigned char part_2 = vec[src_next] >> (8 - bit_shift);

                    vec[i] = part_1 | part_2;
                }

                size_t src = i + byte_shift;
                vec[i] = vec[src] << bit_shift;
            }

            for (size_t i = cells - byte_shift; i < cells; i++)
            {
                vec[i] = 0;
            }
        }
    }
}

//Свдиг вправо на k разрядов
void shiftRight(unsigned char* vec, size_t bits, size_t k)
{
    if (vec && bits && k)
    {
        if (k >= bits)
        {
            size_t cells = ((bits - 1) / 8) + 1;

            for (size_t i = 0; i < cells; i++)
            {
                vec[i] = 0;
            }
        }
        else
        {
            size_t cells = ((bits - 1) / 8) + 1;
            size_t byte_shift = k / 8;
            size_t bit_shift = k % 8;

            if (!bit_shift)
            {
                for (size_t i = cells - 1; i >= byte_shift; i--)
                {
                    vec[i] = vec[i-byte_shift];
                }
            }
            else
            {
                for (size_t i = cells - 1; i > byte_shift; i--)
                {
                    size_t src = i - byte_shift;
                    size_t src_prev = src - 1;

                    unsigned char part_1 = vec[src] >> bit_shift;
                    unsigned char part_2 = vec[src_prev] << (8 - bit_shift);

                    vec[i] = part_1 | part_2;
                }

                size_t src = 0;
                vec[byte_shift] = vec[src] >> bit_shift;
            }

            for (size_t i = 0; i < byte_shift; i++)
            {
                vec[i] = 0;
            }

            size_t tail_len = cells * 8 - bits;
            unsigned char tail_mask = 255 << tail_len;

            vec[cells-1] = vec[cells-1] & tail_mask;
        }
    }
}

//Логическое умножение
unsigned char* logMul(unsigned char* vecA, size_t bitsA, unsigned char* vecB, size_t bitsB)
{
    unsigned char *res = NULL;

    if (vecA && vecB && bitsA && bitsB && (bitsA == bitsB))
    {
        size_t cells = ((bitsA - 1) / 8) + 1;

        res = (unsigned char*)calloc(cells, sizeof(unsigned char));

        if (res)
        {
            for (size_t i = 0; i < cells; i++)
            {
                res[i] = vecA[i] & vecB[i];
            }
        }
    }

    return res;
}

//Логическое сложение
unsigned char* logSum(unsigned char* vecA, size_t bitsA, unsigned char* vecB, size_t bitsB)
{
    unsigned char *res = NULL;

    if (vecA && vecB && bitsA && bitsB && (bitsA == bitsB))
    {
        size_t cells = ((bitsA - 1) / 8) + 1;

        res = (unsigned char*)calloc(cells, sizeof(unsigned char));

        if (res)
        {
            for (size_t i = 0; i < cells; i++)
            {
                res[i] = vecA[i] | vecB[i];
            }
        }
    }

    return res;
}

//Сумма по модулю 2
unsigned char* sumMod2(unsigned char* vecA, size_t bitsA, unsigned char* vecB, size_t bitsB)
{
    unsigned char *res = NULL;

    if (vecA && vecB && bitsA && bitsB && (bitsA == bitsB))
    {
        size_t cells = ((bitsA - 1) / 8) + 1;

        res = (unsigned char*)calloc(cells, sizeof(unsigned char));

        if (res)
        {
            for (size_t i = 0; i < cells; i++)
            {
                res[i] = vecA[i] ^ vecB[i];
            }
        }
    }

    return res;
}

int main()
{
    char str_1[32] = "asv11itrgnnfnbfls;e111143994198\0";
    char str_2[17] = "1111111111111111\0";
    char str_3[2] = "0\0";
    
    size_t cells;

    char *str_new = NULL;

    unsigned char *vec_1 = StrToVec(str_1, &cells);
    printVec(vec_1, 31);
    shiftRight(vec_1, 31, 28);

    str_new = VecToStr(vec_1, cells);
    printf("%s\n", str_new);

    printVec(vec_1 , 31);

    printf("\n");

    unsigned char *vec_2 = StrToVec(str_2, &cells);
    printVec(vec_2, 16);
    shiftRight(vec_2, 16, 9);
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