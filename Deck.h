#pragma once
#include "Card.h"

class Deck {
public:
	Deck():cards(nullptr), count(0), current(0) { }

	Deck(Card** newCards, size_t newCount, size_t newCurrent = 0) {
		count = newCount;
		current = newCurrent;
		cards = new Card*[count];
		for (int i = 0; i < count; ++i) {
			cards[i] = newCards[i];
		}
	}

	Deck(const Deck& other) {
		count = other.count;
		current = other.current;
		cards = new Card*[count];
		for (int i = 0; i < count; ++i) {
			cards[i] = other.cards[i];
		}
	}

	const Deck& operator=(const Deck& other) {
		if (this != &other) {
			if (cards != nullptr)
				delete[] cards;
			count = other.count;
			current = other.current;
			cards = new Card*[count];
			for (int i = 0; i < count; ++i) {
				cards[i] = other.cards[i];
			}
		}
		return *this;
	}


	~Deck() {
		if(cards != nullptr)
			delete[] cards;
	}

	int succCurrent() {
		if (current > count)
			return -1;
		return current++;
	}

	Card** getCards() {
		return cards;
	}

private:
	Card** cards;
	size_t count;
	size_t current;
};