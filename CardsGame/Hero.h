#pragma once
#include "Deck.h"
class Hero
{
public:
	Hero();
	Hero(Deck newDeck, const char* newName);
	Hero(const Hero& other);
	const Hero& operator=(const Hero& other);

	Card** GetHand();
	int GetHealth();
	size_t GetMana();
	size_t GetHandCount();
	char* GetName();

	void DrawCard();
	void ReduceCardsInHandCount();
	void DamageHero(size_t damage);
	void SpendMana(size_t spent);

	//increses the mana on higher rounds
	void FixMana(size_t turn);
	//if the player has played a card move the cards to fill it
	void FixHand();

	void PrintHand();
	void Print();
private:
	char name[20];
	Deck deck;
	Card* hand[10];
	size_t handCount;
	int health;
	size_t mana;
};
