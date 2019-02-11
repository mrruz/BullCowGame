/* This is the console executable, that makes use of the BullCowClass
This acts as the view in a MVC pattern, and is responsible for all user interaction.
For game logic see the FBullCowGame class.

This was completed on 2019-02-11 as part of a Udemy Unreal course.
The source code is https://github.com/UnrealCourse/02_BullCowGame/tree/master/BullCowGame

Commits after 2019-02-11 are my own additions and changes to the game.

*/

#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

// For UE4 freindliness
using FText = std::string; 
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
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {        \___/ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n\n";
	return;
}

// Plays a single game to completion
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
		std::cout << "Try " << BCGame.GetCurrentTry() << " of " << BCGame.GetMaxTries() <<  ". Enter your guess: ";
		std::getline(std::cin, Guess);
		
		// check status and give feedback
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word. \n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters. \n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter your guess in lowercase letters. \n\n";
			break;
		default:
			// assumed guess is valid
			break;
			
		}
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
