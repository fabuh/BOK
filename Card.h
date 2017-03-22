#pragma once
#include <stdio.h>

enum Effect {
	DealDamage, Destroy, Freeze
};

class Card {
public:
	//virtual void useCard(size_t pos) = 0;
	virtual void print() = 0;
	
	virtual bool amIMob() = 0;

	size_t manaCost;
};


class Mob: public Card {
public:
	Mob() {
		manaCost = 12;
		damage = 0;
		health = 0;
		placedThisTurn = 1;
	}

	Mob(size_t newManaCost, size_t newDamage, int newHealth) {
		manaCost = newManaCost;
		damage = newDamage;
		health = newHealth;
		placedThisTurn = 1;
	}

	Mob(const Mob& other) {
		manaCost = other.manaCost;
		damage = other.damage;
		health = other.health;
		placedThisTurn = other.placedThisTurn;
	}

	const Mob& operator=(const Mob& other) {
		if (this != &other) {
			manaCost = other.manaCost;
			damage = other.damage;
			health = other.health;
			placedThisTurn = other.placedThisTurn;
		}
		return *this;
	}

	void print() {
		printf("Mob: Health:%i Damage:%i ManaCost:%i \n", health, damage, manaCost);
	}

	void setLastTurn() {
		placedThisTurn = 0;
	}

	bool getPlaced() {
		return placedThisTurn;
	}

	bool amIMob() {
		return 1;
	}

	size_t getDamage() {
		return damage;
	}

	void damaged(size_t dmg) {
		health -= dmg;
	}

	int getHealth() {
		return health;
	}

	void freeze() {
		placedThisTurn = 1;
	}

private:
	size_t damage;
	int health;
	bool placedThisTurn;
};

class Spell: public Card {
public:
	Spell() {
		manaCost = 12;
		effect = DealDamage;
		amount = 0;
	}

	Spell(size_t newManaCost, Effect newEffect, size_t newCount) {
		manaCost = newManaCost;
		effect = newEffect;
		amount = newCount;
	}

	Spell(const Spell& other) {
		manaCost = other.manaCost;
		effect = other.effect;
		amount = other.amount;
	}

	const Spell& operator=(const Spell& other) {
		if (this != &other) {
			manaCost = other.manaCost;
			effect = other.effect;
			amount = other.amount;
		}
		return *this;
	}

	void print() {
		if (effect == DealDamage) {
			printf("Spell: Deal %i damage to an enemy. %i \n", amount, manaCost);
		}
		else if (effect == Destroy) {
			printf("Spell: Destroy an enemy minions. %i \n", manaCost);
		}
		else {
			printf("Spell: Freeze an enemy minions. %i \n", manaCost);
		}
	}

	bool amIMob() {
		return 0;
	}

	Effect getEffect() {
		return effect;
	}

	size_t getAmount() {
		return amount;
	}

private:
	Effect effect;
	size_t amount;
};