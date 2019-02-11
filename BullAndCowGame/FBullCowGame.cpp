#pragma once
#include "FBullCowGame.h"
#include <map>


//UE4 freindliness
#define TMap std::map

FBullCowGame::FBullCowGame(){Reset();} // default constructor

// Getters
int32 FBullCowGame::GetCurrentTry() const{return MyCurrentTry;}
int32 FBullCowGame::GetHiddenWordLength() const{ return MyHiddenWord.length();}
bool FBullCowGame::IsGameWon() const {	return bGameIsWon;}

int32 FBullCowGame::GetMaxTries() const{
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,16}, {7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "planet"; //This must be an isogram. //TODO make a list of words that can be auto generated
	MyCurrentTry = 1;
	MyHiddenWord = HIDDEN_WORD;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))// if the guess isn't an isogram, 
	{
		return EGuessStatus::Not_Isogram; 
	}
	else if (!IsLowercase(Guess)) // if the guess isn't all lowercase
	{
		return EGuessStatus::Not_Lowercase; 
	}
	else if (GetHiddenWordLength() != Guess.length()) // if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else // otherwise return OK
	{
		return EGuessStatus::OK;
	}

}

// Receives a valid guess and increments the try returns the count.
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	
	FBullCowCount BullCowCount;
	// loop through all letters in the hidden word
	int32 WordLength = MyHiddenWord.length();
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		// compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			//if they match then 
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				if (MHWChar == GChar) { // increment bulls if they're in the same place
					BullCowCount.Bulls++;
				}
				else { // increment cows if not
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Guess) const
{
	// treat 0 and 1 letters words as isograms
	if (Guess.length() <= 1){return true;}
	//define the map
	TMap <char, bool> LetterSeen;
	// iterate through each letter from guess
	for (auto Letter : Guess) {
		Letter = tolower(Letter);
		// load the letter into the map
		// if the value of the map is already true, then break the loop and return false.
		if (LetterSeen[Letter]) {
			return false; // not an isogram
		}
		else {
			LetterSeen[Letter] = true; // is isogram
		}
	}
	
	return true;
}

bool FBullCowGame::IsLowercase(FString Guess) const
{
	// handle null \0 values
	if (Guess.length() <= 1) { return true; }
	// iterate through all letters
	for (auto Letter : Guess) {
		if (!islower(Letter)) { return false; } // if the letter is lowercase then return true
	}
	return true;
}
