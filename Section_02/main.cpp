/*
 * This is the console executable, that make use of the BullCow class
 * It is respnsoble for all user interaction. For Game logic see the FBullCowGame class
 * */
#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

void printIntro();
void playGame();
bool playAgain();
FText getValidGuess();
void printGuess(const FText &);
void printGameSummary();

FBullCowGame BCGame;        // instanciate a new game, which we re-use across plays

// the entry point for our app
int32 main() {
    bool response = true;
    do {
        printIntro();
        playGame();

        response = playAgain();
    } while(response);

    return 0;
}

// Introduce the Game
void printIntro()
{

    std::cout << "Wellcome to Bulls and Cows, a fun word game" << std::endl;
    std::cout << "         {    }           \\   /\n\n";
    std::cout << "Can you guess the " << BCGame.getHiddenWordLength();
    std::cout << " letter isogram I'm thinking of?\n\n\n";
}

// main game loop
void playGame() {
    BCGame.reset();
    int32 maxTries = BCGame.getMaxTries();

    // loop asking for guesses while game is NOT won
    // and there is still tries remaining
    while(!BCGame.isGameWon() && BCGame.getCurrentTry() <= maxTries) {
        FText guess = getValidGuess();

        // submit valid guess to the game
        FBullCowCount bullCowCount = BCGame.submitValidGuess(guess);

        std::cout << "Bull= " << bullCowCount.Bulls;
        std::cout << ". Cows= " << bullCowCount.Cows << "\n\n";

        /*if(guess.empty()) printGuess(guess);
        else
            std::cout << "Your guess value was empty..." << std::endl; */
    }

    printGameSummary();
}

// loop continually until the user gives a valid guess
FText getValidGuess()
{
    EGuessStatus Status = EGuessStatus::Invalid_Status;
    FText guess = "";

    do {
        int32 currentTry = BCGame.getCurrentTry();
        std::cout << "Try " << currentTry << " of " << BCGame.getMaxTries() << ". Input your guess: ";
        getline(std::cin, guess);

        Status = BCGame.checkGuessValidity(guess);
        switch (Status) {
            case EGuessStatus::Not_Isogram :
                std::cout << "The word you entered is not an isogram (word with repeating letters)... \n";
                break;
            case EGuessStatus::Wrong_Lenght:
                std::cout << "Please anter a " << BCGame.getHiddenWordLength() << " letter word.\n";
                break;
            case EGuessStatus::Not_Lowercase :
                std::cout << "The word must be lowercase. \n";
                break;
            default:
                // Assuming the guess is valid
                break;
        }

        //std::cout << std::endl;
    } while(Status != EGuessStatus::OK);    //Keep looping until we get no errors

    return guess;
}

bool playAgain()
{
    std::cout << "Do you want to play again? ";
    FText response = "";
    getline(std::cin, response);

    return (response[0] == 'y' || response[0] == 'Y');
}




// repeat the guess back to them
void printGuess(const FText &ans)
{
    std::cout << "Your guess was: " << ans << "\n\n";
}

void printGameSummary()
{
    if(BCGame.isGameWon()) {
        std::cout << "You WON! Congratulations!" << std::endl;
        std::cout << "You got the right word at the " << BCGame.getCurrentTry()-1 << "th attempt." << "\n\n\n";
    }
    else
        std::cout << "You LOST. Maybe next time :)..." << std::endl;
}
