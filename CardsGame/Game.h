#pragma once
#include "Hero.h"
#include "Minion.h"
#include "Spell.h"
#include <cstdlib>
#include <time.h>
#include <string>
#include <iostream>

class Game
{
public:
	Game(Hero forPlayer1, Hero forPlayer2);

	void StartGame();

private:
	void Turn(size_t last, size_t turnCount);

	void PickOption(int now);

	void Target(Card* card, bool mob, size_t posOnField, size_t now, bool played);

	void FixMobs(size_t now);

	void PrintField();

private:
	Hero player1, player2;
	Minion* field[10];
	bool coin;
	bool started;
};
