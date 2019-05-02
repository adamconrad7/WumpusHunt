#ifndef _bats
#define _bats
#include "event.hpp"
class Bats: public Event{
public:
  Bats();
  void percept();
  char symbol();
  int encounter();
};

#endif
