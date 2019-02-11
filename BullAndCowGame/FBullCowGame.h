/* 
The game logic (no view code or direct user interaction)
The game is a simple guess word based on Mastermind.
*/

#pragma once
#include <string>

//for UE4 type compliance
using FString = std::string; 
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

enum class EResetStatus
{
	No_Hidden_Word,
	OK,
};

class FBullCowGame
{
public:
	FBullCowGame(); //constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;

	void Reset(); 
	FBullCowCount SubmitValidGuess(FString); // counts bulls and cows and incrementing the try number assuming a valid guess.
private:
	//see constructor for initialization
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;

};