#include "utilities.h"
#include <stdio.h>

// Returns the minimum of 2 ints... That's all... 
int min_2_int(int a, int b)
{
if(a <= b) return a;
return b;
}

int char_to_int(char letter)
{
    int ascii = (int)letter;

    if(ascii == 0)
    {
        return 0;
    }

    if (64<ascii && ascii<91)
    {
        return ascii-64;
    }

    if (96<ascii && ascii<123)
    {
        return ascii-96;
    }

    return -1;
}