#pragma once
#include "Deck.h"

class Hero {
public:
	Hero() :deck(Deck()), name(" "), handCount(0), health(40), mana(3) { }

	Hero(Deck newDeck, char* newName) {
		for (int i = 0; i < 20; ++i)
			name[i] = newName[i];
		deck = newDeck;
		handCount = 0;
		health = 40;
		mana = 3;
		for (int i = 0; i < 10; ++i) {
			hand[i] = nullptr;
		}
	}
	
	Hero(const Hero& other) {
		for (int i = 0; i < 20; ++i)
			name[i] = other.name[i];
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
			for (int i = 0; i < 20; ++i)
				name[i] = other.name[i];
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
		if (handCount < 9) {
			int curr = deck.succCurrent();
			if (curr > 0)
				hand[handCount++] = deck.getCards()[curr];
		}
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

	void damaged(size_t damage) {
		health = health - damage;
	}

	void printHand() {
		for (size_t i = 0; i < handCount; ++i) {
			printf("Card %i:", i + 1);
			hand[i]->print();
		}
	}

	void playedCard() {
		handCount--;
	}

	void fixHand() {
		if (handCount < 9) {
			for (size_t i = 0; i < handCount; ++i) {
				if (hand[i] == nullptr) {
					hand[i] = hand[i + 1];
				}
			}
			hand[9] = nullptr;
		}
	}

	size_t getHandCount() {
		return handCount;
	}

	void spendMana(size_t spent) {
		mana -= spent;
	}

	void fixMana(size_t turn) {
		if (turn < 5) {
			mana = 3;
		}
		else if (turn < 7) {
			mana = 7;
		}
		else mana = 11;
	}

	void print() {
		printf("Name: %s \n", name);
	}

	char* getName() {
		return name;
	}

private:
	char name[20];
	Deck deck;
	Card* hand[10];
	size_t handCount;
	int health;
	size_t mana;
};
