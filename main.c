#include <stdio.h>
#include <string.h>
#include "read.h"
#include "utilities.h"
#include "prefix_trees.h"

void main()
{
    prefix_tree tree ;
    tree = read_prefix_tree("data/mots_courants.txt");

    char* helpme = get_most_common_word(tree);
    printf("Most common word : %s \n", helpme);


    int n = 3;
    word_array please = get_most_common_words(tree, n);
    printf("Most common words : |");
    for(int i = 0; i < n; i++)
    {
        printf(" %s |", please.words[i]);
    }
    printf("\n");

    helpme = get_most_common_word(tree);
    printf("Most common word : %s \n", helpme);


    printf("AAA\n");
    
}