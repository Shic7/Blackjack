#ifndef Deck_H
#define Deck_H
#include "Card.h"
#include <vector>
#include <string>
using namespace std;

class Deck
{
public:
	Deck();
	~Deck();
	void shuffle(); 
	void erase();
	Card begin();
protected:
	vector<Card> deck;
};
#endif