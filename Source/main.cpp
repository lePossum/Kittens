#include <iostream>
#include "cards.hpp"

enum {
  MAX_AMOUNT_OF_PLAYERS = 4,
  START_CARDS_AMOUNT = 1
};

int Player::lost_amount = 0;

int main() {
  int players_amount = MAX_AMOUNT_OF_PLAYERS;
  bool correct_am = false;
  while (!correct_am) {
    std::cout << "Input amount of players : ";
    std::cin >> players_amount;
    std::cout << std::endl;
    if ((players_amount <= MAX_AMOUNT_OF_PLAYERS) 
      && (players_amount >= 2)) {
        correct_am = true;
    } else {
      if (system("CLS")) system("clear");
      std::cout << "Wrong amount of players, try again\n";
    }
  }
  Deck cur_deck;
  cur_deck.create_deck(players_amount);
  cur_deck.print();
  Player player_number[players_amount];
  for (int j = 0; j < players_amount; j++) {
      player_number[j].print(j);
    }
  for (int i = 0; i < START_CARDS_AMOUNT; i++) {
    for (int j = 0; j < players_amount; j++) {
      player_number[j].start_get_card(cur_deck);
    }
  }
  cur_deck.print();
  for (int j = 0; j < players_amount; j++) {
    player_number[j].print(j);
  }
  int i = 0;
  //for (int i = 0; i < players_amount; (i++)%players_amount) {
  do { 
    std::cout << "In cycle w/ i = " << i << std::endl;
    if (player_number[i].didntlose()) 
      if (Player::get_lost_am() < players_amount - 1) {
        cur_deck.print();
        player_number[i].start_move(cur_deck, i);
      } else {
        std::cout << "Player " << i + 1 << " has won the game!\n";
        return 0;
      }
    i = (i+1)%players_amount;
  } while (true);
}