#include <iostream>
#include <string>

using namespace std;

void PrintIntro();
string GetGuess();
void PrintGuess(string Guess);

// Entry point for the application
int main()
{
	// introduce the game
	PrintIntro();
	
	//Get and Print back guess
	PrintGuess(GetGuess());
	// repeat the guess back to them
	


	cout << endl;
	system("pause");
	return 0;

}

void PrintIntro() {
	//Introduce the game
	constexpr int WORD_LENGTH = 9;
	cout << "Welcome to Bulls and Cows, a fun word game.\n";
	cout << "Can you guess the " << WORD_LENGTH;
	cout << " letter isogram I'm thinking of?\n";
	return;
}

string GetGuess() {
	// get a guess from the player
	cout << "Enter your guess: ";
	string Guess = "";
	getline(cin, Guess);
	return Guess;
}

void PrintGuess(string Guess) {
	cout << "You guessed: " << Guess;
}