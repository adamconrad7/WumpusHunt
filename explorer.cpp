#include "explorer.hpp"
#include <iostream>

Explorer::Explorer(){
  hasGold = false;
  killedWumpus = false;
  hasDied = false;
  n_arrows = 3;
}

/*********************************************************************
** Function: placeExplorer
** Description: Updates expplorer's current location
** Parameters: current position in each dimension.
** Pre-Conditions: n/a
** Post-Conditions: n/a
*********************************************************************/
void Explorer::placeExplorer(int x, int y, int dim){
  xpos = x;
  ypos = y;
  dimension = dim;
}

/*********************************************************************
** Function: getXpos/Ypos
** Description: Return's the player's current position in the caves.
** Parameters: Direction to move
** Pre-Conditions: n/a
** Post-Conditions: n/a
*********************************************************************/
int Explorer::getXpos(){
  return xpos;
}

int Explorer::getYpos(){
  return ypos;
}

/*********************************************************************
** Function: move
** Description: Moves player one cave in the specified direction, with bounds checking.
** Parameters: n/a
** Pre-Conditions: n/a
** Post-Conditions: n/a
*********************************************************************/
void Explorer::move(char c){
  switch (c){
    case 'w':{
      if(xpos > 0){
       xpos--;
      }else{
        std::cout<<"You are on the edge of the cave."<<std::endl;
      }
      break;
    }
    case 's':{
      if(xpos < dimension - 1 ){
        xpos++;
      }else{
        std::cout<<"You are on the edge of the cave."<<std::endl;
      }
      break;
    }
    case 'a':{
      if( ypos > 0){
        ypos--;
      }else{
        std::cout<<"You are on the edge of the cave."<<std::endl;
      }

      break;
    }
    case 'd':{
      if( ypos < dimension - 1){
        ypos++;
      }else{
        std::cout<<"You are on the edge of the cave."<<std::endl;
      }
      break;
    }
  }
}

/*********************************************************************
** Function: death/bag/killedWumpus
** Description: Modifies booleans that track important aspects of the game.
** Parameters: n/a
** Pre-Conditions: n/a
** Post-Conditions: n/a
*********************************************************************/
void Explorer::death(){
  hasDied = true;
}

void Explorer::bag(){
  hasGold = true;
}

void Explorer::killedWump(){
  killedWumpus = true;
}

/*********************************************************************
** Function: decArrow
** Description: Decemenets the amount of arrows player has.
** Parameters: n/a
** Pre-Conditions: n/a
** Post-Conditions: n/a
*********************************************************************/
void Explorer::decArrow(){
  n_arrows--;
}

/*********************************************************************
** Function: getBag/Death/Arrows/Wumpus
** Description: Getters that return a value relating to the state of the game.
** Parameters: n/a
** Pre-Conditions: n/a
** Post-Conditions: n/a
*********************************************************************/
bool Explorer::getBag(){
  return hasGold;
}

bool Explorer::getDeath(){
  return hasDied;
}

int Explorer::getArrows(){
  return n_arrows;
}

bool Explorer::getWumpus(){
  return killedWumpus;
}
