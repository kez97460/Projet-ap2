#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 32

typedef struct _word_array{
    char** words;
    int length;
} word_array;

int max_2_int(int a, int b);
int char_to_int(char letter);
word_array create_empty_word_array(int nb_words);

#endif