#ifndef READ_H
#define READ_H


#include "prefix_trees.h"

prefix_tree read_prefix_tree(char *filename);
void write_prefix_tree(prefix_tree tree, char *filename);
void user_words_writing(char* FILE_NAME, char* word);

#endif