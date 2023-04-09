#include "utilities.h"
#include <stdio.h>

// Returns the minimum of 2 ints... That's all...
int max_2_int(int a, int b)
{
    if (a > b)
        return a;
    return b;
}

int min_2_int(int a, int b)
{
    if (a > b)
        return b;
    return a;
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

// Inverse function of char_to_int. Returns a '!' for invalid inputs
char int_to_char(int n)
{
    if (n < 1 || n > 26) 
    {
        printf("Invalid input for int_to_char. Returning a '!' \n");
        return '!'; // invalid input, return -1
    }
    return n + 96; // ASCII value of lowercase a is 97, so add 96 to the input
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

// adds a char at the end of a string
void add_char(char* str, char c) 
{
    int len = strlen(str);
    str[len] = c;
    str[len+1] = '\0';
}

char delete_last_char(char *str) 
{
    int len = strlen(str);
    char res = 0;
    if (len > 0) 
    {
        res = str[len];
        str[len - 1] = '\0'; // set the last character to null terminator
    }
    return res;
}