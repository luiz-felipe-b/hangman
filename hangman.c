#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "hangman.h"

//global variables
char secretword[WORD_LENGTH];
char guesses[26];
int givenguesses = 0;

void opening() {
    printf("\n");
    printf("==X=============X=D\n");
    printf("  X             X\n");
    printf("  X             X\n");
    printf("  X             X\n");
    printf("  o=============o\n");
    printf("  ||  HANGMAN  ||\n");
    printf("  o=============o\n");
}

void guess() {
    char guess;
    printf("Choose a letter: ");
    scanf(" %c", &guess);

    if(letterexists(guess)) {
        printf("Nice! The word does have the letter %c\n\n", guess);
    } else {
        printf("What a shame! The word does not have the letter %c\n\n", guess);
    }

    guesses[givenguesses] = guess;
    givenguesses++;
}

int alreadyguessed(char letter) {
    int found = 0;

    for (int j = 0; j < givenguesses; j++) {
        if(guesses[j] == letter) {
            found = 1;
            break;                    
        }
    }

    return found;
}

void drawhang() {

    int misses = wrongguesses();
    
    printf("  _______      \n");
    printf(" |/      |     \n");
    printf(" |      %c%c%c    \n", (misses >= 1 ? '(' : ' '), (misses >= 1 ? '_' : ' '), (misses >= 1 ? ')' : ' '));
    printf(" |      %c%c%c   \n", (misses >= 3 ? '\\' : ' '), (misses >= 2 ? '|' : ' '), (misses >= 3 ? '/' : ' '));
    printf(" |       %c     \n", (misses >= 2 ? '|' : ' '));
    printf(" |      %c %c   \n", (misses >= 4 ? '/' : ' '), (misses >= 4 ? '\\' : ' '));
    printf(" |             \n");
    printf("_|___          \n");
    printf("\n");

    for(int i = 0; i < strlen(secretword); i++) {

        int found = alreadyguessed(secretword[i]);

        if(found) {
            printf("%c", secretword[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n");
}

void addword() {

    char wish;

    printf("Do you want to register a new word for the game? (Y/N)");
    scanf("%c", &wish);

    if(wish == 'Y') {
        char newword[WORD_LENGTH];

        printf("What's the new word?");
        scanf("%c", newword);

        FILE* f;

        f = fopen("words.txt", "r+");
        if(f == 0) {
            printf("Database not available.\n\n");
            exit(1);
        }

        int qty;
        fscanf(f, "%d", &qty);
        qty++;

        fseek(f , 0, SEEK_SET);
        fprintf(f, "%d", qty);

        fseek(f , 0, SEEK_END);
        fprintf(f, "\n%s", newword);

        fclose(f);
    }
}

void chooseword() {
    FILE* f;

    f = fopen("words.txt", "r");
    if(f == 0) {
        printf("Database not available.\n\n");
        exit(1);
    }

    int wordqty;
    fscanf(f, "%d", &wordqty);

    srand(1);
    int randomized = rand() % wordqty;

    for(int i = 0; i <= randomized; i++) {
        fscanf(f, "%s", secretword);
    }

    fclose(f);
}

int letterexists(char letter) {

    for (int j = 0; j < strlen(secretword); j++) {
        if(letter == secretword[j]) {
                return 1;
            }
        }

        return 0;
}

int wrongguesses() {
    int misses = 0;

    for (int i = 0; i < givenguesses; i++) {

        if (!letterexists(guesses[i])) {
            misses++;
        }
    }
    return misses;
}

int hang() {

    return wrongguesses() >= 5;
}

int win() {
    for(int i = 0; i < strlen(secretword); i++) {
        if(!alreadyguessed(secretword[i])) {
            return 0;
        }
    }

    return 1;
}

int main() {

    chooseword();
    opening();

    do {

        drawhang();
        guess();

    } while(!win() && !hang());

    if(win()) {
        printf("You got away from the hang! For now...\n");
        printf("The word was: %c\n", secretword);
    } else {
        printf("Sadly, you got hanged.\n");
    }
}