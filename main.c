#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//Перевод строки в вектор
unsigned char* StrToVec(char* str, size_t* cells)
{
    unsigned char *res = NULL;
    
    if (str != NULL && cells != NULL && strlen(str))
    {
        size_t len = strlen(str);
        *cells = ((len-1) / 8) + 1;
        size_t k = 0;
        unsigned char mask = 1;

        unsigned char *vec = (unsigned char*)calloc(*cells, sizeof(unsigned char));
        
        if (vec != NULL)
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

    if (vec != NULL && cells > 0)
    {
        size_t len = (cells * 8) + 1;
        str = (char*)calloc(len, sizeof(char));
        
        if (str != NULL)
        {
            unsigned char mask = 1;
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
bool printVec(unsigned char* vec, size_t cells)
{
    bool res = false;

    if (vec != NULL && cells > 0)
    {
        char *str = VecToStr(vec, cells);

        if (str != NULL)
        {
            for (size_t i = 0; i < (cells * 8) + 1; i++)
            {
                printf("%c", str[i]);
            }
            
            free(str);
            res = true;
        }
    }

    return res;
}

int main()
{
    
    unsigned char str[32] = "asv00itrgnnfnbfls;e000043994098\0";
    printf("%s\n", str);
    
    size_t cells;
    unsigned char *vec = StrToVec(str, &cells);

    if (vec != NULL)
    {
        for (size_t i = 0; i < cells; i++)
        {
            printf("%X ", vec[i]);
        }

        printf("len: %d\n", cells);
    }
    else
    {
        printf("Memory was never allocated ");
    }

    bool flagN = printVec(vec, cells);
    if (!flagN)
    {
        printf("Memory was never allocated ");
    }

    free(vec);

    return 0;

}
