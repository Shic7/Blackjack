#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include "Dealer.h"
#include <iostream>
using namespace std;

int main()
{
	int numPlayers;

	cout << "WELCOME TO BLACKJACK!" << endl << endl;

	//Prompts user to enter number of Players
	do
	{
		cout << "Enter number of players (1-5): " << endl;
		cin >> numPlayers;

		if (numPlayers < 1 || numPlayers > 5)
		{
			cout << "Invalid: Number of players must be between 1-5." << endl << endl;
		}

	} while (numPlayers < 1 || numPlayers > 5);

	cout << endl;

	Player x { numPlayers, 0 };

	//Game begins
	game(x, numPlayers);

	cin.get();
	cin.get();

	return 0;
}