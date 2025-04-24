#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <numeric>
using namespace std;

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
			for (int rank = 1; rank <= 13; rank++) {
				int value;
				if (rank > 10) {
					value = 10;
				}
				else {
					value = rank;
				}
				for (int suitCount = 0; suitCount < 4; suitCount++) {
					cards.push_back(value);
				}
			}
		}
		shuffleShoe();
	}

	void shuffleShoe() {
		unsigned seed = chrono::system_clock::now().time_since_epoch().count();
		shuffle(cards.begin(), cards.end(), default_random_engine(seed));
	}

	int drawCard() {
		if (cards.size() < 100) {
			cout << "-------------------------------------------" << endl;
			cout << "[Too little cards in deck, Reshuffle Time!]" << endl;
			cout << "-------------------------------------------" << endl;
			cout << endl;
			initializeShoe();
		}
		int card = cards.back();
		cards.pop_back();
		return card;
		/*
		if (card == 1) {
			return 11;
		}
		else {
			return card;
		}
		*/
	}
};

class Blackjack {
private:
	Shoe shoe;
	vector<int> playerHand;
	vector<int> dealerHand;
	int wins = 0, losses = 0, draws = 0;

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

	void resultsTable(int playersValue, char hitOrStand, int &wins, int &losses, int &draws) {
		vector<int> simulatePlayerHand{ playersValue, shoe.drawCard()};
		vector<int> dealersHand{ shoe.drawCard(), shoe.drawCard() };

		if (hitOrStand == 'H' || hitOrStand == 'h') {
			simulatePlayerHand.push_back(shoe.drawCard());
		}

		int playersTotal = getHandValue(simulatePlayerHand);
		if (playersTotal > 21) {
			losses++;
			return;
		}

		while (getHandValue(dealersHand) < 17) {
			dealersHand.push_back(shoe.drawCard());
		}

		int dealersTotal = getHandValue(dealersHand);

		if (playersTotal > dealersTotal || dealersTotal > 21) {
			wins++;
		}
		else if (playersTotal < dealersTotal) {
			losses++;
		}
		else {
			draws++;
		}
	}

public:
	Blackjack() {
		srand(time(0));
	}

	void calculateResults() {
		int simulations = 10;

		for (int handValue = 4; handValue <= 21; handValue++) {
			int hitWins = 0, hitLosses = 0, hitDraws = 0,
				standWins = 0, standLosses = 0, standDraws = 0;

			for (int test = 0; test < simulations; test++) {
				resultsTable(handValue, 'H', hitWins, hitLosses, hitDraws);
				resultsTable(handValue, 'S', standWins, standLosses, standDraws);
			}

			cout << "Starting Hand: " << handValue << endl;
			cout << "Hit Wins: " << hitWins << ", Losses: " << hitLosses << ", Draws: " << hitDraws << endl;
			cout << "Stand Wins: " << standWins << ", Losses: " << standLosses << ", Draws: " << standDraws << endl;
		}
	}

	void playBlackjack() {
		/*
		for (int i = 0; i < 200; i++) {
			cout << shoe.drawCard() << endl;
		}
		*/
		while (true) {
			cout << "Time to play Blackjack!" << endl;
			cout << endl;
			playerHand = { shoe.drawCard(), shoe.drawCard() };
			dealerHand = { shoe.drawCard(), shoe.drawCard() };

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
					playerHand.push_back(shoe.drawCard());
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
				losses++;
			}
			else {
				cout << "Now it's the Dealer's turn!" << endl;
				cout << endl;
				displayHands(dealerHand, "Dealer");

				

				while (getHandValue(dealerHand) < 17) {
					dealerHand.push_back(shoe.drawCard());
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
					losses++;
				}
				else {
					cout << "We have a Draw! Push!" << endl;
					cout << endl;
					draws++;
				}
			}
			cout << "Your Total Wins: " << wins << endl;
			cout << "Your Total Losses: " << losses << endl;
			cout << "Your Total draws: " << draws << endl;
			cout << endl;

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