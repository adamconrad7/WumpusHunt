#include "room.hpp"
#include "event.hpp"
#include "pitfall.hpp"
#include "bats.hpp"
#include "gold.hpp"
#include "wumpus.hpp"
#include <iostream>

Room::Room(){
  event = NULL;
}

/*********************************************************************
** Function: fillRooms
** Description: Assigns room's event pointer to specified event.
** Parameters: char specifiying which event to use.
** Pre-Conditions: n/a
** Post-Conditions: n/a
*********************************************************************/
void Room::fillRoom(char c){
  Event* p;
  switch (c) {
    case 'b':
      {
       p = new Bats;
        break;
      }
    case 'p':
      {
        p = new Pitfall;
        break;
      }
    case 'g':
      {
        p = new Gold;
        break;
      }
    case 'w':
      {
        p = new Wumpus;
        break;
      }
  }
    event = p;
}

/*********************************************************************
** Function: getEvent
** Description: Returns pointer to this room's event.
** Parameters: n/a
** Pre-Conditions: n/a
** Post-Conditions: n/a
*********************************************************************/
Event* Room::getEvent(){
  if(event != NULL){
    return event;
  }else{
    return NULL;
  }
}

/*********************************************************************
** Function: clearRoom
** Description: Resets room's event pointer to NULL.
** Parameters: n/a
** Pre-Conditions: n/a
** Post-Conditions: n/a
*********************************************************************/
void Room::clearRoom(){
  event = NULL;
}
