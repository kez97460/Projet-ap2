#include <stdio.h>
#include <string.h>
#include "read.h"
#include "utilities.h"
#include "prefix_trees.h"

void main()
{
    prefix_tree tree = create_node();
    add_word(tree, "hello");
    add_word(tree, "hi");
    add_word(tree, "hell");
    add_word(tree, "feur");
    add_word(tree, "feur");

    word_array res = create_empty_word_array(2);
    res = get_most_common_words(tree,2);
    printf("Most common word : %s \n",res.words[0]);
}