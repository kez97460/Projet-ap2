#include "utilities.h"
#include <stdio.h>

// Returns the minimum of 2 ints... That's all...
int max_2_int(int a, int b)
{
    if (a > b)
        return a;
    return b;
}

int char_to_int(char letter)
{
    int ascii = (int)letter;

    if (ascii == 0)
    {
        return 0;
    }

    if (64 < ascii && ascii < 91)
    {
        return ascii - 64;
    }

    if (96 < ascii && ascii < 123)
    {
        return ascii - 96;
    }

    return -1;
}

/* String arrays */

// used by
char **create_string_array(int nb_words)
{
    char **words = malloc(nb_words * sizeof(char *));
    for (int i = 0; i < nb_words; i++)
    {
        words[i] = malloc(MAX_WORD_LENGTH * sizeof(char));
    }
    return words;
}

word_array create_empty_word_array(int nb_words)
{
    word_array array;
    array.words = create_string_array(nb_words);
    array.length = nb_words;
    return array;
}
