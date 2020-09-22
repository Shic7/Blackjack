#include "Card.h"
#include <iostream>
#include <string>

//Constructs Card object
Card::Card(int face_val, int suit_val) 
{
	suit = suit_val;
	face = face_val;
	setValue();
}

//Destructs Card object
Card::~Card()
{
	//empty
}

//Array of card face names
string Card::faces[13] = { "Ace","Two","Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };

//Array of card suit names
string Card::suits[4] = { "Clubs", "Diamonds", "Hearts", "Spades" };

//Returns the current card's face 
string Card::getFace() const
{
	return faces[face];
}

//Returns the current card's suit
string Card::getSuit() const
{
	return suits[suit];
}

//Prints the card's name
string Card::printCard() {

	string card = getFace() + " of " + getSuit();
	return card;
}

//Sets the value for each card
void Card::setValue()
{
	if (getFace() == "Ace")
		value = 11;

	else if (getFace() == "Two")
		value = 2;

	else if (getFace() == "Three")
		value = 3;

	else if (getFace() == "Four")
		value = 4;

	else if (getFace() == "Five")
		value = 5;

	else if (getFace() == "Six")
		value = 6;

	else if (getFace() == "Seven")
		value = 7;

	else if (getFace() == "Eight")
		value = 8;

	else if (getFace() == "Nine")
		value = 9;

	else if (getFace() == "Ten" || getFace() == "Jack" || getFace() == "Queen" || getFace() == "King")
		value = 10;
}

//Gets the value for card
int Card::getValue() const
{
	return value;
}