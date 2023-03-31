#include <stdio.h>
#include "read.h"

int char_to_int(char letter)
{
    int ascii = (int)letter;

    printf("%d\n", ascii);

    if (64<ascii && ascii<91)
    {
        return (ascii-64);
    }

    if (96<ascii && ascii<123)
    {
        return ascii-96;
    }

    return -1;
}

void main()
{
    char FILE_NAME[30] = "data/liste_francais.txt";
    
    printf("%d\n", char_to_int('a'));
}