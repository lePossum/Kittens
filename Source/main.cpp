#include <iostream>
#include "cards.hpp"

enum {
  MAX_AMOUNT_OF_PLAYERS = 4,
  START_CARDS_AMOUNT = 1
};

int main() {
  int players_amount = MAX_AMOUNT_OF_PLAYERS;
  // bool correct_am = false;
  // while (!correct_am) {
  //   std::cout << "Input amount of players : ";
  //   std::cin >> players_amount;
  //   std::cout << std::endl;
  //   if ((players_amount <= MAX_AMOUNT_OF_PLAYERS) 
  //     && (players_amount >= 2)) correct_am = true;
  // }
  Deck cur_deck;
  cur_deck.create_deck(players_amount);
  Player player_number[players_amount];
  for (int i = 0; i < START_CARDS_AMOUNT; i++) {
    for (int j = 0; j < players_amount; j++)
      player_number[j].get_card(cur_deck);
  }
  //begin_game(&cur_deck, players_amount);
}