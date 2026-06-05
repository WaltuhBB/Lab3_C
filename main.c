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

int main()
{
    size_t cells;
    
    char str_1[32] = "asv00itrgnnfnbfls;e000043994098\0";
    char str_2[17] = "1101001100011100\0";
    char str_3[2] = "1\0";
    char *str_NULL = NULL;
    char str_zero[1] = "\0";

    //для str_1
    unsigned char *vec_1 = StrToVec(str_1, &cells);
    if (vec_1)
    {
        printf("%s\n", str_1);
        for (size_t i = 0; i < cells; i++)
        {
            printf("%d ", vec_1[i]);
        }
        printf("\n");

        printVec(vec_1, 31);

        unsigned char *new_str = VecToStr(vec_1, cells);

        if (new_str)
        {
            printf("%s", new_str);

            free(new_str);
            new_str = NULL;
        }
        else
        {
            printf("and error occured");
        }
    }
    else
    {
        printf("memory was never allocated ");
    }
    free(vec_1);
    vec_1 = NULL;

    printf("\n\n");

    //для str_2
    unsigned char *vec_2 = StrToVec(str_2, &cells);
    if (vec_2)
    {
        printf("%s\n", str_2);
        for (size_t i = 0; i < cells; i++)
        {
            printf("%d ", vec_2[i]);
        }
        printf("\n");

        printVec(vec_2, 16);

        unsigned char *new_str = VecToStr(vec_2, cells);

        if (new_str)
        {
            printf("%s", new_str);

            free(new_str);
            new_str = NULL;
        }
        else
        {
            printf("and error occured");
        }
    }
    else
    {
        printf("memory was never allocated ");
    }
    free(vec_2);
    vec_2 = NULL;

    printf("\n\n");

    //для str_3
    unsigned char *vec_3 = StrToVec(str_3, &cells);
    if (vec_3)
    {
        printf("%s\n", str_3);
        for (size_t i = 0; i < cells; i++)
        {
            printf("%d ", vec_3[i]);
        }
        printf("\n");

        printVec(vec_3, 1);

        unsigned char *new_str = VecToStr(vec_3, cells);

        if (new_str)
        {
            printf("%s", new_str);

            free(new_str);
            new_str = NULL;
        }
        else
        {
            printf("and error occured");
        }
    }
    else
    {
        printf("memory was never allocated ");
    }
    free(vec_3);
    vec_3 = NULL;

    printf("\n\n");

    //для str_NULL
    unsigned char *vec_NULL = StrToVec(str_NULL, &cells);
    if (vec_NULL)
    {
        printf("%s\n", str_NULL);
        for (size_t i = 0; i < cells; i++)
        {
            printf("%d ", vec_NULL[i]);
        }
    }
    else
    {
        printf("memory was never allocated ");
    }
    free(vec_NULL);
    vec_NULL = NULL;

    printf("\n\n");

    //для str_zero
    unsigned char *vec_zero = StrToVec(str_zero, &cells);
    if (vec_zero)
    {
        printf("%s\n", str_zero);
        for (size_t i = 0; i < cells; i++)
        {
            printf("%d ", vec_zero[i]);
        }
    }
    else
    {
        printf("memory was never allocated ");
    }
    free(vec_zero);
    vec_zero = NULL;
    
    return 0;
}