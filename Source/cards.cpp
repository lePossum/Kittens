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
  bool iteration;
  while ( cards_in_cont > 0 ) {
    std::srand(unsigned(std::time(0)));
    i = (std::rand()) % AMOUNT_OF_CARD_TYPES;
    iteration = true;
    while (iteration) {
      if (container[i] > 0) {
        container[i]--;
        cards_in_cont--;
        card_vector.push_back(Card((Card_type)i));// does it work
        iteration = false;
      } else {
        i = (i + 1) % AMOUNT_OF_CARD_TYPES;
      }
    } 
  }
  return;
}

void Player::get_card(Deck& cur_deck) {
  int i = cur_deck.card_vector.size();
  auto got_card = cur_deck.card_vector[i-1];
  hand[got_card.get_type()]++;
  cur_deck.card_vector.pop_back();
}

void Player::start_get_card(Deck& cur_deck) {
  int i = cur_deck.card_vector.size();
  bool swap_necessity = false, success_flag = false;
  Card final_card(EXPLODE);
  while (!success_flag) {
    if (i > 0) {
      auto pretender_card = cur_deck.card_vector[i - 1];
      Card_type type = pretender_card.get_type();
      if ( type == EXPLODE ) {
        i--;
        swap_necessity = true;
      } else {
        final_card = pretender_card;
        success_flag = true;
      }
      if (swap_necessity) {
        auto temp = cur_deck.card_vector
          [cur_deck.card_vector.size() - 1];
        cur_deck.card_vector
          [cur_deck.card_vector.size() - 1] = 
            cur_deck.card_vector[i - 1];
        cur_deck.card_vector[i - 1] = temp;
      }
    } else {
      throw Exception("Wrong vector index in start_get_card\n");
    }
  }
  hand[final_card.get_type()]++;
  cur_deck.card_vector.pop_back();
}

void Player::start_move() {

}