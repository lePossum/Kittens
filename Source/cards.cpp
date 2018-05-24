#include "cards.hpp"

Card::Card(Card_type c_type) {
  type = c_type;
  card_key = std::rand();
}

void Card::change_key(){
  card_key = std::rand();
}

std::ostream& operator<<(std::ostream& str, Card output_c) {
  switch (output_c.get_type()) {
    case (0):
      std::cout << "EXPLODE";
      break;
    case (1):
      std::cout << "DIFUSE";
      break;
    case (2):
      std::cout << "SLAP";
      break;
    case (3):
      std::cout << "SKIP";
      break;
    case (4):
      std::cout << "SHUFFLE";
      break;
    case (5):
      std::cout << "FORECAST";
      break;
  }
}

void Deck::create_deck(int amount_of_players) {
  int container[AMOUNT_OF_CARD_TYPES];

  container[EXPLODE] = amount_of_players - 1;
  container[DIFUSE] = 6;
  container[SLAP] = 4;
  container[SKIP] = 4;
  container[SHUFFLE] = 4;
  container[FORECAST] = 5;

  int cards_in_cont = 0, i;
  for (i = 0; i < AMOUNT_OF_CARD_TYPES; i++) {
    cards_in_cont += container[i];
  }
  bool iteration;
  while ( cards_in_cont > 0 ) {
    iteration = true;
    while (iteration) {
      i = std::rand() % AMOUNT_OF_CARD_TYPES;
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
          if (i >=2) {
            card_vector.push_back(Card((Card_type)0));
            auto temp = card_vector[i];
            card_vector[i] = card_vector[i - 2];
            card_vector[i - 2] = temp;
            break;
          }
        } 
      case '1':
        if (i >=1) {
          card_vector.push_back(Card((Card_type)0));
          auto temp = card_vector[i];
          card_vector[i] = card_vector[i - 1];
          card_vector[i - 1] = temp;
          break;
        }
      case '0':
        card_vector.push_back(Card((Card_type)0));
        break;
      case '4':
        {
          auto iter = card_vector.begin();
          card_vector.insert(iter, Card((Card_type)0));
        }
        break;
      default : 
        {
          iteration = false;
          std::cout << "Wrong number input,\n try again: ";
        }
    }
  } while (!iteration);
}

void Deck::shuffle() {
  std::sort(card_vector.begin(), card_vector.end(),
    [] (Card a, Card b) {
      return a.get_key() > b.get_key();
    });
  for (auto& n : card_vector) {
    n.change_key();
  }
}

void Deck::forecast() {
  int i = card_vector.size();
  if (i >= 1) {
    std::cout << " 1st card is " << card_vector[i - 1] << std::endl;
    if (i >=2) {
      std::cout << " 2nd card is " << card_vector[i - 2] << std::endl;
      if (i >= 3) {
        std::cout << " 3rd card is " << card_vector[i - 3] << std::endl;
      }
    }
  }
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

char Player::print_self() {
  char c;
  std::cout << "Choose, what you do:\n";
    std::cout << " if you want to get a card  enter '1' " << std::endl;
  if (hand[2] > 0)
    std::cout << " to slap an opponent        enter '2' " << std::endl;
  if (hand[3] > 0)
    std::cout << " to skip your step          enter '3' " << std::endl;
  if (hand[4] > 0)
    std::cout << " to shuffle the deck        enter '4' " << std::endl;
  if (hand[5] > 0)
    std::cout << " to see the future          enter '5' " << std::endl;
  if (hand[1] > 0) {
    std::cout << " also you have " << hand[1] << " difuse cards" << std::endl;
  }
  do {
    std::cout << "Your choice: ";
    while (!(std::cin >> c) || (std::cin.peek() != '\n')) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
      std::cout << "Input error! Retry: ";
    }
  } while ((c < 1 + '0') || (c >= AMOUNT_OF_CARD_TYPES + '0'));
  return c;
}

int Player::slap (int cur_p) {
  char c;
  do {
    std::cout << "Choose a player to slap: ";
    while (!(std::cin >> c) || (std::cin.peek() != '\n')) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
      std::cout << "Input error! Retry: ";
    }
    if (c == '0' + cur_p) {
      std::cout << "You cannot slap yourself\n";
    }
    if ((c < '1') || (c > players_amount + '0')) {
      std::cout << "You have to choose players from 1 to " << players_amount << std::endl;
    }
  } while ((c < '1') || (c > players_amount + '0') || (c == cur_p + '0'));
  return (c - '0') - cur_p;
}

int Player::continue_move(Deck& cur_deck, int p_num) {
  int j;
  bool iteration = true;
  do {
    j = print_self();
    switch (j) {
      case '1' :
        iteration = false;
        break;
      case '2' :
        if(hand[SLAP] > 0) {
          hand[SLAP]--;
          return slap(p_num);
        } else {
          std::cout << "You don't have any SLAP cards\n";
          break;
        }
      case '3' :
        if (hand[SKIP] > 0) {
          hand[SKIP]--;
          return 1;
        } else {
          std::cout << "You don't have any SKIP cards\n";          
          break;
        }
      case '4' :
        if (hand[SHUFFLE] > 0) {
          hand[SHUFFLE]--;
          cur_deck.shuffle();
          break;
        } else {
          std::cout << "You don't have any SHUFFLE cards\n";          
          break;
        }
      case '5' :
        if (hand[FORECAST] > 0) {
          hand[FORECAST]--;
          cur_deck.forecast();
          break;
        } else {
          std::cout << "You don't have any FORECAST cards\n";                    
          break;
        }
    }
  } while (iteration);
  return 0;
}

int Player::start_move(Deck& cur_deck, int i) {
  char c = 0;//input_char
  if (system("CLS")) system("clear");
  std::cout << "Player " << i + 1 << std::endl;
  int a = continue_move(cur_deck, i + 1);
  if (a) return a - 1;
  get_card(cur_deck);
  //print(i);
  //cur_deck.print();
  if (hand[EXPLODE] > 0) {
    if (hand[DIFUSE] > 0) {
      std::cout << "If you don't want to use your DIFUSE card,\n";
      std::cout << "enter 'n'\n";
      while (!(std::cin >> c) || (std::cin.peek() != '\n')) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        std::cout << "Input error! Retry: ";
      }
      if ((c == 'n') || (c == 'N')) {
        std::cout << "GG you chose your lose :( \n";
        lost = true;
        Player::inc_lost_am();
        return 0;
      } else {
        std::cout << "You used your DIFUSE card\n";
        hand[DIFUSE]--;
        hand[EXPLODE]--;
        //cur_deck.card_vector.push_back(Card(EXPLODE));
        cur_deck.push_explode();
      }
    } else {
      std::cout << "You lost, good luck next :( \n";
      //std::cin >> c;
      lost = true;
      Player::inc_lost_am();
      return 0;
    }
  }
  return 0;
}
