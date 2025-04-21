#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
using namespace std;

enum Suit { Hearts, Diamonds, Spades, Clubs };
enum Number { Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace };

class Card {
private:
	Suit suit;
	Number number;
public:
	Card(Suit suit, Number number) {
		this->suit = suit;
		this->number = number;
	}

	int cardValue() const{
		if (number >= Two && number <= Ten) {
			return number;
		}
		else if (number >= Jack && number <= King) {
			return 10;
		}
		else {
			return 11;
		}
	}

	void print() const{
		string numbers[]{ "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
		string Suits[]{ "H", "D", "S", "C" };
		cout << numbers[number - 2] << Suits[suit] << endl;
	}
};

class Shoe {
private:
	vector<Card> deck;
public:
	Shoe(int numDeck) {
		for (int deckOfCards = 0; deckOfCards < 6; deckOfCards++) {
			for (int shoeSuit = Hearts; shoeSuit < Clubs; shoeSuit++) {
				for (int shoeNumber = Two; shoeNumber < Ace; shoeNumber++) {
					deck.push_back(Card(static_cast<Suit>(shoeSuit), static_cast<Number>(shoeNumber)));
				}
			}
		}
	}

	void shuffleDeck() {
		auto seed = chrono::system_clock::now().time_since_epoch().count();
		std::shuffle(deck.begin(), deck.end(), default_random_engine(seed));
	}

	Card deal() {
		if (deck.size() < 100) {
			shuffleDeck();
		}
		Card card = deck.back();
		deck.pop_back();
		return card;
	}

	int remainingCards() {
		return deck.size();
	}
};

class Blackjack {
private:
	Shoe shoe = Shoe(6);
	int wins = 0, loses = 0;

	int handValue(vector<Card> hand) {
		int sum = 0;

		for (const auto& card : hand) {
			sum += card.cardValue();
		}

		return sum;
	}

	void displayHands(vector<Card> playersHand, vector<Card> dealersHand) {
		cout << "Your Hand: " << endl;
		for (const auto& card : playersHand) {
			card.print();
		}
		cout << "Your total: " << handValue(playersHand) << endl;
		cout << endl;
		cout << "Dealer's Hand:" << endl;
		for (const auto& card : dealersHand) {
			card.print();
		}
		cout << "Dealer's total: " << handValue(dealersHand) << endl;
	}

	void playersTurn(vector<Card> playersHand) {
		while (handValue(playersHand) <= 21) {
			int choice;
			cout << "Type 1 to Hit or Type 2 to Stand: ";
			cin >> choice;

			if (choice == 1) {
				playersHand.push_back(shoe.deal());
				cout << "You hit: " << endl;
				playersHand.back().print();
				cout << "Your new total: " << handValue(playersHand) << endl;
			}
			else {
				cout << "You stand with: " << handValue(playersHand) << endl;
				break;
			}
		}
	}

	void dealersTurn(vector<Card> dealersHand) {
		while (handValue(dealersHand) <= 16) {
			dealersHand.push_back(shoe.deal());
			cout << "Dealer hits: " << endl;
			dealersHand.back().print();
			cout << "Dealers new total: " << handValue(dealersHand) << endl;
		}

		cout << "Dealer stands with" << handValue(dealersHand) << endl;
	}

	void calculateOutcome(vector<Card> playersHand, vector<Card> dealersHand) {
		int playersValue = handValue(playersHand);
		int dealersValue = handValue(dealersHand);

		if (playersValue > dealersValue || dealersValue > 21) {
			cout << "Player Wins! The House has Lost!" << endl;
			wins++;
		}
		else if (playersValue < dealersValue || playersValue > 21) {
			cout << "Dealer Wins! The House always does!" << endl;
			loses++;
		}
		else {
			cout << "We have a draw! Push!" << endl;
		}
	}
public:
	Blackjack() {}

	int playBlackjack() {
		while (true) {
			cout << "Time to play Blackjack!" << endl;
			vector<Card> playersHand = { shoe.deal(), shoe.deal() };
			vector<Card> dealersHand = { shoe.deal(), shoe.deal() };

			displayHands(playersHand, dealersHand);

			playersTurn(playersHand);

			if (handValue(playersHand) > 21) {
				cout << "You Busted! Dealer Wins!" << endl;
				loses++;
			}
			else {
				dealersTurn(dealersHand);
				calculateOutcome(playersHand, dealersHand);
			}

			cout << "Your amount of Wins: " << wins << endl;
			cout << "Your amount of Loses: " << loses << endl;

			int choice;
			cout << "Type 1 to Continue Playing or Type 2 to Stop PLaying: ";
			cin >> choice;
			if (choice == 2) {
				break;
			}
		}
	}
};