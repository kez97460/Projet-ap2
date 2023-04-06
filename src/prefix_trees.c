#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prefix_trees.h"
#include "utilities.h"

/* Creation of the structure */

// creates an empty 
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
    for(int i = 0; i <= length; i++)
    {
        index = char_to_int(word[i]);
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
    index = char_to_int(word[i]);
    if(node->children[index] == NULL)
    {
        printf("ERROR : word does not exist, could not update");
        return;
    }
    node->nb_occ = max_2_int(node->nb_occ, new_number); // update each letter
    node = node->children[index];
}
}

// adds the word and returns its nb_occ (the one of the end of the string)
int add_word(prefix_tree root, char* word)
{
prefix_tree node = root; // used to go through the tree
int length = strlen(word);
int index;
for(int i = 0; i <= length; i++)
{
    index = char_to_int(word[i]);
    
    if(node->children[index] == NULL)
    {
        node->children[index] = create_node(); // create a node for the new letter
    }
    node = node->children[index];
}
node->nb_occ++; // add an occurence to the word (will update later to propagate to previous letters)
return node->nb_occ;
}

void add_and_update_word(prefix_tree root, char* word)
{
int new_number = add_word(root, word);
update_word(root, word, new_number); // use new_number to avoid a useless traversal of the tree.
// This optimisation is extremely useless, as only halves the time taken by update_word, but I like it
}

/*------------*/
/* Prediction */
/*------------*/

// merge_sort + lists ? 

int get_nb_occ_children(prefix_tree node, int index)
{
if(node->children[index] == NULL)
{
    return 0;
}
return node->children[index]->nb_occ;
}


int index_most_common_children(prefix_tree node)
{
int nb_occ_child;
int res = 0;
for(int i = 0; i<NB_CHARS; i++)
{
    nb_occ_child = get_nb_occ_children(node, i);
    if(res < nb_occ_child)
    {
        res = nb_occ_child;
    }
}
return res;
}

// sets nb_occ for a word to 0, updates the tree and returns what that number was
int remove_all_occs(prefix_tree root, char* word)
{
// This function works by first modifying the nb_occ for the end of the word ('\0') to 0
// It then modifies nb_occ for every letter of the word, starting from the end 
// The complexity is really bad O(n^2) , but this doesn't matter as the function is executed on words of small size, 
// and only 2 times on each user input
prefix_tree node = root; // used to go through the tree
int length = strlen(word);
int index;
for(int i = 0; i <= length; i++)
{
    index = char_to_int(word[i]);
    if(node->children[index] == NULL)
    {
        printf("ERROR : word does not exist, could not update");
        return -1;
    }
    node = node->children[index];
}
int res = node->nb_occ; // save the old nb_occ of the word to return it
node->nb_occ = 0; // set old_nb_occ for the end of the word to 0
for(int depth = length; depth > 0; depth--)
{
    node = root; // reset tree
    for(int i = 0; i < depth; i++) // go to the last remaining letter
    {
        index = char_to_int(word[i]);
        if(node->children[index] == NULL)
        {
            printf("ERROR : word does not exist, could not update");
            return -1;
        }
        node = node->children[index];
    }
    node->nb_occ = node->children[index_most_common_children(node)]->nb_occ; // set nb_occ to hte max of the nb_occ of the children
}
return res;
}

word_array get_most_common_words(prefix_tree root, int n)
{
prefix_tree node = root;
int* memory_nb_occ = (int*) malloc(n * sizeof(int));
int index;
int char_index;
word_array res = create_empty_word_array(n);
for(int i = 0; i < n; i++)
{
    char_index = 0;
    do
    {
        index = index_most_common_children(node);
        res.words[i][char_index] = (char) index;
        char_index++;
        node = node->children[index];
    } while (index != 0);
    memory_nb_occ[i] = remove_all_occs(root, res.words[i]); // temporarily remove the word from the root tree
}
for(int i = 0; i < n; i++)
{
    update_word(root, res.words[i], memory_nb_occ[i]); // re-add the words to the root tree
}
return res;
}

