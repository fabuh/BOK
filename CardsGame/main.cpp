#include "Game.h"
#include <vector>

bool chosen(int option, std::vector<int> arr) {
	for (int i = 0; i < 10; ++i) {
		if (arr[i] == option) return true;
	}
	return false;
}

void createADeck(Card** cards, Deck* decks, int deckCount) {
	for (int i = 0; i < 20; ++i) {
		printf("Card %i: ", i+1);
		cards[i]->Print();
	}
	printf("\nPick 10 cards out of the shown above. \n");
	size_t count = 10;
	std::vector<int> chosenCards;
	chosenCards.resize(10, 0);
	int option = 0;
	for (int i = 0; i < 10; ++i) {
		option = 0;
		while ((option < 1 || option > 20) && chosen(option, chosenCards)) {
			std::cin >> option;
		}
		printf("Chosen card: %i. \n", option);
		chosenCards[i] = option;
	}
	for (int i = 0; i < 10; ++i) {
		for (int i = 0; i < 3; ++i) {
			decks[deckCount].AddCard(cards[chosenCards[i]]);
		}
	}
}

int main() {
	Card *cards[20];
	Spell spells[5] = { Spell(5 ,Destroy, 1), Spell(2, Freeze, 1), Spell(3, DealDamage, 6), Spell(5, DealDamage, 8), Spell(7, DealDamage, 10)};
	Minion mobs[15];
	Deck decks[20];
	Hero heroes[5];
	int deckCount = 0, heroCount = 0;
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 15; ++i) {
		size_t mana, damage;
		int health;
		do {
			mana = rand() % 11 + 1;
			damage = rand() % 10 + 1;
			health = rand() % 10 + 1;
		} while (2*mana <= damage+health);
		mobs[i] = Minion(mana, damage, health);
		cards[i] = &mobs[i];
	}
	for (int i = 0; i < 5; ++i) {
		cards[i + 15] = &spells[i];
	}

	char option = '0';
	while (option != '3') {
		printf("Pick an option: \n 1.Create a deck \n 2.Create a hero \n 3.Start game");
		option = '0';
		while (option - '0' < 1 || option - '0' > 3) {
			printf("\nYour choice: ");
			std::cin >> option;
		}
		if (option == '1') {
			if (deckCount < 20)
				createADeck(cards, decks, deckCount++);
			printf("Deck %i was just created. \n\n\n", deckCount - 1);
		}
		else if (option == '2' && deckCount > 0) {
			printf("Pick a name for your hero. 20 symbols max length. \n");
			std::string name;
			std::cin >> name;
			printf("Pick a deck. from 1 to %i. \n", deckCount);
			int option2 = 0;
			while (option2 < 1 || option2 > deckCount)
				std::cin >> option2;
			heroes[heroCount++] = Hero(decks[option2-1], name.c_str());
			printf("Hero %s created. \n\n", name.c_str());
		}
		else if (option == '2') {
			printf("Create more Decks first. \n");
		}
		else if (option == '3' && heroCount < 2) {
			printf("Create more Heroes first. \n");
			option = '0';
		}
		else {
			printf("Pick a hero for Player 1. \n");
			for (int i = 0; i < heroCount; ++i) {
				printf("Hero %i: ", i + 1);
				heroes[i].Print();
			}
			char optionPlayer1 = '0';
			while (optionPlayer1 - '0' < 1 || optionPlayer1 - '0' > heroCount+1) {
				printf("\nYour choice: ");
				std::cin >> optionPlayer1;
			}
			printf("Player 1 picked hero %s. \n", heroes[optionPlayer1 - '0' - 1].GetName());


			printf("Pick a hero for Player 2. \n");
			for (int i = 0; i < heroCount; ++i) {
				printf("Hero %i: ", i + 1);
				heroes[i].Print();
			}
			char optionPlayer2 = '0';
			while (optionPlayer2 - '0' < 1 || optionPlayer2 - '0' > heroCount + 1) {
				printf("\nYour choice: ");
				std::cin >> optionPlayer2;
			}
			printf("Player 2 picked hero %s. \n", heroes[optionPlayer2 - '0' - 1].GetName());
			Game theGame(heroes[optionPlayer1 - '0' - 1], heroes[optionPlayer2 - '0' - 1]);
			theGame.StartGame();
		}
	}

	system("pause");
	return 0;
}