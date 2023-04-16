#ifndef PREFIX_TREES_H
#define PREFIX_TREES_H

#include "utilities.h"

typedef struct _tree_node
{
    int nb_occ; // max number of occurences out of the words containing this letter
    struct _tree_node* children[NB_CHARS]; // array of children, size of 27. 
    // children[i] corresponds to the i-th letter of the alphabet. children[0] corresponds to '\0'
}tree_node;

typedef tree_node* prefix_tree;

/* Constructing tree */
prefix_tree create_node();
void update_word(prefix_tree root, char* word, int new_number);
int add_word(prefix_tree root, char* word);
void add_and_update_word(prefix_tree root, char* word);
/* Reading from tree */
char* get_most_common_word(prefix_tree root);
int delete_word(prefix_tree root, char* word);
word_array get_most_common_words(prefix_tree root, int nb_words);

// for testing, to be removed
int index_most_common_children(prefix_tree node);
int read_word(prefix_tree* root_pointer, char* word);


#endif