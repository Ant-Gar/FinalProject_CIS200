#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <numeric>
using namespace std;

class Card {
public:
	static int getCardValue(int card) {
		if (card > 10) {
			return 10;
		}
		else {
			return card;
		}
	}

	static int drawCard() {
		return rand() % 13 + 1;
	}
};

class Shoe {
private:
	vector<int> cards;
public:
	Shoe() {
		initializeShoe();
	}

	void initializeShoe() {
		cards.clear();
		for (int deckOfCards = 0; deckOfCards < 6; ++deckOfCards) {
			for (int rank = 1; rank <= 13; ++rank) {
				for (int suitCount = 0; suitCount < 4; ++suitCount) {
					int value;
					if (rank > 10) {
						value = 10;
					}
					else {
						value = rank;
					}
					cards.push_back(value);
				}
			}
		}
		shuffleShoe();
	}

	void shuffleShoe() {
		srand(time(0));
		random_shuffle(cards.begin(), cards.end());
	}

	int drawCard() {
		if (cards.size() < 100) {
			cout << "[To much cards played, Reshuffle Time!]" << endl;
			initializeShoe();
		}
		int card = cards.back();
		cards.pop_back();
		if (card == 1) {
			return 11;
		}
		else {
			return card;
		}
	}

	int remainingCards() const {
		return cards.size();
	}
};

class Blackjack {
private:
	vector<int> playerHand;
	vector<int> dealerHand;
	int wins = 0, loses = 0;

	int getHandValue(vector<int>& hand) {
		int total = accumulate(hand.begin(), hand.end(), 0);
		int aceCount = count(hand.begin(), hand.end(), 11);
		while (total > 21 && aceCount > 0) {
			total -= 10;
			aceCount--;
		}
		return total;
	}

	void displayHands(vector<int> hand, string name) {
		cout << name << "'s hand: ";
		for (int card : hand) {
			cout << card << " ";
		}
		cout << "(Total: " << getHandValue(const_cast<vector<int>&>(hand)) << ")" << endl;
	}

public:

	Blackjack() {
		srand(time(0));
	}

	int playBlackjack() {
		while (true) {
			cout << "Time to play Blackjack!" << endl;
			playerHand = { Card::drawCard(), Card::drawCard() };
			dealerHand = { Card::drawCard(), Card::drawCard() };

			displayHands(playerHand, "Player");
			cout << "Dealer's first card: " << Card::getCardValue(dealerHand[0]);
			cout << endl;

			int choice;
			cout << "Type 1 to Continue Playing or Type 2 to Stop PLaying: ";
			cin >> choice;
			if (choice == 1) {
				playerHand.push_back(Card::drawCard());
				displayHands(playerHand, "Player");
			}
			else {
				break;
			}

			int playerTotal = getHandValue(playerHand);
			if (playerTotal > 21) {
				cout << "You Busted! Dealer Wins!" << endl;
				loses++;
			}
			
			cout << "Now it's the Dealer's turn!" << endl;
			displayHands(dealerHand, "Dealer");

			int dealerTotal = getHandValue(dealerHand);

			while (getHandValue(dealerHand) < 17) {
				dealerHand.push_back(Card::drawCard());
				displayHands(dealerHand, "Dealer");
			}

			if (playerTotal > dealerTotal || dealerTotal > 21) {
				cout << "Player Wins! The House has Lost!" << endl;
				wins++;
			}
			else if (playerTotal < dealerTotal || playerTotal > 21) {
				cout << "Dealer Wins! The House always does!" << endl;
				loses++;
			}
			else {
				cout << "We have a draw! Push!" << endl;
			}
		}
	}
};