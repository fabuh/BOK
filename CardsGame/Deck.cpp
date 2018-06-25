#include "Deck.h"

Deck::Deck() : count(0)
{
	for (int i = 0; i < 30; ++i)
	{
		cards[i] = nullptr;
	}
}

Deck::Deck(Card** newCards, size_t newCount)
{
	count = newCount;
	for (int i = 0; i < 30; ++i)
	{
		cards[i] = newCards[i];
	}
}

Deck::Deck(const Deck& other)
{
	count = other.count;
	for (int i = 0; i < 30; ++i)
	{
		cards[i] = other.cards[i];
	}
}

const Deck& Deck::operator=(const Deck& other)
{
	if (this != &other)
	{
		count = other.count;
		for (int i = 0; i < 30; ++i)
		{
			cards[i] = other.cards[i];
		}
	}
	return *this;
}

int Deck::SuccCount()
{
	if (count > 30)
		return -1;
	return ++count;
}

Card** Deck::GetCards()
{
	return cards;
}

void Deck::AddCard(Card* newCard)
{
	if (count <= 30)
	{
		cards[count++] = newCard;
	}
	count = 0;
}