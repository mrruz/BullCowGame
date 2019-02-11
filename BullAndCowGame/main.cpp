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
void PrintGameSummary();
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
	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game.\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n\n";
	return;
}

void PlayGame()
{
	BCGame.Reset();
	// Loop for the number of turns asking for guesses while the game is not won
	int32 MaxTries = BCGame.GetMaxTries();
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		//submit valid guess to the game
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << " and Cows = " << BullCowCount.Cows << "\n\n";
	

	}
	
	PrintGameSummary();

	return;

}

//loop continually until the user gets a valid guess
FText GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";
	do 
	{
		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " Enter your guess: ";
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
			// assumed guess is valid
			break;
			
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK); //loop until the user gives a valid guess
	return Guess;
}

bool AskToPlayAgain()
{
	//Ask the player if they want to play again
	std::cout << "Do you want to play again with the same hidden word? (y/n) ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary() {
	if (BCGame.IsGameWon())	{
		std::cout << "You won!";
	}
	else{
		std::cout << "Better luck next time.";
	}
	std::cout << std::endl;
}