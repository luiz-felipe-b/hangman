#include <stdio.h>
#include <string.h>

void opening() {
    printf("X             X\n");
    printf("X             X\n");
    printf("X             X\n");
    printf("o=============o\n");
    printf("||  HANGMAN  ||\n");
    printf("o=============o\n");
}

void guess(char guesses[26], int tries) {
    char guess;
    scanf(" %c", &guess);

    guesses[tries] = guess;
}

int main() {
    char secretword[20];

    sprintf(secretword, "WATERMELON");

    int correct = 0;
    int hung = 0;

    char guesses[26];
    int tries = 0;

    opening();

    do {

        for(int i = 0; i < strlen(secretword); i++) {

            int found = 0;

            for (int j = 0; j < tries; j++) {

                if(guesses[j] == secretword[i]) {
                    found = 1;
                    break;                    
                }
            }

            if(found) {
                printf("%c", secretword[i]);
            } else {
                printf("_ ");
            }
        }
        printf("\n");

        guess(guesses, tries);
        tries++;

    } while(!correct && !hung);
}