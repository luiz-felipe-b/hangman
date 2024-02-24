#include <stdio.h>
#include <string.h>

int main() {
    char secretword[20];

    sprintf(secretword, "WATERMELON");

    int correct = 0;
    int hung = 0;

    char guesses[26];
    int tries = 0;

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

        char guess;
        scanf(" %c", &guess);

        guesses[tries] = guess;
        tries++;

    } while(!correct && !hung);
}