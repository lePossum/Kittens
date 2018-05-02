#include "cards.hpp"

Card::Card(Card_type c_type) {
	type = c_type;
	std::srand(unsigned(std::time(0)));
	card_key = std::rand();
}

void Card::change_key(){
	std::srand(unsigned(std::time(0)));
	card_key = std::rand();
}

void Deck::create_deck(int amount_of_players) {
	int container[AMOUNT_OF_CARD_TYPES];

	container[EXPLODE] = amount_of_players - 1;
	container[DIFUSE] = 6 - amount_of_players;

	int cards_in_cont = 0, i;
	for (i = 0; i < AMOUNT_OF_CARD_TYPES; i++) {
		cards_in_cont += container[i];
	}
	while ( cards_in_cont > 0 ) {
		std::srand(unsigned(std::time(0)));
		i = (std::rand()) % AMOUNT_OF_CARD_TYPES;
		if (container[i] > 0) {
			container[i]--;
			cards_in_cont--;
			card_vector.push_back(Card((Card_type)i));
		}
	}
	return;
}
