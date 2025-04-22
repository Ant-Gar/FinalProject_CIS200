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
	static int drawCard() {
		int card = rand() % 10 + 2;

		return card;
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
		for (int deckOfCards = 0; deckOfCards < 6; deckOfCards++) {
			for (int rank = 1; rank <= 11; rank++) {
				for (int suitCount = 0; suitCount < 4; suitCount++) {
					int value;
					if (rank == 1) {
						value = 11;
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
			cout << "[Too little cards in deck, Reshuffle Time!]" << endl;
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
			cout << "|" << card << "|";
		}
		cout << " = (Total: " << getHandValue(const_cast<vector<int>&>(hand)) << ")" << endl;
		cout << endl;
	}

public:
	Blackjack() {
		srand(time(0));
	}

	void playBlackjack() {
		while (true) {
			cout << "Time to play Blackjack!" << endl;
			cout << endl;
			playerHand = { Card::drawCard(), Card::drawCard() };
			dealerHand = { Card::drawCard(), Card::drawCard() };

			displayHands(playerHand, "Player");
			cout << "Dealer's hand: |" << dealerHand[0] << "||?|";
			cout << " = (Total: ?)" << endl;
			cout << endl;

			char choice;
			do {
				cout << "Type H to Hit or S Stand: ";
				cin >> choice;
				cout << endl;

				if (choice == 'H' || choice == 'h') {
					playerHand.push_back(Card::drawCard());
					displayHands(playerHand, "Player");
				}
				else {
					break;
				}
			} while ((choice == 'H' || choice == 'h') && getHandValue(playerHand) < 21);

			int playerTotal = getHandValue(playerHand);
			if (playerTotal > 21) {
				cout << "You Busted! Dealer Wins!" << endl;
				cout << endl;
				loses++;
			}
			else {
				cout << "Now it's the Dealer's turn!" << endl;
				cout << endl;
				displayHands(dealerHand, "Dealer");

				

				while (getHandValue(dealerHand) < 17) {
					dealerHand.push_back(Card::drawCard());
					displayHands(dealerHand, "Dealer");
				}

				int dealerTotal = getHandValue(dealerHand);
				if (playerTotal > dealerTotal || dealerTotal > 21) {
					cout << "Player Wins! The House has Lost!" << endl;
					cout << endl;
					wins++;
				}
				else if (playerTotal < dealerTotal || playerTotal > 21) {
					cout << "Dealer Wins! The House always does!" << endl;
					cout << endl;
					loses++;
				}
				else {
					cout << "We have a draw! Push!" << endl;
					cout << endl;
				}
			}

			cout << "Do you want to play again? (Y/N): ";
			char playAgain;
			cin >> playAgain;
			if (playAgain != 'Y' && playAgain != 'y') {
				break;
			}
			cout << "------------------------------------" << endl;
		}
	}
};