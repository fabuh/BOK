#pragma once
#include "Deck.h"
#include <string>

class Hero {
public:
	Hero() :deck(Deck()), name(nullptr), handCount(0), health(40), mana(3) { }

	Hero(Deck &newDeck, char* newName) {
		int len = strlen(newName);
		name = new char[len+1];
		for (int i = 0; i < len; ++i)
			name[i] = newName[i];
		name[len] = '\0';
		deck = newDeck;
		handCount = 0;
		health = 40;
		mana = 3;
		deck = newDeck;
		for (int i = 0; i < 10; ++i) {
			hand[i] = nullptr;
		}
	}
	
	Hero(const Hero& other) {
		int len = strlen(other.name);
		name = new char[len+1];
		name[len] = '\0';
		for (int i = 0; i < len; ++i)
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
			int len = strlen(other.name);
			if(name != nullptr)
				delete[] name;
			name = new char[len+1];
			for (int i = 0; i < len; ++i)
				name[i] = other.name[i];
			name[len] = '\0';
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

	~Hero() {
		delete[] name;
	}

	void drawCard() {
		int curr = deck.succCurrent();
		if (handCount < 9) {
			if (curr >= 0 && curr < 30)
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

	void shuffleDeck() {
		int arr[30];
		for (int i = 0; i < 30; ++i) {
			arr[i] = i;
		}
		int temp, num1, num2;
		for (int i = 0; i < 500; ++i) {
			num1 = rand() % 30, num2 = rand() % 30;
			temp = arr[num1];
			arr[num1] = arr[num2];
			arr[num2] = temp;
		}
		Deck shuffled;
		for (int i = 0; i < 30; ++i) {
			shuffled.addCard(deck[arr[i]]);
		}
		deck = shuffled;
	}

private:
	char* name;
	Deck deck;
	Card* hand[10];
	size_t handCount;
	int health;
	size_t mana;
};
