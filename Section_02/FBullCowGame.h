//
// Created by Paulo Trigueiros on 11/10/16.
//
/*
 * The game logic (no view code or direct user interaction)
 * The game is s simple guess the word game based on Mastermind
 *
 */

#pragma once

#include <string>

using FString = std::string;
using int32 = int;
using ulong = unsigned long;

struct FBullCowCount {
    int32 Bulls = 0;
    int32 Cows = 0;
};

enum class EGuessStatus {
    Invalid_Status,
    OK,
    Not_Isogram,
    Wrong_Lenght,
    Not_Lowercase
};

class FBullCowGame {
public:
    FBullCowGame();

    void    reset();
    int32   getMaxTries() const;
    int32   getCurrentTry() const;
    int32   getHiddenWordLength() const;

    EGuessStatus checkGuessValidity(FString) const;

    bool    isGameWon() const;

    // counts bulls and cows, and increases try number assuming valid guess
    FBullCowCount submitValidGuess(FString);

private:
    int32   myCurrentTry;

    FString myHiddenWord;
    bool    bGameIsWon;

    bool isIsogram(FString) const;
    bool isLowerCase(FString) const;
};
