#include <stdio.h>
#include <string.h>
#include "read.h"
#include "utilities.h"
#include "prefix_trees.h"

char common_words_filename[] = "data/mots_courants.txt";
char dict_filename[] = "data/dico.txt";

int process_input(prefix_tree common_words, prefix_tree dict);
word_array predict_word(prefix_tree common_words, prefix_tree dict, char* prefix, int nb_words);

int main() 
{

    

    prefix_tree dict = read_prefix_tree(dict_filename);
    prefix_tree common_words = read_prefix_tree(common_words_filename);

    /* Test code goes here */
    
    /* End of testing area */
    char choice;
    int infinite;
    char validation;
    char word[MAX_WORD_LENGTH];
    printf("\nWelcome\nPress :\na - to add a word the word list\np - to predict the word that you want to write\ni - to predict multiple times in a row\nq - to quit the software\nanything else - to show the commands\n");
    while (1)
    {
        infinite = 0;
        printf("\nPlease enter a command : ");
        scanf(" %c", &choice);
        switch (choice)
        {
        case 'a':
            printf("Please enter a word to add (to the dictionary) : ");
            scanf("%s", word);
            user_words_writing(dict_filename, word);
            printf("Added %s to the dictionary\n",word);
            break;
        case 'p':
            printf("Please enter the beginning of your word : ");
            process_input(common_words, dict);
            break;
        case 'i':
            strcpy(word, "");
            while(!infinite)
            {
                printf("Please enter the beginning of a word : ");
                process_input(common_words, dict);
                printf("Do you want to quit this mode [1(yes)/0(no)] ");
                scanf("%d",&infinite);
            }
            break;
        case 'q':
            printf("You have quit the software.\n");
            return 0;
        default:
            printf("Your entry is not recognized, here is the list of the commands.\n");
            printf("a - add a word the word list\np - predict the word that you want to write\ni - to predict multiple times in a row\nq - quit the software\nelse - list the commands\n");
            break;
        }
    }
    
    return 0;
}

// Function that does most of teh work
word_array predict_word(prefix_tree common_words, prefix_tree dict, char* prefix, int nb_words)
{
    char temp[MAX_WORD_LENGTH];
    read_word(&common_words, prefix);
    read_word(&dict, prefix);
    word_array res = create_empty_word_array(nb_words);

    word_array choices = get_most_common_words(common_words, nb_words);
    for(int i = 0; i < nb_words; i++) // fetch additional words in the dict if needed
    {
        if(!strcmp(choices.words[i], ""))
        {
            strcpy(choices.words[i], get_most_common_word(dict));
            delete_word(dict, choices.words[i]);
            // printf("fetched a word from dict \n");
        }
    }
    printf("( ");
    for (int j = 0; j < nb_words; j++)
    {
        strcpy(temp, prefix);
        strcat(temp, choices.words[j]);
        strcpy(res.words[j], temp);
        printf("(%d) %s ", j+1, temp);
    }
    printf(")\n");
    return res;
}

int process_input(prefix_tree common_words, prefix_tree dict)
{
    char word[MAX_WORD_LENGTH];
    char final_word[MAX_WORD_LENGTH];
    word_array predictions;
    int n;

    scanf("%s", word);
    predictions = predict_word(common_words, dict, word, 3);
    printf("What did you mean ? Type the corresponding number, or finish the word.\n");
    printf("%s", word);
    scanf("%s", final_word);
    n = atoi(final_word);
    if(n > 0 && n <= 3)
        strcpy(final_word, predictions.words[n-1]);
    else 
    {
        strcat(word, final_word); 
        strcpy(final_word, word);
    }
    if(read_word(&dict, final_word))
    {
        printf("Added an occurence of the word %s to the common words file\n", final_word);
        user_words_writing(common_words_filename, final_word);
        return 1;
    }
    printf("Word is not in the dictionnary, was ignored following the project guidelines.\n");
    return 0;
}