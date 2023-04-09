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

void user_words_writing(char* FILE_NAME, char* word)
{
    FILE *file = fopen(FILE_NAME, "a");

    if (file == NULL) {
        printf("Issues with the memory file\n");
        return;
    }
    
    fprintf(file, "\n");
    fprintf(file, "%s", word);

    fclose(file);
}