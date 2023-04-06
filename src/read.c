#include "read.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int read_print(char *FILE_NAME)
{
  FILE *file;
  int i = 0;
  char storage[30];

  file = fopen(FILE_NAME, "r");

  while ((fscanf(file, "%s", storage)) == 1)
    i++;

  fclose(file);

  return i;
}