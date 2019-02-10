/* This is the console executable, that makes use of the BullCowClass
This acts as the view in a MVC pattern, and is responsible for all user interaction.
For game logic see the FBullCowGame class.

*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string; //for UE4 type compliance
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
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
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	return;
}

void PlayGame()
{
	BCGame.Reset();
	// Loop for the number of turns asking for guesses
	int32 MaxTries = BCGame.GetMaxTries();	//TODO change from FOR to WHILE loop once we are validating tries.
	for (int32 i = 0; i < MaxTries; i++) {
		FText Guess = GetValidGuess();
		FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);
		//submit valid guess to the game
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << " and Cows = " << BullCowCount.Cows << "\n\n";
	}
	return;

	//TODO add a game summary.
}

//loop continually until the user gets a valid guess
FText GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do 
	{
		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " Enter your guess: ";
		FText Guess = "";
		std::getline(std::cin, Guess);
		
		// check status and give feedback
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word. \n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters. \n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter your guess in lowercase letters. \n";
			break;
		default:
			return Guess;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK); //loop until the user gives a valid guess
}

bool AskToPlayAgain()
{
	//Ask the player if they want to play again
	std::cout << "Do you want to play again? (y/n) ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}