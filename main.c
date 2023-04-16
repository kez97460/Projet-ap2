#include <stdio.h>
#include <string.h>
#include "read.h"
#include "utilities.h"
#include "prefix_trees.h"

int main() 
{
    char choice;
    char word[30];
    printf("\nWelcome\nPress :\na - to add a word the word list\np - to predict the word that you want to write\nq - to quit the software\nelse - to show the list the commands\n");
    while (1)
    {
        printf("\nPlease enter something:\n");
        scanf(" %c", &choice);
        switch (choice)
        {
        case 'a':
            printf("Please enter a word to add :\n");
            scanf("%s", word);
            user_words_writing("mots_courant", word);
            break;
        case 'p':
            printf("Please enter the begin of your word :\n");
            scanf("%s", word);
            break;
        case 'q':
            printf("You had quit the software.\n");
            return 0;
        default:
            printf("Your entry is not recognized, here is the list of the commands.\n");
            printf("a - add a word the word list\np - predict the word that you want to write\nq - quit the software\nelse - list the commands\n");
            break;
        }
    }
    
    return 0;
}