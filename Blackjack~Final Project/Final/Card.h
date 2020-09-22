#ifndef Card_H
#define Card_H
#include <string>
using namespace std;

class Card {
public:
	Card(int suit_val, int face_val);
	~Card();
	string getSuit() const;
	string getFace() const;
	string printCard();
	void setValue();
	int getValue() const;
private:
	int face;
	int suit;
	int value;
	static string faces[13];
	static string suits[4];
};

#endif