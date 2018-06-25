#pragma once
#include "Card.h"
#include "Utils.h"
class Spell : public Card
{
public:
	Spell();
	Spell(size_t newManaCost, Effect newEffect, size_t newCount);
	Spell(const Spell& other);
	const Spell& operator=(const Spell& other);

	Effect GetEffect();
	size_t GetAmount();

	bool IsMinion();

	void Print();
private:
	Effect effect;
	size_t amount;
};