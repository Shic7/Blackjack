#include "Deck.h"
#include "Card.h"
#include <ctime>

//Creates Deck object
Deck::Deck() 
{
	for (int suit = 0; suit < 4; suit++) 
	{
		for (int face = 0; face < 13; face++) 
		{
			Card card(face, suit);
			deck.push_back(card);
		}
	}
}

//Destructs Deck object
Deck::~Deck()
{
	//empty
}

//Shuffles the deck of cards
void Deck::shuffle()
{
	srand(static_cast<unsigned int>(time(0)));

	for (int i = 0; i < 52; i++) 
	{
		int shuffle = (rand() % 52);
		Card card = deck[i];
		Card card2 = deck[shuffle];
		Card temp = card;
		deck[shuffle] = temp;
		deck[i] = card2;
	}
}

//Erases the first card in deck
void Deck::erase()
{
	deck.erase(deck.begin());
}

//Returns first card in deck
Card Deck::begin()
{
	Card topCard = deck[0];

	return topCard;
}
