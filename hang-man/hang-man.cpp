#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h> 
#include <cctype>

using namespace std;

string displayGame();
bool checkInput(char guess);
int lettersInWord(char guess, string word);
int guessCount = 0;

int incorrectGuesses = 0;
string guessedChars = "";
int const categories = 3;

char alphabet[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

int main()
{
	srand(time(NULL));

	string words[3][5] = { {"Drink", "milk", "sunnyd"}, {"Animals", "cow", "zebra"}, {"Food", "butter", "cheese"}};
	
	int categoryPicked = rand() % categories;
	int wordPicked = rand() % 2 + 1;
	
	string randWord = words[categoryPicked][wordPicked];
	string hideWord = "";
	string category = words[categoryPicked][0];

	for (int i = 0; i < randWord.length(); i++)
	{
		hideWord += "_";
	}

	bool gameOver = false;

	//starting the game
	while (!gameOver) {
		system("cls");
		cout << displayGame() << endl;
		cout << "Category: " << category << endl;
		cout << "Letters Guessed: " << guessedChars << endl;
		cout << "Incorrect Guesses: (" << incorrectGuesses << "/4)" << endl;
		bool flag = false;

		//displaying the hidden word with spaces
		cout << "\n    ";

		for (int i = 0; i < hideWord.length(); i++)
		{
			cout << hideWord[i] << " ";
		}

		cout << "\n";

		string guess = "";

		cin >> guess;

		//making sure the input is correct
		while (!checkInput(guess[0])) {
			cin >> guess;
		}

		guessedChars += " ";
		guessedChars += guess;

		for (int i = 0; i < randWord.length(); i++)
		{
			if (guess[0] == randWord[i]) {
				//so it doesn't repeat
				if (!flag) {
					cout << "There are " << lettersInWord(guess[0], randWord) << " " << guess << ((lettersInWord(guess[0], randWord)) > 1 ? "'s!" : ".") << endl;
				}

				flag = true;
				
				hideWord.erase(i, 1);
				hideWord.insert(i, guess);

				
				}
			else if (i == (randWord.length() - 1) && !flag) {

				cout << "incorrect guess!" << endl;
				incorrectGuesses++;
			}
		}

		if (hideWord == randWord || incorrectGuesses == 4) {
			gameOver = true;
		}

		system("pause");
	}
	
	//display game last time to see results
	system("cls");

	cout << displayGame() << endl;
	cout << "Letters Guessed: " << guessedChars << endl;
	cout << "Incorrect Guesses: (" << incorrectGuesses << "/4)" << endl;

	if (incorrectGuesses < 4) {
		cout << hideWord << endl;
		cout << "congrats, you win!!" << endl;
	}
	else {
		cout << "The word was: " << randWord << endl;
		cout << hideWord << endl;
		cout << "Game Over, you lost." << endl;
	}

	system("pause");
	return 0;
}

string displayGame() {
	string gameDisplay;

	switch (incorrectGuesses) {
	case 0:
		gameDisplay = "   --------\n   |      |\n   O      |\n   |      |\n          |\n         /-\\";
		break;
	case 1:
		gameDisplay = "   --------\n   |      |\n   O      |\n  /|      |\n          |\n         /-\\";
		break;
	case 2:
		gameDisplay = "   --------\n   |      |\n   O      |\n  /|\\     |\n          |\n         /-\\";
		break;
	case 3:
		gameDisplay = "   --------\n   |      |\n   O      |\n  /|\\     |\n  /       |\n         /-\\";
		break;
	case 4:
		gameDisplay = "   --------\n   |      |\n   O      |\n  /|\\     |\n  / \\     |\n         /-\\";
		break;
	}

	return gameDisplay;
}

bool checkInput(char guess) {
	bool flag = false;
	//checking if it was a letter
	for (int i = 0; i < 27; i++) 
		if (toupper(guess) == alphabet[i]) {
			flag = true;
		}
		else if (i == 26 && !flag) {
			cout << "Please enter a letter!" << endl;
		}
	
	
	//checking if it has been guessed before
	for (int i = 0; i < guessedChars.length(); i++)
		if (guess == guessedChars[i]) {
			flag = false;
			cout << "You already guessed " << guess << "!" << endl;
			break;
		}
	

	if (!flag) {
		return false;
	} else {
		return true;
	}
}


int lettersInWord(char guess, string word) {
	int letterCount = 0;
	
	for (int i = 0; i < word.length(); i++)
		if (guess == word[i]) {
			letterCount++;
		}

	return letterCount;
}