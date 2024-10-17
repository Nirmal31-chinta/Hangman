#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define MAX_TRIES 6
#define WORD_COUNT 5

void display_hangman(int tries) {
    switch (tries) {
        case 6: printf("  _______\n |     |\n |     O\n |    /|\\\n |    / \\\n |\n"); 
                break;
        case 5: printf("  _______\n |     |\n |     O\n |    /|\\\n |    / \n |\n"); 
                break;
        case 4: printf("  _______\n |     |\n |     O\n |    /|\\\n |    \n |\n"); 
                break;
        case 3: printf("  _______\n |     |\n |     O\n |     |\n |    \n |\n"); 
                break;
        case 2: printf("  _______\n |     |\n |     O\n |    \n |    \n |\n"); 
                break;
        case 1: printf("  _______\n |     |\n |    \n |    \n |    \n |\n"); 
                break;
        case 0: printf("  _______\n |     |\n |\n |\n |\n |\n"); 
                break;
        default: break;
    }
}

int main() {
    srand(time(NULL));
    
    const char *words[WORD_COUNT] = {"programming", "computer", "hangman", "development", "challenge"};
    const char *hints[WORD_COUNT] = {
        "The process of writing computer code.",
        "An electronic device for storing and processing data.",
        "A game where you guess letters to form a word.",
        "The process of creating software applications.",
        "A difficult task that tests your skills."
    };
    
    char guessed_word[20];
    char guessed_letters[26];
    int tries, correct_guesses, word_length, score;
    char guess[3];  
    int found;
    char play_again;

    do {
        tries = 0;
        correct_guesses = 0;
        score = 0;

        int random_index = rand() % WORD_COUNT;
        const char *secret_word = words[random_index];
        const char *hint = hints[random_index];
        word_length = strlen(secret_word);
        
        // Initialize guessed_word with underscores
        for (int i = 0; i < word_length; i++) {
            guessed_word[i] = (secret_word[i] == ' ') ? ' ' : '_';
        }
        guessed_word[word_length] = '\0';
        memset(guessed_letters, 0, sizeof(guessed_letters));

        printf("Welcome to Hangman!\n");
        printf("Hint: %s\n", hint);

        while (tries < MAX_TRIES && correct_guesses < word_length) {
            display_hangman(tries);
            printf("\nWord: %s\n", guessed_word);
            printf("Guessed letters: ");
            for (int i = 0; i < 26; i++) {
                if (guessed_letters[i]) {
                    printf("%c ", 'A' + i);
                }
            }
            printf("\nEnter a letter: ");
            scanf("%s", guess);

            // Validate input
            if (strlen(guess) != 1 || !isalpha(guess[0])) {
                printf("Invalid input. Please enter a single alphabetical letter.\n");
                continue;
            }
            guess[0] = tolower(guess[0]);

            if (guessed_letters[guess[0] - 'a']) {
                printf("You've already guessed '%c'. Try again.\n", guess[0]);
                continue;
            }
            guessed_letters[guess[0] - 'a'] = 1;

            found = 0;
            for (int i = 0; i < word_length; i++) {
                if (secret_word[i] == guess[0]) {
                    guessed_word[i] = guess[0];
                    found = 1;
                    correct_guesses++;
                    score++; // Increment score for each correct guess
                }
            }

            if (!found) {
                tries++;
                printf("Sorry, '%c' is not in the word.\n", guess[0]);
            }
        }

        if (correct_guesses == word_length) {
            printf("Congratulations! You've guessed the word: %s\n", secret_word);
            printf("Your score for this game: %d\n", score);
        } else {
            display_hangman(tries);
            printf("You've run out of tries! The word was: %s\n", secret_word);
            printf("Your score for this game: %d\n", score);
        }

        // Ask if the player wants to play again
        do {
            printf("Do you want to play again? (y/n): ");
            scanf(" %c", &play_again);
            play_again = tolower(play_again);
            if (play_again != 'y' && play_again != 'n') {
                printf("Invalid input. Please enter 'y' for yes or 'n' for no.\n");
            }
        } while (play_again != 'y' && play_again != 'n');

    } while (play_again == 'y');

    printf("Thank you for playing!\n");
    return 0;
}