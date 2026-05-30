#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

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
bool printVec(unsigned char* vec, size_t len, size_t cells)
{
    bool res = false;

    if (vec && len && cells)
    {
        size_t len_c = len;
        
        if (len > (cells * 8))
        {
            len_c = cells * 8;
        }
        
        unsigned char mask_tail = 255 >> ((8 * cells) - len_c);

        size_t k = 0;
        unsigned char mask;

        for (size_t i = 0; i < cells; i++)
        {
            mask = 1 << 7;

            for (size_t j = 0; (j < 8) && (k < len_c); j++)
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

int main()
{
    //Тесты 1

    //11100111 11111111 11100001 01111011
    unsigned char str[32] = "asv00itrgnnfnbfls;e000043994098\0";

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

    bool check = printVec(vec, len, cells);
    if (!check)
    {
        printf("an error occured\n");
    }

    free(vec);
    vec = NULL;

    printf("\n");

    return 0;
}
