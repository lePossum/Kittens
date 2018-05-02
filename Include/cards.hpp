#include <vector>
#include <cstdlib>
#include <ctime>

enum Card_type {
	EXPLODE, //0
	DIFUSE,  //1
	SLAP,    //2
	SKIP,    //3
	SHUFFLE, //4
	FORECAST //5
};

enum {
	AMOUNT_OF_CARD_TYPES = 2
};

class Card {
	Card_type type;
	int card_key;
public:
	Card(Card_type);
	void change_key();
	void execute();
};

class Deck {
	std::vector<Card> card_vector;
public:
	void create_deck(int);
};

class Player {
	int hand[AMOUNT_OF_CARD_TYPES];
public:
	void start_move();
};