#pragma once
#include "Card.h"
class Minion : public Card
{
public:
	Minion();
	Minion(size_t newManaCost, size_t newDamage, int newHealth);
	Minion(const Minion& other);
	const Minion& operator=(const Minion& other);

	void Freeze();
	void Unfreeze();
	bool IsFrozen();

	int GetHealth() const;
	size_t GetDamage() const;

	void DamageMinion(size_t dmg);

	bool IsMinion();

	void Print();

private:
	size_t damage;
	int health;
	bool frozen;
};

