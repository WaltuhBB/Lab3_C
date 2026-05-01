#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

int main()
{
    
    unsigned char str[32] = "asv00itrgnnfnbfls;e000043994098\0";
    
    size_t cells;
    unsigned char *vec = StrToVec(str, &cells);

    if (vec != NULL)
    {
        for (size_t i = 0; i < cells; i++)
        {
            printf("%X ", vec[i]);
        }
    }
    else
    {
        printf("Memory was never allocated ");
    }

    return 0;

}
