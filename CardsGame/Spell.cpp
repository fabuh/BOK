#include "Spell.h"

Spell::Spell()
{
	manaCost = 12;
	effect = DealDamage;
	amount = 0;
}

Spell::Spell(size_t newManaCost, Effect newEffect, size_t newCount)
{
	manaCost = newManaCost;
	effect = newEffect;
	amount = newCount;
}

Spell::Spell(const Spell& other)
{
	manaCost = other.manaCost;
	effect = other.effect;
	amount = other.amount;
}

const Spell& Spell::operator=(const Spell& other)
{
	if (this != &other)
	{
		manaCost = other.manaCost;
		effect = other.effect;
		amount = other.amount;
	}
	return *this;
}

Effect Spell::GetEffect()
{
	return effect;
}

size_t Spell::GetAmount()
{
	return amount;
}

bool Spell::IsMinion()
{
	return 0;
}

void Spell::Print()
{
	if (effect == DealDamage)
	{
		printf("Spell: Deal %i damage to an enemy. %i \n", amount, manaCost);
	}
	else if (effect == Destroy)
	{
		printf("Spell: Destroy an enemy minions. %i \n", manaCost);
	}
	else
	{
		printf("Spell: Freeze an enemy minions. %i \n", manaCost);
	}
}