#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prefix_trees.h"
#include "utilities.h"

/* Creation of the structure */

// creates an empty prefix_tree and returns it
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
            printf("Error : word does not exist, could not update");
            return;
        }
        node = node->children[index];
    }
    new_number = node->nb_occ; // set new_number to the correct amount
}
node = root; // reset tree
for(int i = 0; i <= length; i++)
{
    index = char_to_int(word[i]);
    if(node->children[index] == NULL)
    {
        printf("Error : word does not exist, could not update");
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

// updates the nb_occ of the \0 at the end of a word to the specified number
void update_nb_occ(prefix_tree root, char* word, int nb)
{
    read_word(&root, word);
    root->children[0]->nb_occ = nb;
}

/*------------------*/
/*--- Prediction ---*/
/*------------------*/

// merge_sort + lists ? -> not efficient on large trees 

// frees all the children of a node
void free_all_children(prefix_tree node)
{
    for(int i = 0; i < NB_CHARS; i++)
    {
        free(node->children[i]);
        node->children[i] = NULL;
    }
}

// "reads" a letter in a prefix tree, going to the corresponding subtree. Returns 0 if subtree is empty
int read_letter(prefix_tree* root_pointer, char letter)
{
    if(*root_pointer == NULL)
    {
        return 0;
    }
    if(((*root_pointer)->children[char_to_int(letter)]) != NULL)
    {
        *root_pointer = (*root_pointer)->children[char_to_int(letter)];
        return 1;
    }
    return 0;
}

// "reads" each letter of the word, going to the corresponding subtree. Returns 1 if the subtree exists, stops and returns 0 otherwise.
int read_word(prefix_tree* root_pointer, char* word)
{
    int letter_exists;
    int length = strlen(word);
    for(int i = 0; i < length; i++)
    {
        letter_exists = read_letter(root_pointer, word[i]);
        if(!letter_exists)
        {
            return 0;
        }
    }
    return 1;
}

int index_most_common_children(prefix_tree node)
{
if(node == NULL)
{
    printf("Error : trying to compare children of an empty node \n");
    return 0;
}
int nb_occ_child;
int maxi = 0;
int res = -1; // return -1 if every node is empty
for(int i = 0; i<NB_CHARS; i++)
{
    if(node->children[i] != NULL)
        nb_occ_child = node->children[i]->nb_occ;
    else
        nb_occ_child = 0;
    if(maxi < nb_occ_child)
    {
        maxi = nb_occ_child;
        res = i;
    }
}
return res;
}

char* get_most_common_word(prefix_tree root)
{
if(root == NULL || index_most_common_children(root) == -1)
{
    return "";
}
prefix_tree node = root;
int index;
char* res = (char*) malloc(MAX_WORD_LENGTH * sizeof(char));
strcpy(res, ""); 
while ((index = index_most_common_children(node)) != 0)
{
    add_char(res, int_to_char(index));
    if(node == NULL)
    {
        printf("Error : word does not exist. WHAT. HOW. Wait is that tree EMPTY ???? \n");
        return NULL;
    }
    node = node->children[index];
} 
return res;
}

// Deletes a word from the tree. Sets useless nodes to NULL. Returns the nb_occ of the deleted word. 
int delete_word(prefix_tree root, char* word)
{
    if(!strcmp(word, ""))
    {
        return 0;
    }
    // if i don't do that i get a segfault
    char w[MAX_WORD_LENGTH];
    strcpy(w, word);

    prefix_tree node = root;
    if(!read_word(&node, word)) // goes to the end of word, returns 0 if the word doesn't exist
    {
        printf("Warning : can't delete a word that doesn't exist\n");
        return 0;
    }
    int res = node->children[0]->nb_occ; // res = nb_occ of deleted word
    free_all_children(node->children[0]);
    node->children[0] = NULL;  // delete the '\0' marknig end of word in the tree

    do
    {
        node = root; // reset node
        read_word(&node, w); // go to subtree
        node->nb_occ = 0;
        if(index_most_common_children(node) == -1)
        {
            free_all_children(node);
            node = NULL;
        }
        else
        {
            node->nb_occ = node->children[index_most_common_children(node)]->nb_occ;
        }
    } while(delete_last_char(w)); // while string not empty, delete last char.

    return res;
}

word_array get_most_common_words(prefix_tree root, int nb_words)
{
    word_array res = create_empty_word_array(nb_words);
    int* save_nb_occ = (int*) malloc(nb_words * sizeof(int));
    for(int i = 0; i < nb_words; i++)
    {
        strcpy(res.words[i], get_most_common_word(root)); // add a word
        save_nb_occ[i] = delete_word(root, res.words[i]); // delete it from the tree
    }
    for(int i = 0; i < nb_words; i++) // re-add the deleted words to the tree
    {
        add_word(root, res.words[i]);
        update_nb_occ(root, res.words[i], save_nb_occ[i]);
        update_word(root, res.words[i], save_nb_occ[i]);
    }
    return res;
}