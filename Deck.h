#pragma once
#include "Card.h"
#include <cstdlib>
#include <time.h>

class Deck {
public:
	Deck() :count(0) {
		for (int i = 0; i < 30; ++i) {
			cards[i] = nullptr;
		}
	}

	Deck(Card** newCards, size_t newCount = 0) {
		count = newCount;
		for (int i = 0; i < 30; ++i) {
			cards[i] = newCards[i];
		}
	}

	Deck(const Deck& other) {
		count = other.count;
		for (int i = 0; i < 30; ++i) {
			cards[i] = other.cards[i];
		}
	}

	const Deck& operator=(const Deck& other) {
		if (this != &other) {
			count = other.count;
			for (int i = 0; i < 30; ++i) {
				cards[i] = other.cards[i];
			}
		}
		return *this;
	}

	int succCurrent() {
		if (count > 30)
			return -1;
		return count++;
	}

	Card** getCards() {
		return cards;
	}

	void addCard(Card* newCard) {
		if (count <= 30) {
			cards[count++] = newCard;
		}
	}

	Card* operator[](int num) {
		if (num >= 0 && num < 30)
			return cards[num];
		return nullptr;
	}

private:
	Card* cards[30];
	size_t count;
};