#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

char *progressBar = NULL;
char *screenPtr = NULL;
char *choosenWord = NULL;
char *hint = NULL;
char wordsArr[50][300];
int points = 0;
FILE *fptr;
char *bg[] = {"          HANGMAN          \n        -----              \n       |                   \n       |                   \n       |                   \n       |                   \n       |                   \n       |                   \n       |                   \n      ___                  ",
              "          HANGMAN          \n        -----              \n       |                   \n       |                   \n       |                   \n       |                   \n       |                   \n       |                   \n       |                   \n      ___                  ",
              "          HANGMAN          \n        -----              \n       |     |             \n       |                   \n       |                   \n       |                   \n       |                   \n       |                   \n       |                   \n      ___                  ",
              "          HANGMAN          \n        -----              \n       |     |             \n       |     0             \n       |                   \n       |                   \n       |                   \n       |                   \n       |                   \n      ___                  ",
              "          HANGMAN          \n        -----              \n       |     |             \n       |     0             \n       |    /|             \n       |                   \n       |                   \n       |                   \n       |                   \n      ___                  ",
              "          HANGMAN          \n        -----              \n       |     |             \n       |     0             \n       |    /|\\           \n       |                   \n       |                   \n       |                   \n       |                   \n      ___                  ",
			  "          HANGMAN          \n        -----              \n       |     |             \n       |     0             \n       |    /|\\           \n       |    /              \n       |                   \n       |                   \n       |                   \n      ___                  ",
              "          HANGMAN          \n        -----              \n       |     |             \n       |     0             \n       |    /|\\           \n       |    / \\           \n       |                   \n       |                   \n       |                   \n      ___                  ",
};


void screenUpdate(char *outputText);
void welcome_screen();
int setDifficulty(int level);
void getWordAndHint();
char *createProgressBar();
char *updateProgressBar(char ch);
int notInProgressBar(char ch);
int correctCount(char ch);
void playGame();
void clearGame();
int findSpace(char *word);

int main(){
    //Main
    system("@cls||clear");
    screenPtr = malloc(600 * sizeof(char));
    choosenWord = malloc(51 * sizeof(char));
    progressBar = malloc(51 * sizeof(char));
    hint = malloc(251 * sizeof(char));
    welcome_screen();
    getWordAndHint();
    sprintf(screenPtr, "%s \n\n Hint: %s\n\n     %s\n", bg[0], hint, createProgressBar(choosenWord));
    screenUpdate(screenPtr);
    playGame();
    while(1){
        printf("Play Again? (Y/N)\nOr M for menu\n");
        char choice;
        scanf(" %c", &choice);
        if((int)choice == 'M' || (int)choice == 'm'){
            clearGame();
            main();
            break;}
        else if((int)choice == 'Y' || (int)choice == 'y'){
            system("@cls||clear");
            getWordAndHint();
            sprintf(screenPtr, "%s \n\n Hint: %s\n\n     %s\n", bg[0], hint, createProgressBar(choosenWord));
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

char *createProgressBar(){
    for(int i = 0; i < strlen(choosenWord); i++){
        if((int)choosenWord[i] == ' '){progressBar[i] = ' ';}
        else{progressBar[i] = '-';}
    }
    progressBar[strlen(choosenWord)] = '\0';
    return progressBar;
}

char *updateProgressBar(char ch){
    for(int i = 0; i < strlen(choosenWord); i++){
        if((int)tolower(choosenWord[i]) == tolower(ch)){progressBar[i] = ch;}
    }
    return progressBar;
}

int notInProgressBar(char ch){
    for(int i = 0; i < strlen(progressBar); i++){
        if((int)tolower(progressBar[i]) == tolower(ch)){return 0;}
    }
    return 1;
}

int correctCount(char ch){
    int count = 0;
    for(int i = 0; i < strlen(choosenWord); i++){
        if((int)tolower(choosenWord[i]) == tolower(ch)){count++;}
    }
    return count;
}

void getWordAndHint(){
    time_t t;
    char bufferRaw[300], bufferWord[51];
    int state = 0, num = 0;
    srand((unsigned) time(&t));
    sprintf(choosenWord, "\0");
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

int findSpace(char *word){
    int count = 0;
    for(int i = 0; i < strlen(word); i++){
        if((int)word[i] == ' '){count++;}
    }
    return count;
}

void playGame(){
    char temp;
    int state = 0, correctNum = findSpace(choosenWord), life = 7, count = 0;
    while(1){
        printf("Input a character: ");
        state = 0;
        scanf(" %c", &temp);
        system("@cls||clear");
        if((int)temp == ' '){continue;}
        count = correctCount(temp);
        if(count != 0){
            if(notInProgressBar(temp)){
                correctNum += count;
                sprintf(screenPtr, "%s \n\n Hint: %s\n\n     %s\n\n%c is correct\n\n", bg[7-life], hint, updateProgressBar(temp), temp);
                }
            screenUpdate(screenPtr);
            state = 1;}
        if(!state){
            life--;
            sprintf(screenPtr, "%s \n\n Hint: %s\n\n     %s\n\n%c is incorrect\n\n", bg[7-life], hint, progressBar, temp);
            screenUpdate(screenPtr);
            if(life <= 0){
                printf("You died\n");
                printf("The correct word is : %s\n", choosenWord);
                points = 0;
                break;}
        }
        if(correctNum == strlen(choosenWord)){
            printf("You won, the word is : %s\n", choosenWord);
            points++;
            printf("You've got %d points\n", points);
            break;}
    }
}

void welcome_screen(){
    sprintf(screenPtr, "\n   _\n  | |\n  | |__   __ _ _ __   __ _ _ __ ___   __ _ _ __    \n  | '_ \\ / _` | '_ \\ / _` | '_ ` _ \\ / _` | '_ \\   \n  | | | | (_| | | | | (_| | | | | | | (_| | | | |  \n  |_| |_|\\__,_|_| |_|\\__, |_| |_| |_|\\__,_|_| |_|  \n                      __/ |\n                     |___/\n\n             EASY: PRESS A + ENTER    \n            NORMAL: PRESS S + ENTER  \n             HARD: PRESS D + ENTER    \n\n");
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

void clearGame(){
    points = 0;
    screenPtr = NULL;
    choosenWord = NULL;
    progressBar = NULL;
    hint = NULL;
    fclose(fptr);
    system("@cls||clear");
    for(int i = 0; i < 50; i++){
        sprintf(wordsArr[i], "\0");
    }
}