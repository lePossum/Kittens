#include <iostream>
#include "cards.hpp"

enum {
  AMOUNT_OF_PLAYERS = 4
};

int main() {
  int players_amount = 2;
  // bool correct_am = false;
  // while (!correct_am) {
  //   std::cout << "Input amount of players : ";
  //   std::cin >> players_amount;
  //   std::cout << std::endl;
  //   if ((players_amount <= AMOUNT_OF_PLAYERS) 
  //     && (players_amount >= 2)) correct_am = true;
  // }
  Deck cur_deck;
  cur_deck.create_deck(players_amount);
  //Begin_game(&cur_deck, players_amount);
}