#include "read.h"
#include "prefix_trees.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

prefix_tree read_prefix_tree(char *filename)
{
  FILE *file;
  int i = 0;
  char storage[MAX_WORD_LENGTH];
  prefix_tree tree = create_node();

  file = fopen(filename, "r");
  if (file == NULL)
  {
    printf("Warning : Could not open file\n");
    return tree;
  }
  while ((fscanf(file, "%s", storage)) == 1)
  {
    add_and_update_word(tree, storage);
    i++;
  }
  fclose(file);
  printf("Successfully read %d words from file %s\n", i, filename);
  return tree;
}

// writes the content of a prefix tree to a text file. DELETES THE PREFIX TREE
void write_prefix_tree(prefix_tree tree, char *filename)
{
  char temp[MAX_WORD_LENGTH];
  int n;
  int wordcount;
  FILE* file = fopen(filename, "w");
  if(file == NULL)
  {
    printf("Warning : Could not open file\n");
    return;
  }
  while(tree->nb_occ != 0)
  {
    strcpy(temp, get_most_common_word(tree));
    n = delete_word(tree, temp);
    for (int i = 0; i < n; i++)
    {
      fprintf(file, "%s\n", temp);
      wordcount++;
    }
  }
  fclose(file);
  printf("Wrote %d words to the file %s \n", wordcount, filename);
}
