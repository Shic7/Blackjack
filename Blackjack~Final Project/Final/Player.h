#ifndef Player_H
#define Player_H
#include "Deck.h"
#include <array>

class Player
{
	friend std::ostream& operator<<(std::ostream&, const Player&);
public:
	Player();
	Player(int);
	Player(int, int);
	~Player();
	void setNumberOfPlayers(int);
	int getNumberOfPlayers() const;
	float getBalance(int);
	void setBalance(float, int);
	int getScore(int);
	void setBet(float, int ,int);
	float getBet(int, int);
	void giveCard(Card, int);
	void giveCardNew(Card);
	void drawCard(Deck&, int, int, int); 
	void display(int);
	bool getHit(int);
	void setHit(int, int, int);
	Player showPlayer(int) const;
	string getName();
	void dealCardPlayer(Card&, int, int);
	void dealCardPlayerNew(Card&, int);
	void setSurrender(int, int, int);
	bool getSurrender(int, int) const;
	bool checkPair(int);
	void splitHand(int, int);
	int getSplit(int);
	void firstTurnPrompt( Deck&, int, int);
	void firstTurnPromptSplit(Deck&, int, int, int);
	bool checkBlackjack(Deck&, int, int);
	void standardPrompt(Deck&, int, int);
	void clearHand(int, int);
protected:
	int playerNum;
	int numberOfPlayers;
	bool hit;
	float balance;
	int score;
	int nextHand;
	int split;
	vector<Player> players;
	array<bool, 4> hits{ true };
	array<bool, 4> surrender;
	array<float, 4> bets;
	array<vector<Card>, 4> hands;
	static string players1[5];
};
#endif