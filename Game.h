#pragma once
#include "Hero.h"
#include <iostream>

class Game {
public:
	Game(Hero &forPlayer1, Hero &forPlayer2) {
		player1 = forPlayer1;
		player2 = forPlayer2;
		started = 0;
		for (int i = 0; i < 10; ++i) {
			field[i] = nullptr;
		}
	}


	void startGame() {
		started = 1;
		srand((unsigned int)time(NULL));
		if(rand() % 2) coin = 1;
		else coin = 0;
		size_t last = coin + 1;
		size_t turnCount = 2;
		player1.shuffleDeck();
		player2.shuffleDeck();
		for (int i = 0; i < 5; ++i) {
			player1.drawCard();
			player2.drawCard();
		}
		while (player1.getHealth() > 0 || player2.getHealth() > 0) {
			turn(last, turnCount++);
		}
		if (player1.getHealth() <= 0)
			printf("The winner is Player 2");
		else
			printf("The winner is Player 1");
	}

private:
	void turn(size_t last, size_t turnCount) {
		size_t now;
		if (last == 1)
			now = 2;
		else now = 1;

		system("CLS");

		printf("Turn %i: Player %i's turn. \n Press Enter to continue.\n", turnCount / 2, now);
		std::string wtfNiggaISaidPressEnter;
		std::cin >> wtfNiggaISaidPressEnter;
		printField();
		pickOption(now);
		fixMobs(now);
		if (now == 1) {
			player1.fixMana(turnCount/2);
		}
		else {
			player2.fixMana(turnCount/2);
		}
	}

	void pickOption(int now) {
		char option = '0';
		bool passedTurn = 1;
		Hero* player;
		if (now == 1)
			player = &player1;
		else
			player = &player2;

		player->drawCard();

		while (option != '3') {
			option = '0';
			printf("Pick an option: \n 1.Play Card \n 2.Attack with Mobs \n 3.End Turn");
			while (option - '0' < 1 || option - '0' > 3) {
				printf("\nYour choice: ");
				std::cin >> option;
			}
			if (option == '1') {
				passedTurn = 0;
				bool played = 0;
				Card** hand;
				hand = player->getHand();
				player->printHand();
				printf("Pick a card to play: ");
				size_t num = 0;
				while (num < 1 && num > player->getHandCount()) {
					std::cin >> num;
				}
				if (hand[num]->manaCost > player->getMana()) continue;
				if (hand[num]->amIMob() == 1) {
					for (int i = 0; i < 5; ++i) {
						if (field[i + !(now - 1) * 5] == nullptr) {
							field[i + !(now - 1) * 5] = static_cast<Mob*>(hand[num]);
							played = 1;
							player->playedCard();
							player->spendMana(hand[num]->manaCost);
							hand[num] = nullptr;
							break;
						}
					}
				}
				else {
					target(hand[num], 0, -1, now, played);
					if (played) {
						player->playedCard();
						player->spendMana(hand[num]->manaCost);
						hand[num] = nullptr;
					}
				}
				if(played) player->fixHand();
			}
			else if (option == '2') {
				bool empty = true;
				for (int i = 0; i < 5; ++i) {
					if (field[i + !(now - 1) * 5] != nullptr)
						empty = false;
				}
				if (!empty) {
					passedTurn = 0;
					for (int i = 0; i < 5; ++i) {
						Mob* mob = field[i + !(now - 1) * 5];
						if (mob != nullptr)
							target(mob, 1, i + !(now - 1) * 5, now, 0);
						mob->freeze();
					}
				}
			}
			else {
				if (passedTurn == 1)
					player->damaged(2);
			}
		}
	}

	void target(Card* card, bool mob, size_t posOnField, size_t now, bool played) {
		printf("0 - player, 1-5 - mobs");
		printf("Pick an enemy to attack: ");
		int num = -1;
		while (num < 0 || num > 5) {
			std::cin >> num;
		}
		size_t targeted = num + (!(now - 1)) * 5 - 1;
		if (mob) {
			Mob* current = static_cast<Mob*>(card);
			if (num == 0 && now == 1) {
				player2.damaged(current->getDamage());
				return;
			}
			else if (num == 0) {
				player1.damaged(current->getDamage());
				return;
			}
			if (field[targeted] == nullptr) return;
			field[posOnField]->damaged(field[targeted]->getDamage());
			if (field[posOnField]->getHealth() < 1) field[posOnField] = nullptr;
			field[targeted]->damaged(current->getDamage());
			if (field[targeted]->getHealth() < 1) field[targeted] = nullptr;
		}
		else {
			Spell* current = static_cast<Spell*>(card);
			if (num == 0 && now == 1 && current->getEffect() == DealDamage) {
				player2.damaged(current->getAmount());
				played = 1;
				return;
			}
			else if (num == 0 && current->getEffect() == DealDamage) {
				player1.damaged(current->getAmount());
				played = 1;
				return;
			}
			if (field[targeted] == nullptr) return;
			if (num == 0) return;
			switch (current->getEffect()) {
			case DealDamage:
				field[targeted]->damaged(current->getAmount());
				if (field[targeted]->getHealth() < 1) field[targeted] = nullptr;
				played = 1;
				break;
			case Freeze:
				field[targeted]->freeze();
				played = 1;
				break;
			case Destroy:
				field[targeted] = nullptr;
				played = 1;
				break;
			}
		}
	}
	
	void fixMobs(size_t now) {
		for (int i = 0; i < 5; ++i) {
			if (field[i + 5 * !(now - 1)] != nullptr) {
				field[i + 5 * !(now - 1)]->setLastTurn();
			}
		}
	}

	void printField() {
		printf("Player 1: %i hp %i mana \n", player1.getHealth(), player1.getMana());
		for (int i = 0; i < 10; ++i) {
			if (i == 5) printf("\n\n");
			if (field[i] == nullptr)
				printf("Empty\n");
			else
				field[i]->print();
		}
		printf("Player 2: %i hp %i mana \n", player2.getHealth(), player2.getMana());
	}

private:
	Hero player1, player2;
	Mob* field[10];
	bool coin;
	bool started;
};
