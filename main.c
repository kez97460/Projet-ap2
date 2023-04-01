#include <stdio.h>
#include <string.h>
#include "read.h"

void main()
{
    char FILE_NAME[30] = "data/liste_francais.txt";
    
    for(int i = 0; i <= strlen(FILE_NAME); i++)
    {
        printf("%d ", char_to_int(FILE_NAME[i]));
    }
    printf("\n");
}