#include "FBullCowGame.h"

FBullCowGame::FBullCowGame()
{
	Reset();
}

// Getters
int FBullCowGame::GetMaxTries() const{return MyMaxTries;}
int FBullCowGame::GetCurrentTry() const{return MyCurrentTry;}
bool FBullCowGame::IsGameWon() const {	return false;}


void FBullCowGame::Reset()
{
	constexpr int MAX_TRIES = 8;
	MyCurrentTry = MAX_TRIES;
	MyMaxTries = 5;
	return;
}

bool FBullCowGame::CheckGuessValidity(std::string)
{
	return false;
}
