#pragma once
#include <stdio.h>

enum Effect {
	DealDamage, Destroy, Freeze
};

class Card {
public:
	//virtual void useCard(size_t pos) = 0;
	virtual void print() = 0;
	
	size_t manaCost;
};


class Mob: public Card {
public:
	Mob() {
		manaCost = 12;
		damage = 0;
		health = 0;
	}

	Mob(size_t newManaCost, size_t newDamage, int newHealth) {
		manaCost = newManaCost;
		damage = newDamage;
		health = newHealth;
	}

	Mob(const Mob& other) {
		manaCost = other.manaCost;
		damage = other.damage;
		health = other.health;
	}

	const Mob& operator=(const Mob& other) {
		if (this != &other) {
			manaCost = other.manaCost;
			damage = other.damage;
			health = other.health;
		}
		return *this;
	}

	void print() {
		printf("Mob: Health:%i Damage:%i ManaCost:%i \n", health, damage, manaCost);
	}

private:
	size_t damage;
	int health;
};

class Spell: public Card {
public:
	Spell() {
		manaCost = 12;
		effect = DealDamage;
		count = 0;
	}

	Spell(size_t newManaCost, Effect newEffect, size_t newCount) {
		manaCost = newManaCost;
		effect = newEffect;
		count = newCount;
	}

	Spell(const Spell& other) {
		manaCost = other.manaCost;
		effect = other.effect;
		count = other.count;
	}

	const Spell& operator=(const Spell& other) {
		if (this != &other) {
			manaCost = other.manaCost;
			effect = other.effect;
			count = other.count;
		}
		return *this;
	}

	void print() {
		if (effect == DealDamage) {
			printf("Spell: Deal %i damage to an enemy. %i \n", count, manaCost);
		}
		else if (effect == Destroy) {
			printf("Spell: Destroys %i enemy minions. %i \n", count, manaCost);
		}
		else {
			printf("Spell: Freezes %i enemy minions. %i \n", count, manaCost);
		}
	}

private:
	Effect effect;
	size_t count;
};