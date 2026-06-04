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