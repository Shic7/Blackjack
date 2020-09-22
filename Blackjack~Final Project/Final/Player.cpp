#include "Player.h"
#include <iostream>
using namespace std;

//Constructs Player object
Player::Player()
{
	score = 0;
	hit = true;
}

//Constructs Player object
Player::Player(int playerNumber)
{
	playerNum = playerNumber;
	split = 0;
	nextHand = 1;
	balance = 1000;
}

//Constructs Player object
Player::Player(int x, int y)
{
	for (int i = 0; i < x; i++)
	{
		Player player(i);
		players.push_back(player);
	}
}

Player::~Player()
{
	//empty
}

//Array of Player Numbers
string Player::players1[5] = { "Player 1", "Player 2", "Player 3", "Player 4", "Player 5" };

//Gets the name of player
string Player::getName()
{
	return players1[playerNum];
}

//Sets the number of players
void Player::setNumberOfPlayers(int number)
{
	numberOfPlayers = number;
}

//Gets the number of players
int Player::getNumberOfPlayers() const
{
	return numberOfPlayers;
}

//Gives the player a card
void Player::giveCard(Card topCard, int i)
{	
	hands[i].push_back(topCard);
}

//Give the player a card to their new hand (split)
void Player::giveCardNew(Card topCard)
{	
	hits[nextHand] = true;

	hands[nextHand++].push_back(topCard);
}

//Gets split count
int Player::getSplit(int i)
{
	return players[i].split;
}

//Splits the player's hand
void Player::splitHand(int i, int j) //would you like to split?
{
	vector<Card> topCard = players[i].hands[j];
	Card card = topCard[1];

	players[i].hands[j].erase(players[i].hands[j].begin()+1);

	players[i].hands[players[i].nextHand].push_back(card);
	
	players[i].split++;
}

//Deals card to player
void Player::dealCardPlayer(Card& topCard, int i, int j)
{
	players[i].giveCard(topCard, j);
}

////Deals card to player's new hand (split)
void Player::dealCardPlayerNew(Card& topCard, int i)
{
	players[i].giveCardNew(topCard);
}

//Shows current player
Player Player::showPlayer(int i) const
{
	Player p = players[i];

	return p;
}

//Sets the player's balances
void Player::setBalance(float bal, int i)
{
	players[i].balance = bal;
}

//Gets the player's balances
float Player::getBalance(int i)
{
	return players[i].balance;
}

//Gets the player's score
int Player::getScore(int j) 
{ 
	int sum = 0; 

	for (vector<Card>::iterator i = hands[j].begin(); i != hands[j].end(); ++i)
	{
		sum += i->getValue();
	}

	//ACE can count as an 11 or a 1
	for (vector<Card>::iterator i = hands[j].begin(); i != hands[j].end(); ++i)
	{
		if (sum > 21)
		{
			if (i->getValue() == 11)
			{
				sum = sum - 10;
			}
		}
	}

	return sum;
}

//Checks if the player has a pair
bool Player::checkPair(int i)
{
	int value1 = (hands[i].begin())->getValue();
	int value2 = (hands[i].end()-1)->getValue();

	if (value1 == value2)
		return true;

	else
		return false;
}

//Sets the player's bet
void Player::setBet(float x, int i, int j)
{
	players[i].bets[j] = x;
}

//Gets the player's bet
float Player::getBet(int i, int j)
{
	return players[i].bets[j];
}

//Displays the player's current hand
void Player::display(int j)
{
	if (j == 0)
	{
		for (vector<Card>::iterator i = hands[0].begin(); i != hands[0].end(); ++i)
		{
			cout << i->printCard() << endl;
		}
	}

	if (j == 1)
	{
		for (vector<Card>::iterator i = hands[1].begin(); i != hands[1].end(); ++i)
		{
			cout << i->printCard() << endl;
		}
	}

	if (j == 2)
	{
		for (vector<Card>::iterator i = hands[2].begin(); i != hands[2].end(); ++i)
		{
			cout << i->printCard() << endl;
		}
	}
	
	if (j == 3)
	{
		for (vector<Card>::iterator i = hands[3].begin(); i != hands[3].end(); ++i)
		{
			cout << i->printCard() << endl;
		}
	}
} 

//Draw's a card from the deck
void Player::drawCard(Deck& deck1, int input, int i, int j) ///////////
{ 

	if (input == 1)
	{
		Card handCard = deck1.begin();
		
		cout << endl;

		cout << showPlayer(i).getName() << " took out: " << handCard.printCard() << endl;

		players[i].hands[j].push_back(handCard);
		deck1.erase();
	}

	else
		players[i].hits[j] = false; 
}

//Checks if player still wants to hit
bool Player::getHit(int j) 
{
	return hits[j];
}

//Sets whether the player would still like to 'hit'
void Player::setHit(int i, int j, int k)
{
	if(k == 1)
		players[i].hits[j] = true;

	else
		players[i].hits[j] = false;
}

//Sets whether player surrendered or busted
void Player::setSurrender(int i, int j, int k)
{	
	if(k == 1)
		players[i].surrender[j] = true;

	else 
		players[i].surrender[j] = false;
}

//Gets player's surrender/bust status
bool Player::getSurrender(int i, int j) const
{
	return players[i].surrender[j];
}

//Normal prompt for first turn
void Player::firstTurnPrompt(Deck& gameDeck, int i, int j)
{
	int input;

	cout << showPlayer(i).getName() << "'s Current Hand: " << endl;
	showPlayer(i).display(j);
	cout << endl;

	do
	{
		cout << showPlayer(i).getName() << ", press (1) to 'hit', (2) to 'stand', (3) to 'double down', or (4) to 'surrender' for current hand." << endl;
		cin >> input;

		if (input < 1 || input > 4)
			cout << "Invalid input." << endl << endl;

	} while (input < 1 || input > 4);

	if (input == 1 || input == 2)
	{
		drawCard(gameDeck, input, i, j);

		cout << endl;

		if (input != 2 && input != 4)
		{
			cout << showPlayer(i).getName() << "'s Updated Current Hand: " << endl;
			showPlayer(i).display(j);
			cout << endl;
		}

		if (showPlayer(i).getScore(j) > 21)
		{
			cout << showPlayer(i).getName() << "'s current hand busts!" << endl;
			drawCard(gameDeck, 0, i, j);
			setSurrender(i, j, 1);
			balance = getBalance(i) - getBet(i, j);
			setBalance(balance, i);
			cout << showPlayer(i).getName() << " loses $" << getBet(i, j) << endl;
			cout << showPlayer(i).getName() << "'s balance is $" << getBalance(i) << endl << endl;
		}
	}

	if (input == 3) //double down
	{
		setBet(getBet(i, j) * 2, i, j);

		drawCard(gameDeck, 1, i, j);

		drawCard(gameDeck, 0, i, j);

		if (input != 2 && input != 4)
		{
			cout << endl;
			cout << showPlayer(i).getName() << "'s Updated Current Hand: " << endl;
			showPlayer(i).display(j);
			cout << endl;
		}

		if (showPlayer(i).getScore(j) > 21)
		{
			cout << showPlayer(i).getName() << "'s current hand busts!" << endl;
			setSurrender(i, 0, 1);
			balance = getBalance(i) - getBet(i, j);
			setBalance(balance, i);
			cout << showPlayer(i).getName() << " loses $" << getBet(i, j) << endl;
			cout << showPlayer(i).getName() << "'s balance is $" << getBalance(i) << endl << endl;
		}
	}

	else if (input == 4) //surrender
	{
		cout << endl;

		drawCard(gameDeck, 0, i, j);

		setBet(getBet(i, 0) / 2, i, j);

		setSurrender(i, j, 1);

		cout << showPlayer(i).getName() << " surrenders!" << endl;

		balance = getBalance(i) - getBet(i, j);
		setBalance(balance, i);
		cout << showPlayer(i).getName() << " loses $" << getBet(i, j) << endl;
		cout << showPlayer(i).getName() << "'s balance is $" << getBalance(i) << endl << endl;
	}
}

//Split version of first turn prompt
void Player::firstTurnPromptSplit(Deck& gameDeck, int i, int input, int j)
{
	if (input == 1 || input == 2)
	{
		drawCard(gameDeck, input, i, j);

		cout << endl;

		if (input != 2 && input != 4 && input != 5)
		{
			cout << showPlayer(i).getName() << "'s Updated Current Hand: " << endl;
			showPlayer(i).display(j);
			cout << endl;
		}

		if (showPlayer(i).getScore(j) > 21)
		{
			cout << showPlayer(i).getName() << "'s current hand busts!" << endl;
			drawCard(gameDeck, 0, i, j);
			setSurrender(i, j, 1);
			balance = getBalance(i) - getBet(i, j);
			setBalance(balance, i);
			cout << showPlayer(i).getName() << " loses $" << getBet(i, j) << endl;
			cout << showPlayer(i).getName() << "'s balance is $" << getBalance(i) << endl << endl;
		}
	}

	if (input == 3) //double down
	{
		setBet(getBet(i, j) * 2, i, j);

		drawCard(gameDeck, 1, i, j);

		drawCard(gameDeck, 0, i, j);

		if (input != 2 && input != 4 && input != 5)
		{
			cout << endl;
			cout << showPlayer(i).getName() << "'s Updated Current Hand: " << endl;
			showPlayer(i).display(j);
			cout << endl;
		}

		if (showPlayer(i).getScore(j) > 21)
		{
			cout << showPlayer(i).getName() << "'s current hand busts!" << endl;
			setSurrender(i, 0, 1);
			balance = getBalance(i) - getBet(i, j);
			setBalance(balance, i);
			cout << showPlayer(i).getName() << " loses $" << getBet(i, j) << endl;
			cout << showPlayer(i).getName() << "'s balance is $" << getBalance(i) << endl << endl;
		}
	}

	else if (input == 4) //surrender
	{
		cout << endl; 

		drawCard(gameDeck, 0, i, j);

		setBet(getBet(i, 0) / 2, i, j);

		setSurrender(i, j, 1);

		cout << showPlayer(i).getName() << " surrenders!" << endl;

		balance = getBalance(i) - getBet(i, j);
		setBalance(balance, i);
		cout << showPlayer(i).getName() << " loses $" << getBet(i, j) << endl;
		cout << showPlayer(i).getName() << "'s balance is $" << getBalance(i) << endl << endl;
	}
}

//Checks if player has a blackjack
bool Player::checkBlackjack(Deck& gameDeck, int i, int j)
{
	if (showPlayer(i).getScore(j) == 21)
	{
		cout << showPlayer(i).getName() << "'s current hand has a BlackJack!" << endl;
		cout << "Dealer does not have a Blackjack!" << endl;
		cout << showPlayer(i).getName() << "'s current hand wins!" << endl;
		drawCard(gameDeck, 0, i, j);
		setSurrender(i, j, 1); 
		setBet(float(getBet(i, 0)*1.5), i, j);
		balance = getBalance(i) + getBet(i, j);
		setBalance(balance, i);
		cout << showPlayer(i).getName() << " wins $" << getBet(i, j) << "." << endl;
		cout << showPlayer(i).getName() << "'s balance is $" << getBalance(i) << "." << endl << endl;

		return true;
	}

	else
		return false;
}

//Prompt to be used after first turn
void Player::standardPrompt(Deck& gameDeck, int i, int j)
{
	int input; 

	if (showPlayer(i).getHit(j) == true)
	{
		cout << showPlayer(i).getName() << "'s Current Hand: " << endl;
		showPlayer(i).display(j);
		cout << endl;

		do
		{
			cout << showPlayer(i).getName() << ", would you like to 'hit' or 'stand'? Press (1) for 'hit' or (2) for 'stand' for current hand." << endl;
			cin >> input;

			if (input < 1 || input > 2)
				cout << "Invalid input." << endl;

		} while (input < 1 || input > 2);

		drawCard(gameDeck, input, i, j);

		if (input != 2)
		{
			cout << endl;
			cout << showPlayer(i).getName() << "'s Updated Current Hand: " << endl;
			showPlayer(i).display(j);
		}

		cout << endl;

		if (showPlayer(i).getScore(j) > 21)
		{
			cout << showPlayer(i).getName() << "'s current hand busts!" << endl;
			drawCard(gameDeck, 0, i, j);
			setSurrender(i, j, 1);
			balance = getBalance(i) - getBet(i, j);
			setBalance(balance, i);
			cout << showPlayer(i).getName() << " loses $" << getBet(i, j) << endl;
			cout << showPlayer(i).getName() << "'s balance is $" << getBalance(i) << endl << endl;
		}
	}
}

//Clears the hand of all players
void Player::clearHand(int i, int j)
{
	players[i].hands[j].clear();
}

//Overloaded operator<< to show player's scores that are still in the game
ostream& operator<<(ostream& output, const Player& x)
{
	for (int i = 0; i < x.getNumberOfPlayers(); i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (x.getSurrender(i, j) == false && x.showPlayer(i).getScore(j) > 0)
				output << x.showPlayer(i).getName() << "'s Score: " << x.showPlayer(i).getScore(j) << endl;
		}
	}

	return output;
}
