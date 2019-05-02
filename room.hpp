#ifndef _room
#define _room
#include "event.hpp"
#include "pitfall.hpp"
#include "bats.hpp"
#include "gold.hpp"
#include "wumpus.hpp"

class Room{
  Event* event;
public:
  Room();

  void fillRoom(char);
  Event* getEvent();
  void clearRoom();
};

#endif
