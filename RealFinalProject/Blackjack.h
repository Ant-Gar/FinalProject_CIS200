#include <iostream>
#include <vector>
#include <random>
#include <chrono>
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

	int cardValue() {
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
};

class Shoe {
private:
	vector<Card> deck;
public:
	Shoe() {
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
		Card card = deck.front();
		return card;
	}
};