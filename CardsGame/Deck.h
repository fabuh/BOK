#pragma once
#include "Card.h"

class Deck {
public:
	Deck();
	Deck(Card** newCards, size_t newCount = 0);
	Deck(const Deck& other);
	const Deck& operator=(const Deck& other);

	int SuccCount();

	Card** GetCards();

	void AddCard(Card* newCard);

private:
	Card* cards[30];
	size_t count;
};