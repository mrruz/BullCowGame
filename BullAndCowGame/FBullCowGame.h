#pragma once
#include <string>

class FBullCowGame
{
public:
	FBullCowGame(); //constructor

	int GetMaxTries() const;
	int GetCurrentTry() const;
	bool IsGameWon() const;

	void Reset(); //TODO make a more rich return value.
	bool CheckGuessValidity(std::string); // TODO make a more rich return value.
	// Provide a method for counting bulls and cows and incrementing the try number.


// ^^ Please try ignore this and focus on the interface above ^^
private:
	//see constructor for initialization
	int MyCurrentTry;
	int MyMaxTries;
};