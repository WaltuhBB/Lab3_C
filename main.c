#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//Часть 1

//Перевод строки в вектор
unsigned char* StrToVec(char* str, size_t* cells)
{
    unsigned char *res = NULL;
    
    if (str && cells && strlen(str))
    {
        size_t len = strlen(str);
        *cells = ((len-1) / 8) + 1;
        size_t k = 0;
        unsigned char mask = 1;

        unsigned char *vec = (unsigned char*)calloc(*cells, sizeof(unsigned char));
        
        if (vec)
        {
            for (size_t i = 0; i < *cells; i++)
            {
                for (int j = 0; (j < 8) && (k < len); j++)
                {
                    vec[i] = vec[i] << 1;
                    
                    if (str[k] != '0')
                    {
                        vec[i] = vec[i] | mask;
                    }

                    k++;
                }
            }
        }
        
        res = vec;
    }

    return res;
}

//Перевод вектора в строку
char* VecToStr(unsigned char* vec, size_t cells)
{
    char *str = NULL;

    if (vec && cells > 0)
    {
        size_t len = (cells * 8) + 1;
        str = (char*)calloc(len, sizeof(char));
        
        if (str)
        {
            unsigned char mask;
            size_t k = 0;

            for (size_t i = 0; i < cells; i++)
            {
                mask = 1;
                mask = mask << 7;

                for (int j = 0; (j < 8) && (k < len); j++)
                {
                    if ((vec[i] & mask) != 0)
                    {
                        str[k] = '1';
                    }
                    else
                    {
                        str[k] = '0';
                    }

                    mask = mask >> 1;
                    k++;
                }
            }

            str[k] = '\0';
        }
    }

    return str;
}

//Вывод вектора в консоль
bool printVec(unsigned char* vec, size_t len)
{
    bool res = false;

    if (vec && len)
    {    
        size_t cells = ((len-1) / 8) + 1;
        
        unsigned char mask_tail = 255 >> ((8 * cells) - len);

        size_t k = 0;
        unsigned char mask;

        for (size_t i = 0; i < cells; i++)
        {
            mask = 1 << 7;

            for (size_t j = 0; (j < 8) && (k < len); j++)
            {
                if (i != cells - 1)
                {
                    if (mask & vec[i])
                    {
                        printf("1");
                    }
                    else
                    {
                        printf("0");
                    }

                    k++;
                }
                else
                {
                    if (mask & mask_tail)
                    {
                        if (mask & vec[i])
                        {
                            printf("1");
                        }
                        else
                        {
                            printf("0");
                        }

                        k++;
                    }
                }

                mask = mask >> 1;
            }
        }

        res = true;
    }

    return res;
}

//Часть 2

//Логическое умножение
unsigned char* logMul(unsigned char* vec_A, size_t bits_A, unsigned char* vec_B, size_t bits_B)
{
    unsigned char *res = NULL;

    if (vec_A && vec_B && bits_A && bits_B && (bits_A == bits_B))
    {
        size_t cells = ((bits_A - 1) / 8) + 1;
        res = (unsigned char*)calloc(cells, sizeof(unsigned char));

        if (res)
        {
            for (size_t i = 0; i < cells; i++)
            {
                res[i] = vec_A[i] & vec_B[i];
            }
        }
    }

    return res;
}

int main()
{
//Тесты 1

    //11100111 11111111 11100001 01111011
    unsigned char str[32] = "asv00itrgnnfnbfls;e000043994098\0";

    //00000111 11111111 11100001 01111011
    //unsigned char str[32] = "00000itrgnnfnbfls;e000043994098\0";

    //010001
    //unsigned char str[7] = "0b000c\0";

    //11111111 11111111
    //unsigned char str[17] = "1234567812345678\0";

    //unsigned char str[1] = "\0";

    printf("%s\n", str);

    size_t cells = 1;
    size_t len = strlen(str);
    unsigned char *vec = StrToVec(str, &cells);

    if (vec)
    {
        unsigned char* new_str = VecToStr(vec, cells);
        printf("%s\n", new_str);
        
        free(new_str);
        new_str = NULL;
    }

    bool check = printVec(vec, len);
    if (!check)
    {
        printf("an error occured\n");
    }

    free(vec);
    vec = NULL;

    printf("\n\n");

//Тесты 2

//Умножение

    printf("logMul tests:\n\n");

    size_t cells_1;
    size_t cells_2;

    unsigned char *vec_1 = StrToVec("0111011\0", &cells_1);
    unsigned char *vec_2 = StrToVec("01001\0", &cells_2);

    if (vec_1 && vec_2)
    {
        unsigned char *vec_res = logMul(vec_1, 7, vec_2, 5);

        printVec(vec_1, 7);
        printf("\n");
        printVec(vec_2, 5);
        printf("\n");

        check = printVec(vec_res, 7);
        if (!check)
        {
            printf("an error occured");
        }

        free(vec_res);
        vec_res = NULL;
    }
    else
    {
        printf("memory was never allocated\n");
    }

    free(vec_1);
    vec_1 = NULL;
    free(vec_2);
    vec_2 = NULL;

    printf("\n\n");

    vec_1 = StrToVec("110110101110000\0", &cells_1);
    vec_2 = StrToVec("101110001110110\0", &cells_2);

    if (vec_1 && vec_2)
    {
        unsigned char *vec_res = logMul(vec_1, 15, vec_2, 15);

        printVec(vec_1, 15);
        printf("\n");
        printVec(vec_2, 15);
        printf("\n");

        check = printVec(vec_res, 15);
        if (!check)
        {
            printf("an error occured");
        }

        free(vec_res);
        vec_res = NULL;
    }
    else
    {
        printf("memory was never allocated\n");
    }

    free(vec_1);
    vec_1 = NULL;
    free(vec_2);
    vec_2 = NULL;

    return 0;
}
