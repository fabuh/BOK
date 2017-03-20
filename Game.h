#pragma once
#include "Hero.h"
#include <cstdlib>
#include <time.h>
#include <string>
#include <iostream>

class Game {
public:
	Game(Hero forPlayer1, Hero forPlayer2) {
		player1 = forPlayer1;
		player2 = forPlayer2;
		started = 0;
	}


	void startGame() {
		started = 1;
		srand(time(NULL));
		coin = rand() % 2;
		size_t last = coin + 1;
		size_t turnCount = 2;
		while (player1.getHealth() > 0 || player2.getHealth() > 0) {
			turn(last, turnCount++);

		}
	}

	void turn(size_t last, size_t turnCount) {
		size_t now;
		if (last == 1)
			now = 2;
		else now = 1;
		printf("Turn %i: Player %i's turn. \n Press Enter to continue.", turnCount/2, now);
		std::string wtfNiggaISaidPressEnter;
		std::cin >> wtfNiggaISaidPressEnter;
	}
	
	void pickOption(int now) {
		char option = '0';
		while (option != '3') {
			printf("Pick an option: \n 1.Play Card \n 2.Attack with Mobs \n 3.End Turn \n");
			while (option - '0' < 0 && option - '0' > 4) {
				printf("Your choice: ");
				std::cin >> option;
			}
			if (option == '1') {
				Card** hand;
				if (now == 1) {
					hand = player1.getHand();
					player1.printHand();
				}
				else {
					hand = player2.getHand();
					player2.printHand();
				}
				
			}
			else if (option == '2') {

			}
		}
	}


private:
	Hero player1, player2;
	bool coin;
	bool started;
};
