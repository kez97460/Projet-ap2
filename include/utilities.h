#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NB_CHARS 27 // 27 possibilities for a letter : [a-z] or \0
#define MAX_WORD_LENGTH 32 // max length of a word

typedef struct _word_array{
    char** words;
    int length;
} word_array;

int max_2_int(int a, int b);
int min_2_int(int a, int b);
/* Transform chars to indexes for the prefix_tree*/
int char_to_int(char letter);
char int_to_char(int n);
/* String and word_array manipulation */
word_array create_empty_word_array(int nb_words);
void add_char(char* str, char c);
char delete_last_char(char *str) ;

#endif