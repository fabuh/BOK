#include "Hero.h"


Hero::Hero() 
	:deck(Deck()), name(" "), handCount(0), health(40), mana(3)
{

}

Hero::Hero(Deck newDeck, const char* newName)
{
	for (int i = 0; i < 20; ++i)
	{
		name[i] = newName[i];
	}
	deck = newDeck;
	handCount = 0;
	health = 40;
	mana = 3;
	for (int i = 0; i < 10; ++i)
	{
		hand[i] = nullptr;
	}
}

Hero::Hero(const Hero& other)
{
	for (int i = 0; i < 20; ++i)
	{
		name[i] = other.name[i];
	}
	deck = other.deck;
	for (int i = 0; i < 10; ++i)
	{
		hand[i] = other.hand[i];
	}
	handCount = other.handCount;
	health = other.health;
	mana = other.mana;
}

const Hero& Hero::operator=(const Hero& other)
{
	if (this != &other)
	{
		for (int i = 0; i < 20; ++i)
		{
			name[i] = other.name[i];
		}
		deck = other.deck;
		for (int i = 0; i < 10; ++i)
		{
			hand[i] = other.hand[i];
		}
		handCount = other.handCount;
		health = other.health;
		mana = other.mana;
	}
	return *this;
}

Card** Hero::GetHand()
{
	return hand;
}

int Hero::GetHealth()
{
	return health;
}

size_t Hero::GetMana()
{
	return mana;
}

size_t Hero::GetHandCount()
{
	return handCount;
}

char* Hero::GetName()
{
	return name;
}

void Hero::DrawCard()
{
	if (handCount < 9)
	{
		int curr = deck.SuccCount();
		if (curr > 0)
		{
			hand[handCount++] = deck.GetCards()[curr];
		}
	}
}

void Hero::ReduceCardsInHandCount()
{
	handCount--;
}

void Hero::DamageHero(size_t damage)
{
	health = health - damage;
}

void Hero::SpendMana(size_t spent)
{
	mana -= spent;
}

void Hero::FixMana(size_t turn)
{
	if (turn < 5)
	{
		mana = 3;
	}
	else if (turn < 7)
	{
		mana = 7;
	}
	else mana = 11;
}

void Hero::FixHand()
{
	if (handCount < 9)
	{
		for (size_t i = 0; i < handCount; ++i)
		{
			if (hand[i] == nullptr)
			{
				hand[i] = hand[i + 1];
			}
		}
		hand[9] = nullptr;
	}
}

void Hero::PrintHand()
{
	for (size_t i = 0; i < handCount; ++i)
	{
		printf("Card %i:", i + 1);
		hand[i]->Print();
	}
}

void Hero::Print()
{
	printf("Name: %s \n", name);
}

