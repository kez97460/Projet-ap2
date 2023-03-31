#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prefix_trees.h"
#include "utilities.h"

prefix_tree create_node()
{
prefix_tree tree = (prefix_tree) malloc(sizeof(tree_node));
tree->nb_occ = 0;
for (int i = 0; i < NB_CHARS; i++) 
{
    tree->children[i] = NULL;    
}
}

// updates the nb_occ for all letters in a word. Input new_number < 0 to automatically fetch it in the tree.
void update_word(prefix_tree root, char* word, int new_number)
{
prefix_tree node = root; // used to go through the tree
int length = strlen(word);
int index;

if(new_number<0)
{
    for(int i = 0; i < length; i++)
    {
        index = /*get_char(letter)*/(int) word[i] - 'a';
        if(node->children[index] == NULL)
        {
            printf("ERROR : word does not exist, could not update");
            return;
        }
        node = node->children[index];
    }
    new_number = node->nb_occ; // set new_number to the correct amount
}

node = root; // reset tree
for(int i = 0; i < length; i++)
{
    index = /*get_char(letter)*/(int) word[i] - 'a';
    if(node->children[index] == NULL)
    {
        printf("ERROR : word does not exist, could not update");
        return;
    }
    node->nb_occ = min_2_int(node->nb_occ, new_number); // update each letter
    node = node->children[index];
}
}

// adds the word and returns its nb_occ (the one of the end of the string)
int add_word(prefix_tree root, char* word)
{
prefix_tree node = root; // used to go through the tree
int length = strlen(word);
int index;
for(int i = 0; i < length; i++)
{
    index = /*get_char(letter)*/(int) word[i] - 'a';
    
    if(node->children[index] == NULL)
    {
        node->children[index] = create_node(); // create a node for the new letter
    }
    node = node->children[index];
}
node->nb_occ++; // add an occurence to the word (will update later to propagate to previous letters)
}

void add_and_update_word(prefix_tree root, char* word)
{
int new_number = add_word(root, word);
update_word(root, word, new_number); // use new_number to avoid a useless traversal of the tree.
// This optimisation is extremely useless, as it avoids an operation in O(size of word). But I like it.
}

