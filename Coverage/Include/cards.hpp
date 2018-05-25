#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>
#include <unistd.h>
#include <algorithm>

enum Card_type {
  EXPLODE, //0
  DIFUSE,  //1
  SLAP,    //2
  SKIP,    //3
  SHUFFLE, //4
  FORECAST //5
};

enum {
  AMOUNT_OF_CARD_TYPES = 6
};

class Card {
  Card_type type;
  int card_key;
public:
  Card(Card_type);
  void change_key();
  Card_type get_type() { return type; }
  int get_key() { return card_key; }
};

std::ostream& operator<<(std::ostream&, Card);

struct Deck {
  std::vector<Card> card_vector;
public:
  void create_deck(int);
  int size () { return card_vector.size(); }
  void print() {
    std::cout << "  In deck: \n";
    for (auto a : card_vector)
      std::cout << "  " << a.get_type() << std::endl;
  }
  void push_explode();
  void shuffle();
  void forecast();
};

class Player {
  int hand[AMOUNT_OF_CARD_TYPES];
  bool lost;
  static int lost_amount;
  static int players_amount;
public:
  Player (): lost(false) {
    for (int j = 0; j < AMOUNT_OF_CARD_TYPES; j++) {
      hand[j] = 0;
    }
  }
  int slap(int);
  int start_move(Deck&, int);
  int continue_move(Deck&, int);
  void get_card(Deck&);
  void start_get_card(Deck&);
  bool didntlose () { return !lost; }
  static int get_lost_am () { return lost_amount; }
  static void set_p_am (int a) { players_amount = a; }
  static void inc_lost_am () { lost_amount++ ;}
  void print(int num) {
    std::cout << "Player " << num + 1 << " has:\n"; 
    for (int i = 0; i < AMOUNT_OF_CARD_TYPES; i++) {
      std::cout <<  "  " << hand[i] << " cards of type " << i << std::endl;
    }
  }
  char print_self();
};

struct Exception {
  std::string reason;
  Exception(const std::string &reason)
    : reason(reason) {}
};
