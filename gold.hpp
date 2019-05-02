#ifndef _gold
#define _gold
#include "event.hpp"
class Gold: public Event{
public:
  Gold();
  void percept();
  char symbol();
  int encounter();
};

#endif
