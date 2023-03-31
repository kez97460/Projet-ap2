#ifndef PREFIX_TREES_H
#define PREFIX_TREES_H

#define NB_CHARS 27 // 27 possibilities for a letter : [a-z] or \0

typedef struct _tree_node
{
    int nb_occ; // max number of occurences out of the words containing this letter
    struct _tree_node* children[NB_CHARS]; // array of children, size of 27. 
    // children[i] corresponds to the i-th letter of the alphabet. children[0] corresponds to '\0'
}tree_node;

typedef tree_node* prefix_tree;


#endif