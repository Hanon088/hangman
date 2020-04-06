#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

char progressBar[51];
char *screenPtr = NULL;
char choosenWord[51];
char hint[250];
char wordsArr[50][300];
FILE *fptr;
char *bg[] = {"          HANGMAN          \n        -----              \n       |                   \n       |                   \n       |                   \n       |                   \n       |                   \n       |                   \n       |                   \n      ___                  ",
              "          HANGMAN          \n        -----              \n       |                   \n       |                   \n       |                   \n       |                   \n       |                   \n       |                   \n       |                   \n      ___                  ",
              "          HANGMAN          \n        -----              \n       |     |             \n       |                   \n       |                   \n       |                   \n       |                   \n       |                   \n       |                   \n      ___                  ",
              "          HANGMAN          \n        -----              \n       |     |             \n       |     0             \n       |                   \n       |                   \n       |                   \n       |                   \n       |                   \n      ___                  ",
              "          HANGMAN          \n        -----              \n       |     |             \n       |     0             \n       |    /|\\            \n       |                   \n       |                   \n       |                   \n       |                   \n      ___                  ",
              "          HANGMAN          \n        -----              \n       |     |             \n       |     0             \n       |    /|\\            \n       |    / \\            \n       |                   \n       |                   \n       |                   \n      ___                  "};


void screenUpdate(char *outputText);
void welcome_screen();
int setDifficulty(int level);
void getWordAndHint();
char *createProgressBar(char *word);
char *updateProgressBar(char ch);
int notInProgressBar(char ch);
int pointCount(char ch);
void playGame();

int main(){
    //Main
    system("@cls||clear");
    screenPtr = malloc(600 * sizeof(char));
    welcome_screen();
    getWordAndHint();
    sprintf(screenPtr, "%sHint: %s\n\n     %s\n", bg[0], hint, createProgressBar(choosenWord));
    screenUpdate(screenPtr);
    playGame();
    while(1){
        printf("Play Again? (Y/N)\nOr M for menu\n");
        char choice;
        scanf(" %c", &choice);
        if((int)choice == 'M' || (int)choice == 'm'){
            fclose(fptr);
            main();
            break;}
        else if((int)choice == 'Y' || (int)choice == 'y'){
            system("@cls||clear");
            getWordAndHint();
            sprintf(screenPtr, "%sHint: %s\n\n     %s\n", bg[0], hint, createProgressBar(choosenWord));
            screenUpdate(screenPtr);
            playGame();}
        else{
            fclose(fptr);
            printf("Exiting\n");
            break;}
    }
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

void getWordAndHint(){
    time_t t;
    char bufferRaw[300], bufferWord[51];
    int state = 0, num = 0;
    srand((unsigned) time(&t));
    strcpy(bufferRaw, wordsArr[rand() % (sizeof(wordsArr)/sizeof(wordsArr[0]))]);
    for(int i = 0; i <= strlen(bufferRaw); i++){
        if(state == 1){hint[num++] = bufferRaw[i];}
        else if((int)bufferRaw[i] != ';'){
            bufferWord[i] = bufferRaw[i];
        }
        else{
            bufferWord[i] = '\0';
            state = 1;
        }
    }
    strcpy(choosenWord, bufferWord);
}

int setDifficulty(int level){
    if(level == 0){fptr = fopen("easy_words.txt", "r");}
    else if(level == 1){fptr = fopen("medium_words.txt", "r");}
    else if(level == 2){fptr = fopen("hard_words.txt", "r");}
    if(fptr == NULL){printf("Error opening file.");return -1;}
    for(int i = 0; i < 50; i++){
        fgets(wordsArr[i], 300, fptr);
    }
    return 0;
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
                sprintf(screenPtr, "%sHint: %s\n\n     %s\n\n%c is correct\n\n", bg[5-life], hint, updateProgressBar(temp), temp);
                screenUpdate(screenPtr);
                state = 1;
            }
        }
        if(!state){
            life--;
            sprintf(screenPtr, "%sHint: %s\n\n     %s\n\n%c is incorrect\n\n", bg[5-life], hint, updateProgressBar(temp), temp);
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

void welcome_screen(){
    sprintf(screenPtr, "          HANGMAN          \n                           \n                           \n                           \n                           \n                           \n  EASY: PRESS A + ENTER    \n  NORMAL: PRESS S + ENTER  \n  HARD: PRESS D + ENTER    \n                           \n");
    screenUpdate(screenPtr);
    char diff;
    int level;
    scanf(" %c", &diff);
    if ((int)diff == 'A' || (int)diff == 'a'){
        level = 0;}
    else if ((int)diff == 'S' || (int)diff == 's'){
        level = 1;}
    else if ((int)diff == 'D' || (int)diff == 'd'){
        level = 2;}
    setDifficulty(level);
}