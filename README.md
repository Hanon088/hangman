# Hangman
### A terminal hangman game made in C.
Made By

Janisata Mukda นางสาวณิสตา มุกดา 62070025

Tanate Sukdaipung นายธเนศ สุขได้พึ่ง 62070085

Tawatchai Hanon นายธวัชชัย ฮานอน 62070088

Suwatphot Kalom นายสุวพจน์ กาลอม 62070211

### Documentations
The game starts by clearing the screen and allocating spaces for all the texts that will be use, shows are a welcome screen, set the difficulty, get the words, and start the game loop.

___Each of the functions serve a specific purpose, which are:___

___main()___ The main fucntion that runs the program.

___screenUpdate()___ Updates the output on the screen.

___welcome_screen()___ Create a welcome screen to greet the player and choose the difficulty level.

___setDifficulty()___ Open the words.txt files according to the difficulty choosen.

___getWordAndHint()___ Choose a random word taken from the words.txt files.

___createProgressBar()___ Create a progress bar used to show the letters guessed correctly.

___updateProgressBar()___ Update the progress bar each time the player guessed correctly.

___notInProgressBar()___ Check if a letter has already been guessed correctly.

___correctCount()___ Count the number a letter appear in the choosen word.

___findSpace()___ Find the number of whitespaces in the choosen word.

___playGame()___ The main game loop that takes the input and count the scores.

___clearGame()___ Clear all the memory and filestream.
