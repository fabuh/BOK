#pragma once
#include "Game.h"
Game::Game(Hero forPlayer1, Hero forPlayer2)
{
	player1 = forPlayer1;
	player2 = forPlayer2;
	started = 0;
	for (int i = 0; i < 10; ++i)
	{
		field[i] = nullptr;
	}
}


void Game::StartGame()
{
	started = 1;
	srand((unsigned int)time(NULL));
	coin = rand() % 2;
	size_t last = coin + 1;
	size_t turnCount = 2;
	while (player1.GetHealth() > 0 || player2.GetHealth() > 0)
	{
		Turn(last, turnCount++);
	}
	if (player1.GetHealth() <= 0)
		printf("The winner is Player 2");
	else
		printf("The winner is Player 1");
}

void Game::Turn(size_t last, size_t turnCount)
{
	size_t now;
	if (last == 1)
	{
		now = 2;
	}
	else
	{
		now = 1;
	}

	printf("Turn %i: Player %i's turn. \n Press Enter to continue.", turnCount / 2, now);
	std::system("pause");

	PrintField();
	PickOption(now);
	FixMobs(now);
	if (now == 1)
	{
		player1.FixMana(turnCount / 2);
	}
	else
	{
		player2.FixMana(turnCount / 2);
	}
}

void Game::PickOption(int now)
{
	char option = '0';
	bool passedTurn = 1;
	Hero player;
	if (now == 1)
	{
		player = player1;
	}
	else
	{
		player = player2;
	}
	player.DrawCard();

	while (option != '3')
	{
		option = '0';
		printf("Pick an option: \n 1.Play Card \n 2.Attack with Mobs \n 3.End Turn");
		while (option - '0' < 1 || option - '0' > 3)
		{
			printf("\nYour choice: ");
			std::cin >> option;
		}
		if (option == '1')
		{
			passedTurn = 0;
			bool played = 0;
			Card** hand;
			hand = player.GetHand();
			player.PrintHand();
			printf("Pick a card to play: ");
			size_t num = 0;
			while (num < 1 && num > player.GetHandCount())
			{
				std::cin >> num;
			}
			if (hand[num]->manaCost > player.GetMana()) continue;
			if (hand[num]->IsMinion() == 1)
			{
				for (int i = 0; i < 5; ++i)
				{
					if (field[i + !(now - 1) * 5] == nullptr)
					{
						field[i + !(now - 1) * 5] = static_cast<Minion*>(hand[num]);
						played = 1;
						player.ReduceCardsInHandCount();
						player.SpendMana(hand[num]->manaCost);
						hand[num] = nullptr;
						break;
					}
				}
			}
			else
			{
				Target(hand[num], 0, -1, now, played);
				if (played)
				{
					player.ReduceCardsInHandCount();
					player.SpendMana(hand[num]->manaCost);
					hand[num] = nullptr;
				}
			}
			if (played) player.FixHand();
		}
		else if (option == '2')
		{
			passedTurn = 0;
			for (int i = 0; i < 5; ++i)
			{
				Minion* mob = field[i + !(now - 1) * 5];
				if (mob != nullptr)
				{
					Target(mob, 1, i + !(now - 1) * 5, now, 0);
				}
				mob->Freeze();
			}
		}
		else
		{
			if (passedTurn = 1)
			{
				player.DamageHero(2);
			}
		}
	}
}

void Game::Target(Card* card, bool mob, size_t posOnField, size_t now, bool played)
{
	printf("0 - player, 1-5 - mobs");
	printf("Pick an enemy to attack: ");
	int num = -1;
	while (num < 0 || num > 5)
	{
		std::cin >> num;
	}
	size_t targeted = num + (!(now - 1)) * 5 - 1;
	if (mob)
	{
		Minion* current = static_cast<Minion*>(card);
		if (num == 0 && now == 1)
		{
			player2.DamageHero(current->GetDamage());
			return;
		}
		else if (num == 0)
		{
			player1.DamageHero(current->GetDamage());
			return;
		}
		if (field[targeted] == nullptr) return;
		field[targeted]->DamageMinion(current->GetDamage());
		if (field[targeted]->GetHealth() < 1) field[targeted] = nullptr;
		field[posOnField]->DamageMinion(field[targeted]->GetDamage());
		if (field[posOnField]->GetHealth() < 1) field[posOnField] = nullptr;
	}
	else
	{
		Spell* current = static_cast<Spell*>(card);
		if (num == 0 && now == 1 && current->GetEffect() == DealDamage)
		{
			player2.DamageHero(current->GetAmount());
			played = 1;
			return;
		}
		else if (num == 0 && current->GetEffect() == DealDamage)
		{
			player1.DamageHero(current->GetAmount());
			played = 1;
			return;
		}
		if (field[targeted] == nullptr) return;
		if (num == 0) return;
		switch (current->GetEffect())
		{
		case DealDamage:
			field[targeted]->DamageMinion(current->GetAmount());
			if (field[targeted]->GetHealth() < 1) field[targeted] = nullptr;
			played = 1;
			break;
		case Freeze:
			field[targeted]->Freeze();
			played = 1;
			break;
		case Destroy:
			field[targeted] = nullptr;
			played = 1;
			break;
		}
	}
}

void Game::FixMobs(size_t now)
{
	for (int i = 0; i < 5; ++i)
	{
		if (field[i + 5 * !(now - 1)] != nullptr)
		{
			field[i + 5 * !(now - 1)]->Unfreeze();
		}
	}
}

void Game::PrintField()
{
	printf("Player 1:%i hp %i mana \n", player1.GetHealth(), player1.GetMana());
	for (int i = 0; i < 10; ++i)
	{
		if (i == 5) printf("\n\n");
		if (field[i] == nullptr)
			printf("Empty");
		else
			field[i]->Print();
	}
	printf("\nPlayer 2:%i hp %i mana \n", player2.GetHealth(), player2.GetMana());
}