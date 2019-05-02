#ifndef _wumpus
#define _wumpus
#include "event.hpp"
class Wumpus: public Event{
public:
  Wumpus();
  void percept();
  char symbol();
  int encounter();
};

#endif
