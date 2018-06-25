#include "Minion.h"

Minion::Minion()
{
	manaCost = 12;
	damage = 0;
	health = 0;
	frozen = 1;
}

Minion::Minion(size_t newManaCost, size_t newDamage, int newHealth)
{
	manaCost = newManaCost;
	damage = newDamage;
	health = newHealth;
	frozen = 1;
}

Minion::Minion(const Minion& other)
{
	manaCost = other.manaCost;
	damage = other.damage;
	health = other.health;
	frozen = other.frozen;
}

const Minion& Minion::operator=(const Minion& other)
{
	if (this != &other) {
		manaCost = other.manaCost;
		damage = other.damage;
		health = other.health;
		frozen = other.frozen;
	}
	return *this;
}

void Minion::Freeze()
{
	frozen = true;
}

void Minion::Unfreeze()
{
	frozen = 0;
}

bool Minion::IsFrozen()
{
	return frozen;
}

size_t Minion::GetDamage() const
{
	return damage;
}


int Minion::GetHealth() const
{
	return health;
}

void Minion::DamageMinion(size_t dmg)
{
	health -= dmg;
}

bool Minion::IsMinion()
{
	return 1;
}

void Minion::Print()
{
	printf("Mob: Health:%i Damage:%i ManaCost:%i \n", health, damage, manaCost);
}