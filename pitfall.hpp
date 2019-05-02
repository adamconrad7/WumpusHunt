#ifndef _pitfall
#define _pitfall
#include "event.hpp"
class Pitfall: public Event{
public:
  Pitfall();
  void percept();
  char symbol();
  int encounter();
};

#endif
