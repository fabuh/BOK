#pragma once
#include <iostream>
class Card {
public:
	//virtual void useCard(size_t pos) = 0;
	virtual void Print() = 0;

	virtual bool IsMinion() = 0;

	size_t manaCost;
};