#include <stdio.h>
#include "read.h"

void main()
{
    char FILE_NAME[30] = "data/liste_francais.txt";

    printf("%d\n", read_print(FILE_NAME));
}