#include <stdio.h>
#include <string.h>
#include "read.h"
#include "utilities.h"
#include "prefix_trees.h"

void main()
{
    prefix_tree tree = create_node();
    add_and_update_word(tree, "hello");
    add_and_update_word(tree, "hi");
    add_and_update_word(tree, "hi");
    add_and_update_word(tree, "hell");
    add_and_update_word(tree, "feur");
    add_and_update_word(tree, "feur");
    add_and_update_word(tree, "feur");
    add_and_update_word(tree, "feur");

    char* helpme = get_most_common_word(tree);
    printf("Most common word : %s \n", helpme);

    int fuckthis;

    // read_word(&tree, "feur", MAX_WORD_LENGTH);
    // fuckthis = index_most_common_children(tree);
    // printf("%d\n", fuckthis);
    int n = 3;
    word_array please = get_most_common_words(tree, n);
    printf("Most common words : |");
    for(int i = 0; i < n; i++)
    {
        printf(" %s |",please.words[i]);
    }
    printf("\n");
}