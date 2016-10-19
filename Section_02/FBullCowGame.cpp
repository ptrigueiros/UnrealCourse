//
// Created by Paulo Trigueiros on 11/10/16.
//

#include "FBullCowGame.h"
#include <map>
#define TMap std::map

FBullCowGame::FBullCowGame()
{
    reset();
}

void FBullCowGame::reset()
{
    const FString HIDDEN_WORD = "paulos";       // this must be an isogram
    myHiddenWord = HIDDEN_WORD;

    myCurrentTry = 1;
    bGameIsWon = false;
}

int32 FBullCowGame::getMaxTries() const
{
    TMap<int32, int32> wordLengthToMaxTries{{3, 3}, {4, 4}, {5, 5}, {6, 6}};
    return wordLengthToMaxTries[myHiddenWord.length()];
}

int32 FBullCowGame::getCurrentTry() const
{
    return myCurrentTry;
}

int32 FBullCowGame::getHiddenWordLength() const
{
    return myHiddenWord.length();
}

bool FBullCowGame::isGameWon() const
{
    return bGameIsWon;
}

EGuessStatus FBullCowGame::checkGuessValidity(FString guess) const
{
    if(!isIsogram(guess)) {             // if the guess isn't an isogram
        return EGuessStatus::Not_Isogram;
    }
    else if(!isLowerCase(guess)) {        // if the guess isn't all lowercase
        return EGuessStatus::Not_Lowercase;
    }
    else if(guess.length() != getHiddenWordLength()) {  // if the guess lenght is wrong
        return EGuessStatus::Wrong_Lenght;
    }
    else
        return EGuessStatus::OK;
}

// receives a VALID guess, increments turn and returns count
FBullCowCount FBullCowGame::submitValidGuess(FString guess)
{
    myCurrentTry++;
    FBullCowCount bullCowCount;
    ulong wordLenght = myHiddenWord.length();   //assuning the same lenght as guess

    for(int32 hwChar = 0; hwChar < wordLenght; hwChar++) {
        // compare letters against the guess
        for(int32 gChar = 0; gChar < wordLenght; gChar++) {
            // if they match then
            if(guess[gChar] == myHiddenWord[hwChar]) {
                if (hwChar == gChar) // if they're in the same place
                    bullCowCount.Bulls++; //increment bulls

                else
                    bullCowCount.Cows++; // increment cows
            }
        }
    }
    if(bullCowCount.Bulls == wordLenght)
        bGameIsWon = true;
    else
        bGameIsWon = false;

    return bullCowCount;
}

bool FBullCowGame::isIsogram(FString word) const
{
    // treat 0 and 1 letter words as isograms
    if(word.length() <= 1) return true;


    TMap<char, bool> letterSeen;    // setup our map
    for(auto letter : word) {       // for all letters in word
        letter = tolower(letter);   // handle mixed case
        if(letterSeen[letter] )
            return false;
        else
            letterSeen[letter] = true;
    }
    return true;
}

bool FBullCowGame::isLowerCase(FString word) const
{
    if(word.length() <= 1) return true;

    for(auto letter : word) {
        if(!islower(letter))
            return false;
    }
    return true;
}




