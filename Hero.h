#pragma once
#include "Deck.h"

class Hero {
public:
	Hero() :deck(Deck()), handCount(0), health(40), mana(3) { }

	Hero(Deck newDeck) {
		deck = newDeck;
		handCount = 0;
		health = 40;
		mana = 3;
	}
	
	Hero(const Hero& other) {
		deck = other.deck;
		for (int i = 0; i < 10; ++i) {
			hand[i] = other.hand[i];
		}
		handCount = other.handCount;
		health = other.health;
		mana = other.mana;
	}

	const Hero& operator=(const Hero& other) {
		if (this != &other) {
			deck = other.deck;
			for (int i = 0; i < 10; ++i) {
				hand[i] = other.hand[i];
			}
			handCount = other.handCount;
			health = other.health;
			mana = other.mana;
		}
		return *this;
	}

	void drawCard() {
		int curr = deck.succCurrent();
		if(handCount == 10)
		if(curr > 0)
			hand[handCount++] = deck.getCards()[curr];
	}

	Card** getHand() {
		return hand;
	}

	int getHealth() {
		return health;
	}

	size_t getMana() {
		return mana;
	}

	void getDamage(size_t damage) {
		health = health - damage;
	}

	void printHand() {
		for (int i = 0; i < handCount; ++i) {
			hand[i]->print();
		}
	}

private:
	Deck deck;
	Card* hand[10];
	size_t handCount;
	int health;
	size_t mana;
};
