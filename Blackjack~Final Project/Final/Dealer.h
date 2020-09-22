#ifndef Dealer_H
#define Dealer_H
#include "Player.h"
#include "Card.h"
#include "Deck.h"

class Dealer : public Player
{
	friend void game(Player&, int);
public:
	~Dealer();
	void displayDealerAll();
	void dealCard(Player&, Deck&, int, int);
	void dealCardNew(Player&, Deck&, int);
	void dealCardDealer(Dealer&, Deck&);
	void giveCard(Card);
	void displayDealer();
	int getScore();
	void setHit();
	bool getHit();
	void drawCard(Deck&, int);
private:
	vector<Card> hand;
};
#endif