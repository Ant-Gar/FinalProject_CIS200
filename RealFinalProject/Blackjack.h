#include <iostream>
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