#include <iostream>
#include <string>
#include "FBullCowGame.h"

void PrintIntro();
void PlayGame();
std::string GetGuess();
bool AskToPlayAgain();
FBullCowGame BCGame; // instantiate a new game

// Entry point for the application
int main()
{
	do
	{
		PrintIntro();
		PlayGame();
	} while (AskToPlayAgain());
	system("pause");
	return 0;

}


void PrintIntro() 
{
	//Introduce the game
	constexpr int WORD_LENGTH = 9;
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << "Can you guess the " << WORD_LENGTH;
	std::cout << " letter isogram I'm thinking of?\n";
	return;
}

void PlayGame()
{
	BCGame.Reset();
	// Loop for the number of turns asking for guesses
	int MaxTries = BCGame.GetMaxTries();

	for (int i = 0; i < MaxTries; i++)
	{
		std::cout << "You guessed: " << GetGuess();
		std::cout << std::endl;
	}
	return;
}

std::string GetGuess() 
{
	// get a guess from the player
	int CurrentTry = BCGame.GetCurrentTry();
	std::cout << "Try " << CurrentTry << " Enter your guess: ";
	std::string Guess = "";
	std::getline(std::cin, Guess);
	return Guess;
}

bool AskToPlayAgain()
{
	//Ask the player if they want to play again
	std::cout << "Do you want to play again? (y/n) ";
	std::string Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}