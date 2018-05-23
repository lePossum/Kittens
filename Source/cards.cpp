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
  std::srand(unsigned(std::time(0)));
  container[EXPLODE] = amount_of_players - 1;
  container[DIFUSE] = 6;
  std::cout << "Container has: " << container[EXPLODE] 
    << " explodes and " << container[DIFUSE] << 
    " difuses" << std::endl;
  int cards_in_cont = 0, i;
  for (i = 0; i < AMOUNT_OF_CARD_TYPES; i++) {
    cards_in_cont += container[i];
  }
  bool iteration;
  while ( cards_in_cont > 0 ) {
    iteration = true;
    while (iteration) {
      i = std::rand() % AMOUNT_OF_CARD_TYPES;
      std::cout << "Number of card type is " << i << std::endl;
      if (container[i] > 0) {
        container[i]--;
        cards_in_cont--;
        card_vector.push_back(Card((Card_type)i));// does it work
        iteration = false;
      }
    } 
  }
  return;
}

void Deck::push_explode() {
  char c;
  std::cout << "If you want to put EXPLODE card:\n";
  std::cout << "  at the top of the deck,    enter 0\n";
  std::cout << "  after next card,           enter 1\n";
  std::cout << "  third in the deck,         enter 2\n";
  std::cout << "  at the bottom of the deck, enter 4\n";
  int i = size();
  bool iteration;
  do {
    std::cin >> c;
    iteration = true;
    switch (c) {
      case '2':
        {
          std::cout << "   IN CASE 2" << std::endl;
          if (i >=2) {
            card_vector.push_back(Card((Card_type)0));
            auto temp = card_vector[i];
            card_vector[i] = card_vector[i - 2];
            card_vector[i - 2] = temp;
            break;
          }
        } 
      case '1':
        
          std::cout << "   IN CASE 1" << std::endl;
          if (i >=1) {
            card_vector.push_back(Card((Card_type)0));
            auto temp = card_vector[i];
            card_vector[i] = card_vector[i - 1];
            card_vector[i - 1] = temp;
            break;
          }
        
      case '0':
        
          std::cout << "   IN CASE 0" << std::endl;
          card_vector.push_back(Card((Card_type)0));
        
        break;
      case '4':
        {
          std::cout << "   IN CASE 4" << std::endl;
          auto iter = card_vector.begin();
          card_vector.insert(iter, Card((Card_type)0));
        }
          break;
      default : 
        {
          iteration = false;
          std::cout << "Wrong number inputted\n, try again: ";
        }
    }
  } while (!iteration);
}

void Player::get_card(Deck& cur_deck) {
  int i = cur_deck.size();
  auto got_card = cur_deck.card_vector[i-1];
  hand[got_card.get_type()]++;
  cur_deck.card_vector.pop_back();
}

void Player::start_get_card(Deck& cur_deck) {
  int i = cur_deck.size();
  bool swap_necessity = false, success_flag = false;
  Card final_card(EXPLODE);
  //cur_deck.print();
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
          [cur_deck.size() - 1];
        cur_deck.card_vector
          [cur_deck.size() - 1] = 
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

void Player::start_move(Deck& cur_deck, int i) {
  char c = 0;//input_char
  get_card(cur_deck);
  if (system("CLS")) system("clear");
  print(i);
  //cur_deck.print();
  std::cout << "Player " << i + 1 << std::endl;
  if (hand[EXPLODE] > 0) {
    if (hand[DIFUSE] > 0) {
      std::cout << "If you don't want to use your DIFUSE card,\n";
      std::cout << "enter n\n";
      std::cin >> c;
      if (c == 'n') {
        std::cout << "GG u chose your lose :( \n";
        lost = true;
        Player::inc_lost_am();
        return;
      } else {
        std::cout << "U used your DIFUSE card\n";
        hand[DIFUSE]--;
        hand[EXPLODE]--;
        //cur_deck.card_vector.push_back(Card(EXPLODE));
        cur_deck.push_explode();
      }
    } else {
      std::cout << "Prepare for your lose :( \n";
      sleep(1);
      lost = true;
      Player::inc_lost_am();
      return;
    }
  }
  continue_move(cur_deck);
}

void Player::continue_move(Deck& cur_deck) {
  return;
}