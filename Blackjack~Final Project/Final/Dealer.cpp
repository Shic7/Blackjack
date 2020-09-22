#include "Dealer.h"
#include <vector>
#include <iostream>
#include <iomanip>  
using namespace std;

Dealer::~Dealer()
{
	//empty
}

//Sets Dealer's hit status
void Dealer::setHit()
{
	hit = false;
}

//Gets Dealer's hit status
bool Dealer::getHit()
{
	return hit;
}

//Dealer deals card to players
void Dealer::dealCard(Player& player, Deck& deck1, int i, int j)
{
	Card topCard = deck1.begin();

	deck1.erase();

	player.dealCardPlayer(topCard, i, j);
}

//Dealer deals cards to players (split)
void Dealer::dealCardNew(Player& player, Deck& deck1, int i)
{
	Card topCard = deck1.begin();

	deck1.erase();

	player.dealCardPlayerNew(topCard, i);
}

//Dealer deals themself a card
void Dealer::dealCardDealer(Dealer& dealer, Deck& deck1)
{
	Card topCard = deck1.begin();

	deck1.erase();

	dealer.giveCard(topCard);
}

//Gives card to Dealer
void Dealer::giveCard(Card topCard)
{
	hand.push_back(topCard);
}

//Gets Dealer's score
int Dealer::getScore()
{
	int sum = 0;

	for (vector<Card>::iterator i = hand.begin(); i != hand.end(); ++i)
	{
		sum += i->getValue();
	}

	for (vector<Card>::iterator i = hand.begin(); i != hand.end(); ++i)
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

//Displays Dealer's hand with first card hidden
void Dealer::displayDealer()
{
	for (vector<Card>::iterator i = hand.begin() + 1; i != hand.end(); ++i)
	{
		cout << i->printCard() << endl;
	}
}

//Displays Dealer's entire hand
void Dealer::displayDealerAll()
{
	for (vector<Card>::iterator i = hand.begin(); i != hand.end(); ++i)
	{
		cout << i->printCard() << endl;
	}
}

//Dealer draws card
void Dealer::drawCard(Deck& deck1, int input)
{
	if (input == 1)
	{
		Card handCard = deck1.begin();

		cout << "Dealer took out: " << handCard.printCard() << endl << endl;

		cout << "Dealer's Updated Hand: " << endl;

		cout << "(Hidden Card)" << endl;

		hand.push_back(handCard);
		deck1.erase();
	}

	else
		hit = false;
}

//Contains the entire game
void game(Player& x, int size)
{
	float bet;
	int input;
	float balance;
	int gameFlag = 0;

	x.setNumberOfPlayers(size);

	cout << fixed << setprecision(2);

	do
	{
		Deck gameDeck;
		Dealer dealer;
		int stopFlag = 0;
		int blackjackFlag = 0;

		gameDeck.shuffle();


		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				x.setSurrender(i, j, 0);
				x.setHit(i, j, 0);
			}
		}

		for (int i = 0; i < size; i++)
		{
			x.setHit(i, 0, 1);
		}

		for (int i = 0; i < size; i++)
		{
			do
			{
				cout << "Enter bet amount for " << x.showPlayer(i).getName() << ":" << endl;
				cin >> bet;

				if (bet < 5 || bet > 100)
					cout << "Invalid input: bet must be between $5 to $100." << endl;

				cout << endl;

			} while (bet < 5 || bet > 100);

			x.setBet(bet, i, 0);
			cout << x.showPlayer(i).getName() << "'s bet is $" << x.getBet(i, 0) << endl << endl;
		}

		//Starts dealing cards
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < size; j++)
			{
				dealer.dealCard(x, gameDeck, j, 0); 
			}

			dealer.dealCardDealer(dealer, gameDeck);
		}

		for (int i = 0; i < size; i++)
		{
			cout << x.showPlayer(i).getName() << "'s Cards: " << endl;
			x.showPlayer(i).display(0);
			cout << endl;
		}

		cout << "Dealer's Cards: " << endl;
		cout << "(Hidden Card)" << endl;
		dealer.displayDealer();
		cout << endl;

		//Checks blackjack at beginning
		if (dealer.getScore() == 21)
		{
			cout << "Dealer has a Blackjack!" << endl << endl;

			cout << "All of Dealer's Cards Revealed: " << endl;

			dealer.displayDealerAll();

			cout << endl;

			for (int i = 0; i < size; i++)
			{
				if (x.showPlayer(i).getScore(0) == 21)
				{
					cout << x.showPlayer(i).getName() << " has a Blackjack!" << endl;
					cout << x.showPlayer(i).getName() << " and Dealer have a tie!" << endl << endl;
				}

				else
				{
					cout << x.showPlayer(i).getName() << " does not have a Blackjack." << endl;
					balance = x.getBalance(i) - x.getBet(i, 0);
					x.setBalance(balance, i);
					cout << x.showPlayer(i).getName() << " loses $" << x.getBet(i, 0) << endl;
					cout << x.showPlayer(i).getName() << "'s balance is $" << x.getBalance(i) << endl << endl;
				}
			}

			stopFlag = 1;
		}

		if (stopFlag == 0)
		{	
			for (int i = 0; i < size; i++)
				{
					for (int i = 0; i < size; i++)
					{
						for (int j = 0; j < 4; j++)
						{	
							if (x.showPlayer(i).getHit(j) == true)
							{
								if (x.checkBlackjack(gameDeck, i, j) == false)
								{
									blackjackFlag = 1;
								}
							}
						}
					}

					if (blackjackFlag == 0)
					{
						break;
					}
					
					int newHand = 1;

					//If Player's hand has a pair
					if (x.showPlayer(i).checkPair(0) == true && x.showPlayer(i).getHit(0) == true) 
					{ 
						cout << x.showPlayer(i).getName() << "'s Current Hand: " << endl;
						x.showPlayer(i).display(0);
						cout << endl;

						do
						{
							cout << x.showPlayer(i).getName() << ", press (1) to 'hit', (2) to 'stand', (3) to 'double down', (4) to 'surrender', or (5) to 'split'." << endl;
							cin >> input;

							if (input < 1 || input > 5)
								cout << "Invalid input." << endl;

						} while (input < 1 || input > 5);

						x.firstTurnPromptSplit(gameDeck, i, input, 0);

						if (input == 5) 
						{
							x.splitHand(i, 0);

							dealer.dealCard(x, gameDeck, i, 0);
							dealer.dealCardNew(x, gameDeck, i); 

							x.setBet(x.getBet(i, 0), i, newHand);

							newHand++;

							cout << endl;
							cout << "New Hand: " << endl;
							x.showPlayer(i).display(0); 
							cout << endl;
							cout << "Next New Hand: " << endl;
							x.showPlayer(i).display(1);
							cout << endl;

							for (int i = 0; i < size; i++)
							{
								for (int j = 0; j < 4; j++)
								{
									if (x.showPlayer(i).getHit(j) == true && x.showPlayer(i).getScore(j) == 21)
									{
										cout << x.showPlayer(i).getName() << "'s Current Hand: " << endl;
										x.showPlayer(i).display(j);
										cout << endl;

										if (x.checkBlackjack(gameDeck, i, j) == false)
										{
											blackjackFlag = 1;
										}
									}
								}
							}

							if (blackjackFlag == 0)
							{
								break;
							}

							if (x.showPlayer(i).checkPair(0) == false && x.showPlayer(i).getHit(0) == true)
							{
								x.firstTurnPrompt(gameDeck, i, 0);

							}

							else if (x.showPlayer(i).checkPair(0) == true && x.showPlayer(i).getHit(0) == true)
							{
								cout << endl;
								cout << x.showPlayer(i).getName() << "'s Current Hand: " << endl;
								x.showPlayer(i).display(0);
								cout << endl;

								do
								{
									cout << x.showPlayer(i).getName() << ", press (1) to 'hit', (2) to 'stand', (3) to 'double down', (4) to 'surrender', or (5) to 'split' for current hand." << endl;
									cin >> input;

									if (input < 1 || input > 5)
										cout << "Invalid input." << endl;

								} while (input < 1 || input > 5);

								x.firstTurnPromptSplit(gameDeck, i, input, 0);

								if (input == 5)
								{
									x.splitHand(i, 0);
									dealer.dealCard(x, gameDeck, i, 0); 
									dealer.dealCardNew(x, gameDeck, i);

									x.setBet(x.getBet(i, 0), i, newHand);

									newHand++;

									cout << endl;
									cout << "New Hand: " << endl;
									x.showPlayer(i).display(0); 
									cout << endl;
									cout << "Next New Hand: " << endl;
									x.showPlayer(i).display(2);
									cout << endl;

									for (int i = 0; i < size; i++)
									{
										for (int j = 0; j < 4; j++)
										{
											if (x.showPlayer(i).getHit(j) == true && x.showPlayer(i).getScore(j) == 21)
											{
												cout << x.showPlayer(i).getName() << "'s Current Hand: " << endl;
												x.showPlayer(i).display(j);
												cout << endl;

												if (x.checkBlackjack(gameDeck, i, j) == false)
												{
													blackjackFlag = 1;
												}
											}
										}
									}

									if (blackjackFlag == 0)
									{
										break;
									}

									if (x.showPlayer(i).checkPair(0) == false && x.showPlayer(i).getHit(0) == true)
									{
										x.firstTurnPrompt(gameDeck, i, 0);
									}

									else if (x.showPlayer(i).checkPair(0) == true && x.showPlayer(i).getHit(0) == true) 
									{
										cout << endl;
										cout << x.showPlayer(i).getName() << "'s Current Hand: " << endl;
										x.showPlayer(i).display(0);
										cout << endl;

										do
										{
											cout << x.showPlayer(i).getName() << ", press (1) to 'hit', (2) to 'stand', (3) to 'double down', (4) to 'surrender', or (5) to 'split' for current hand." << endl;
											cin >> input;

											if (input < 1 || input > 5)
												cout << "Invalid input." << endl;

										} while (input < 1 || input > 5);

										x.firstTurnPromptSplit(gameDeck, i, input, 0);

										if (input == 5)
										{
											x.splitHand(i, 0);
											dealer.dealCard(x, gameDeck, i, 0); 
											dealer.dealCardNew(x, gameDeck, i);

											x.setBet(x.getBet(i, 0), i, newHand);

											newHand++;

											cout << endl;
											cout << "New Hand: " << endl;
											x.showPlayer(i).display(0); 
											cout << endl;
											cout << "Next New Hand: " << endl;
											x.showPlayer(i).display(3);
											cout << endl;

											for (int i = 0; i < size; i++)
											{
												for (int j = 0; j < 4; j++)
												{
													if (x.showPlayer(i).getHit(j) == true && x.showPlayer(i).getScore(j) == 21)
													{
														cout << x.showPlayer(i).getName() << "'s Current Hand: " << endl;
														x.showPlayer(i).display(j);
														cout << endl;

														if (x.checkBlackjack(gameDeck, i, j) == false)
														{
															blackjackFlag = 1;
														}
													}
												}
											}

											if (blackjackFlag == 0)
											{
												break;
											}

											if (x.getSurrender(i, 0) == false && x.showPlayer(i).getScore(0) > 0 && x.showPlayer(i).getHit(0) == true)
											{
												x.firstTurnPrompt(gameDeck, i, 0);
											}

											if (x.getSurrender(i, 3) == false && x.showPlayer(i).getScore(3) > 0 && x.showPlayer(i).getHit(3) == true)
											{
												x.firstTurnPrompt(gameDeck, i, 3);
											}

											if (x.getSurrender(i, 1) == false && x.showPlayer(i).getScore(1) > 0 && x.showPlayer(i).getHit(1) == true)
											{
												x.firstTurnPrompt(gameDeck, i, 1);
											}

											if (x.getSurrender(i, 2) == false && x.showPlayer(i).getScore(2) > 0 && x.showPlayer(i).getHit(2) == true)
											{
												x.firstTurnPrompt(gameDeck, i, 2);
											}
										}
									}

									if (x.showPlayer(i).checkPair(2) == false && x.showPlayer(i).getHit(2) == true)
									{
										x.firstTurnPrompt(gameDeck, i, 2);

									}

									else if (x.showPlayer(i).checkPair(2) == true && x.getSplit(i) < 3 && x.showPlayer(i).getHit(2) == true)
									{
										cout << endl;
										cout << x.showPlayer(i).getName() << "'s Current Hand: " << endl;
										x.showPlayer(i).display(2);
										cout << endl;

										do
										{
											cout << x.showPlayer(i).getName() << ", press (1) to 'hit', (2) to 'stand', (3) to 'double down', (4) to 'surrender', or (5) to 'split' for current hand." << endl;
											cin >> input;

											if (input < 1 || input > 5)
												cout << "Invalid input." << endl;

										} while (input < 1 || input > 5);

										x.firstTurnPromptSplit(gameDeck, i, input, 2);

										if (input == 5)
										{
											x.splitHand(i, 2);
											dealer.dealCard(x, gameDeck, i, 2);
											dealer.dealCardNew(x, gameDeck, i);

											x.setBet(x.getBet(i, 0), i, newHand);

											newHand++;

											cout << endl;
											cout << "New Hand: " << endl;
											x.showPlayer(i).display(2); 
											cout << endl;
											cout << "Next New Hand: " << endl;
											x.showPlayer(i).display(3);
											cout << endl;

											for (int i = 0; i < size; i++)
											{
												for (int j = 0; j < 4; j++)
												{
													if (x.showPlayer(i).getHit(j) == true && x.showPlayer(i).getScore(j) == 21)
													{
														cout << x.showPlayer(i).getName() << "'s Current Hand: " << endl;
														x.showPlayer(i).display(j);
														cout << endl;

														if (x.checkBlackjack(gameDeck, i, j) == false)
														{
															blackjackFlag = 1;
														}
													}
												}
											}

											if (blackjackFlag == 0)
											{
												break;
											}

											if (x.getSurrender(i, 2) == false && x.showPlayer(i).getScore(2) > 0 && x.showPlayer(i).getHit(2) == true)
											{
												x.firstTurnPrompt(gameDeck, i, 2);
											}

											if (x.getSurrender(i, 3) == false && x.showPlayer(i).getScore(3) > 0 && x.showPlayer(i).getHit(3) == true)
											{
												x.firstTurnPrompt(gameDeck, i, 3);
											}

											if (x.getSurrender(i, 0) == false && x.showPlayer(i).getScore(0) > 0 && x.showPlayer(i).getHit(0) == true)
											{
												x.firstTurnPrompt(gameDeck, i, 0);
											}

											if (x.getSurrender(i, 1) == false && x.showPlayer(i).getScore(1) > 0 && x.showPlayer(i).getHit(1) == true)
											{
												x.firstTurnPrompt(gameDeck, i, 1);
											}
										}
									}
								}
							}

							if (x.showPlayer(i).checkPair(1) == false && x.showPlayer(i).getHit(1) == true)
							{
								x.firstTurnPrompt(gameDeck, i, 1);
							}

							else if (x.showPlayer(i).checkPair(1) == true && x.getSplit(i) < 3)
							{
								cout << endl;
								cout << x.showPlayer(i).getName() << "'s Current Hand: " << endl;
								x.showPlayer(i).display(1);
								cout << endl;

								do
								{
									cout << x.showPlayer(i).getName() << ", press (1) to 'hit', (2) to 'stand', (3) to 'double down', (4) to 'surrender', or (5) to 'split' for current hand." << endl;
									cin >> input;

									if (input < 1 || input > 5)
										cout << "Invalid input." << endl;

								} while (input < 1 || input > 5);

								x.firstTurnPromptSplit(gameDeck, i, input, 1);

								if (input == 5)
								{
									x.splitHand(i, 1);
									dealer.dealCard(x, gameDeck, i, 1); 
									dealer.dealCardNew(x, gameDeck, i);

									x.setBet(x.getBet(i, 0), i, newHand);

									newHand++;

									cout << endl;
									cout << "New Hand: " << endl;
									x.showPlayer(i).display(1); 
									cout << endl;
									cout << "Next New Hand: " << endl;
									x.showPlayer(i).display(2);
									cout << endl;

									for (int i = 0; i < size; i++)
									{
										for (int j = 0; j < 4; j++)
										{
											if (x.showPlayer(i).getHit(j) == true && x.showPlayer(i).getScore(j) == 21)
											{
												cout << x.showPlayer(i).getName() << "'s Current Hand: " << endl;
												x.showPlayer(i).display(j);
												cout << endl;

												if (x.checkBlackjack(gameDeck, i, j) == false)
												{
													blackjackFlag = 1;
												}
											}
										}
									}

									if (blackjackFlag == 0)
									{
										break;
									}

									if (x.showPlayer(i).checkPair(1) == false && x.showPlayer(i).getHit(1) == true)
									{
										x.firstTurnPrompt(gameDeck, i, 1);
									}

									else if (x.showPlayer(i).checkPair(1) == true && x.getSplit(i) < 3 && x.showPlayer(i).getHit(1) == true) 
									{
										cout << endl;
										cout << x.showPlayer(i).getName() << "'s Current Hand: " << endl;
										x.showPlayer(i).display(1);
										cout << endl;

										do
										{
											cout << x.showPlayer(i).getName() << ", press (1) to 'hit', (2) to 'stand', (3) to 'double down', (4) to 'surrender', or (5) to 'split' for current hand." << endl;
											cin >> input;

											if (input < 1 || input > 5)
												cout << "Invalid input." << endl;

										} while (input < 1 || input > 5);

										x.firstTurnPromptSplit(gameDeck, i, input, 1);

										if (input == 5)
										{
											x.splitHand(i, 1);
											dealer.dealCard(x, gameDeck, i, 1); 
											dealer.dealCardNew(x, gameDeck, i);

											x.setBet(x.getBet(i, 0), i, newHand);

											newHand++;

											cout << endl;
											cout << "New Hand: " << endl;
											x.showPlayer(i).display(1); 
											cout << endl;
											cout << "Next New Hand: " << endl;
											x.showPlayer(i).display(3);
											cout << endl;

											for (int i = 0; i < size; i++)
											{
												for (int j = 0; j < 4; j++)
												{
													if (x.showPlayer(i).getHit(j) == true && x.showPlayer(i).getScore(j) == 21)
													{
														cout << x.showPlayer(i).getName() << "'s Current Hand: " << endl;
														x.showPlayer(i).display(j);
														cout << endl;

														if (x.checkBlackjack(gameDeck, i, j) == false)
														{
															blackjackFlag = 1;
														}
													}
												}
											}

											if (blackjackFlag == 0)
											{
												break;
											}

											if (x.getSurrender(i, 1) == false && x.showPlayer(i).getScore(1) > 0 && x.showPlayer(i).getHit(1) == true)
											{
												x.firstTurnPrompt(gameDeck, i, 1);
											}

											if (x.getSurrender(i, 3) == false && x.showPlayer(i).getScore(3) > 0 && x.showPlayer(i).getHit(3) == true)
											{
												x.firstTurnPrompt(gameDeck, i, 3);
											}

											if (x.getSurrender(i, 0) == false && x.showPlayer(i).getScore(0) > 0 && x.showPlayer(i).getHit(0) == true)
											{
												x.firstTurnPrompt(gameDeck, i, 0);
											}

											if (x.getSurrender(i, 2) == false && x.showPlayer(i).getScore(2) > 0 && x.showPlayer(i).getHit(2) == true)
											{
												x.firstTurnPrompt(gameDeck, i, 2);
											}
										}
									}

									if (x.showPlayer(i).checkPair(2) == false && x.showPlayer(i).getHit(2) == true)
									{
										x.firstTurnPrompt(gameDeck, i, 2);

									}

									else if (x.showPlayer(i).checkPair(2) == true && x.getSplit(i) < 3 && x.showPlayer(i).getHit(3) == true)
									{
										cout << endl;
										cout << x.showPlayer(i).getName() << "'s Current Hand: " << endl;
										x.showPlayer(i).display(2);
										cout << endl;

										do
										{
											cout << x.showPlayer(i).getName() << ", press (1) to 'hit', (2) to 'stand', (3) to 'double down', (4) to 'surrender', or (5) to 'split' for current hand." << endl;
											cin >> input;

											if (input < 1 || input > 5)
												cout << "Invalid input." << endl;

										} while (input < 1 || input > 5);

										x.firstTurnPromptSplit(gameDeck, i, input, 2); 

										if (input == 5)
										{
											x.splitHand(i, 2);
											dealer.dealCard(x, gameDeck, i, 2); 
											dealer.dealCardNew(x, gameDeck, i);

											x.setBet(x.getBet(i, 0), i, newHand);

											newHand++;

											cout << endl;
											cout << "New Hand: " << endl;
											x.showPlayer(i).display(2); 
											cout << endl;
											cout << "Next New Hand: " << endl;
											x.showPlayer(i).display(3);
											cout << endl;

											for (int i = 0; i < size; i++)
											{
												for (int j = 0; j < 4; j++)
												{
													if (x.showPlayer(i).getHit(j) == true && x.showPlayer(i).getScore(j) == 21)
													{
														cout << x.showPlayer(i).getName() << "'s Current Hand: " << endl;
														x.showPlayer(i).display(j);
														cout << endl;

														if (x.checkBlackjack(gameDeck, i, j) == false)
														{
															blackjackFlag = 1;
														}
													}
												}
											}

											if (blackjackFlag == 0)
											{
												break;
											}

											if (x.getSurrender(i, 2) == false && x.showPlayer(i).getScore(2) > 0 && x.showPlayer(i).getHit(2) == true)
											{
												x.firstTurnPrompt(gameDeck, i, 2);
											}

											if (x.getSurrender(i, 3) == false && x.showPlayer(i).getScore(3) > 0 && x.showPlayer(i).getHit(3) == true)
											{
												x.firstTurnPrompt(gameDeck, i, 3);
											}

											if (x.getSurrender(i, 0) == false && x.showPlayer(i).getScore(0) > 0 && x.showPlayer(i).getHit(0) == true)
											{
												x.firstTurnPrompt(gameDeck, i, 0);
											}

											if (x.getSurrender(i, 1) == false && x.showPlayer(i).getScore(1) > 0 && x.showPlayer(i).getHit(1) == true)
											{
												x.firstTurnPrompt(gameDeck, i, 1);
											}
										}
									}
								}
							}
						}
					}

					//Player did not have a pair
					else
					{
						if(x.showPlayer(i).getHit(0) == true)
							x.firstTurnPrompt(gameDeck, i, 0);
					}
				}

			int surrenderFlag = 0;
			
			//Proceeds to play game after first turns are done
			for (int i = 0; i < size; i++)
				{
					for (int j = 0; j < 4; j++)
					{
						if (x.getSurrender(i, j) == false && x.showPlayer(i).getScore(j) > 0)
						{
							surrenderFlag = 1;
							break;
						}
					}
				}

			if (surrenderFlag == 0)
				{
					cout << "No players remaining!" << endl << endl;
					stopFlag = 1;
				}

			if (stopFlag == 0)
				{
					if (dealer.getScore() <= 16)
					{
						cout << "Dealer chose to 'hit'." << endl;
						dealer.drawCard(gameDeck, 1);
						dealer.displayDealer();
						cout << endl;

						if (dealer.getScore() > 21)
						{
							cout << "Dealer Busts! All remaining players win!" << endl << endl;

							for (int i = 0; i < size; i++) 
							{
								for (int j = 0; j < 4; j++)
								{
									if (x.getSurrender(i, j) == false && x.showPlayer(i).getScore(j) > 0)
									{
										balance = x.getBalance(i) + x.getBet(i, j);
										x.setBalance(balance, i);
										cout << x.showPlayer(i).getName() << " wins $" << x.getBet(i, j) << endl;
										cout << x.showPlayer(i).getName() << "'s balance is $" << x.getBalance(i) << endl << endl;
									}
								}
							}

							stopFlag = 1;
						}
					}

					else if (dealer.getScore() >= 17 && dealer.getScore() <= 21 && dealer.getHit() == true)
					{
						cout << "Dealer chose to 'stand'." << endl << endl;
						dealer.setHit();
					}
				}

			int flag = 0;

			//Continues playing rest of game after everyone's first turn
			if (stopFlag == 0)
				{
					do
					{

						for (int i = 0; i < size; i++)
						{
							for(int j = 0; j < 4; j++)
							{
								x.standardPrompt(gameDeck, i, j);
							}
						}

						int surrenderFlag = 0;

						for (int i = 0; i < size; i++)
						{
							for (int j = 0; j < 4; j++)
							{
								if (x.getSurrender(i, j) == false && x.showPlayer(i).getScore(j) > 0)
								{
									surrenderFlag = 1;
									break;
								}
							}
						}

						if (surrenderFlag == 0)
						{
							cout << "No players remaining!" << endl << endl;
							stopFlag = 1;
						}

						if (stopFlag == 0)
						{
							if (dealer.getScore() <= 16)
							{
								cout << "Dealer chose to 'hit'." << endl;
								dealer.drawCard(gameDeck, 1);
								dealer.displayDealer();
								cout << endl;

								if (dealer.getScore() > 21)
								{
									cout << "Dealer Busts! All remaining players win!" << endl << endl;
								
									for (int i = 0; i < size; i++)
									{
										for (int j = 0; j < 4; j++)
										{
											if (x.getSurrender(i, j) == false && x.showPlayer(i).getScore(j) > 0)
											{
												balance = x.getBalance(i) + x.getBet(i, j);
												x.setBalance(balance, i);
												cout << x.showPlayer(i).getName() << " wins $" << x.getBet(i, j) << endl;
												cout << x.showPlayer(i).getName() << "'s balance is $" << x.getBalance(i) << endl << endl;
											}
										}
									}

									stopFlag = 1;
								}
							}

							else if (dealer.getScore() >= 17 && dealer.getScore() <= 21 && dealer.getHit() == true)
							{
								cout << "Dealer chose to 'stand'." << endl << endl;
								dealer.setHit();
							}

							if (flag == 0)
							{
								for (int i = 0; i < size; i++)
								{
									for (int j = 0; j < 4; j++)
									{
										if (x.getSurrender(i, j) == false && x.showPlayer(i).getScore(j) == 21)
										{
											x.drawCard(gameDeck, 0, i, j);
										}
									}
								}
							}

							int flag_two = 0;

							for (int i = 0; i < size; i++)
							{
								if (x.showPlayer(i).getHit(0) == true || x.showPlayer(i).getHit(1) == true || x.showPlayer(i).getHit(2) == true || x.showPlayer(i).getHit(3) == true)
								{
									flag_two = 1;
									break;
								}
							}

							if (flag_two == 0)
							{
								flag = 1;
							}

							int surrenderFlag = 0;

							for (int i = 0; i < size; i++) 
							{
								for (int j = 0; j < 4; j++)
								{
									if (x.getSurrender(i, j) == false && x.showPlayer(i).getScore(j) > 0)
									{
										surrenderFlag = 1;
										break;
									}
								}
							}

							if (surrenderFlag == 0)
							{
								cout << "No players remaining!" << endl << endl;
								stopFlag = 1;
							}
						}

					} while ((flag == 0 && stopFlag == 0) || (dealer.getScore() <= 16 && stopFlag == 0));


					//Reveals all of dealer's cards and shows all scores for those still in the game
					if (stopFlag == 0)
					{
						cout << "All of Dealer's Cards Revealed: " << endl;

						dealer.displayDealerAll();

						cout << endl;

						//Overloaded << operator for Player's scores
						cout << x;

						cout << "Dealer's Score: " << dealer.getScore() << endl << endl;

						for (int i = 0; i < size; i++)
						{
							for (int j = 0; j < 4; j++)
							{
								if (x.getSurrender(i, j) == false && x.showPlayer(i).getScore(j) > 0)
								{
									if (x.showPlayer(i).getScore(j) == dealer.getScore())
									{
										cout << x.showPlayer(i).getName() << " ties with Dealer." << endl << endl;
									}

									else if (x.showPlayer(i).getScore(j) > dealer.getScore())
									{
										balance = x.getBalance(i) + x.getBet(i, j);
										x.setBalance(balance, i);
										cout << x.showPlayer(i).getName() << " wins $" << x.getBet(i, j) << endl;
										cout << x.showPlayer(i).getName() << "'s balance is $" << x.getBalance(i) << endl << endl;
									}

									else if (x.showPlayer(i).getScore(j) < dealer.getScore())
									{
										balance = x.getBalance(i) - x.getBet(i, j);
										x.setBalance(balance, i);
										cout << x.showPlayer(i).getName() << " loses $" << x.getBet(i, j) << endl;
										cout << x.showPlayer(i).getName() << "'s balance is $" << x.getBalance(i) << endl << endl;
									}
								}
							}
						}
					}
				}
			}

		//Clears all player's hands
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < 4; j++)				
			{
				x.clearHand(i, j);
			}
		}

		cout << "Game's Done" << endl << endl;

		//Prompts user if they would like to play again with remaining balances
		do
		{
			cout << "Would you like to play another game of Blackjack? Press (1) for 'Yes' or (2) for 'No'." << endl;
			cin >> input;

			if (input < 1 || input > 2)
			{
				cout << "Invalid input." << endl << endl;
			}

		} while (input < 1 || input > 2);

		gameFlag = input;

		cout << endl;

	} while (gameFlag == 1);

	//Closes the program if player(s) decide to not continue another game
	exit(0);
}