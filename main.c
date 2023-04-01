#include <stdio.h>

int main() {
    
    char entry[30];
    printf("Please write something\n");
    scanf("%30s", entry);
    printf("You wrote %s\n", entry);

    user_words_writing("data/mots_courants.txt", entry);

    return 0;
}