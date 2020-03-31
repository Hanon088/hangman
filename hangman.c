#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

char progressBar[51];
char *screenPtr = NULL;
char choosenWord[300];
FILE *fptr;
char *bg[] = {"          HANGMAN          \n        -----              \n       |                   \n       |                   \n       |                   \n       |                   \n       |                   \n       |                   \n       |                   \n      ___                  \n",
              "          HANGMAN          \n        -----              \n       |                   \n       |                   \n       |                   \n       |                   \n       |                   \n       |                   \n       |                   \n      ___                  \n",
              "          HANGMAN          \n        -----              \n       |     |             \n       |                   \n       |                   \n       |                   \n       |                   \n       |                   \n       |                   \n      ___                  \n",
              "          HANGMAN          \n        -----              \n       |     |             \n       |     0             \n       |                   \n       |                   \n       |                   \n       |                   \n       |                   \n      ___                  \n",
              "          HANGMAN          \n        -----              \n       |     |             \n       |     0             \n       |    /|\\            \n       |                   \n       |                   \n       |                   \n       |                   \n      ___                  \n",
              "          HANGMAN          \n        -----              \n       |     |             \n       |     0             \n       |    /|\\            \n       |    / \\            \n       |                   \n       |                   \n       |                   \n      ___                  \n"};


void screenUpdate(char *outputText);
//welcome_screen();
//void chooseDifficulty(int level);
void getWord();
//void getHint();
char *createProgressBar(char *word);
char *updateProgressBar(char ch);
int notInProgressBar(char ch);
int pointCount(char ch);
void playGame();

int main(){
    //Main
    system("@cls||clear");
    screenPtr = malloc(300 * sizeof(char));
    getWord();
    sprintf(screenPtr, "%s\n     %s", bg[0], createProgressBar(choosenWord));
    screenUpdate(screenPtr);
    playGame();
    printf("Exiting\n");
    return 0;
}

void screenUpdate(char *outputText){
    system("@cls||clear");
    printf("%s\n", outputText);
}

char *createProgressBar(char *word){
    strcpy(progressBar, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0");
    for(int i = 0; i < strlen(word); i++){
        progressBar[i] = '-';
    }
    return progressBar;
}

char *updateProgressBar(char ch){
    for(int i = 0; i < strlen(choosenWord); i++){
        if((int)choosenWord[i] == ch){progressBar[i] = ch;}
    }
    return progressBar;
}

int notInProgressBar(char ch){
    for(int i = 0; i < strlen(progressBar); i++){
        if((int)progressBar[i] == ch){return 0;}
    }
    return 1;
}

int pointCount(char ch){
    int count = 0;
    for(int i = 0;i < strlen(choosenWord); i++){
        if((int)choosenWord[i] == ch){count++;}
    }
    return count;
}

void getWord(){
    char *words[] = {"test", "zoo", "demagogue", "cherry", "hello", "world", "dictator"};
    time_t t;
    srand((unsigned) time(&t));
    strcpy(choosenWord, words[rand() % (sizeof(words)/sizeof(words[0]))]);
}

void playGame(){
    char temp;;
    int state = 0, points = 0, life = 5;
    while(1){
        printf("Input a character: ");
        state = 0;
        scanf(" %c", &temp);
        system("@cls||clear");
        for(int i = 0; i < strlen(choosenWord); i++){
            if((int)choosenWord[i] == temp && notInProgressBar(temp)){
                points += pointCount(temp);
                sprintf(screenPtr, "%s\n     %s\n%c is correct\n", bg[5-life], updateProgressBar(temp), temp);
                screenUpdate(screenPtr);
                state = 1;
            }
        }
        if(!state){
            life--;
            sprintf(screenPtr, "%s\n     %s\n%c is incorrect\n", bg[5-life], updateProgressBar(temp), temp);
            screenUpdate(screenPtr);
            if(life <= 0){
                printf("You died\n");
                printf("The correct word is %s\n", choosenWord);
                break;}
        }
        if(points == strlen(choosenWord)){
            printf("You won, the word is %s\n", choosenWord);
            printf("You've got %d points\n", points);
            break;}
    }
}
