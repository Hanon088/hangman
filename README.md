# Hangman
## A terminal hangman game made in C.
Made By
Janisata Mukda นางสาวณิสตา มุกดา 62070025
Tanate Sukdaipung นายธเนศ สุขได้พึ่ง 62070085
Tawatchai Hanon นายธวัชชัย ฮานอน 62070088
Suwatphot Kalom นายสุวพจน์ กาลอม 62070211

### Documentations
The game starts by clearing the screen and allocating spaces for all the texts that will be use, shows are a welcome screen, set the difficulty, get the words, and start the game loop.

_Each of the functions serve a specific purpose, which are:_
_main()_ The main fucntion that runs the program.
_screenUpdate()_ Updates the output on the screen.
_welcome_screen()_ Create a welcome screen to greet the player and choose the difficulty level.
_setDifficulty()_ Open the words.txt files according to the difficulty choosen.
_getWordAndHint()_ Choose a random word taken from the words.txt files.
_createProgressBar()_ Create a progress bar used to show the letters guessed correctly.
_updateProgressBar()_ Update the progress bar each time the player guessed correctly.
_notInProgressBar()_ Check if a letter has already been guessed correctly.
_correctCount()_ Count the number a letter appear in the choosen word.
_findSpace()_ Find the number of whitespaces in the choosen word.
_playGame()_ The main game loop that takes the input and count the scores.
_clearGame()_ Clear all the memory and filestream.
