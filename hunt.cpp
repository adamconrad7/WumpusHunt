/*********************************************************************
** Program Filename:   zooTycoon.cpp
** Author: Adam Conrad
** Date: 2/18/19
** Description: A game where users operate a zoo. They can buy animals of three different species.
** Input: Type and amount of animals to buy, type of food to use.
** Output: Current day, available balance, price of food, amount of animals, net income for a single day, and special event information.
*********************************************************************/
#include <iostream>
#include "dungeon.hpp"
#include "room.hpp"
#include "explorer.cpp"
#include <vector>

int main(int argc, char* argv[]){
  char c = *argv[1];
  int n = (int)c - 48;
  std::string str1 = "Would you like to (m)ove or (s)hoot?";
  std::string str2 = "Direction: WASD";
  Dungeon d(n);
  d.fillDungeon();
  d.shuffle();
  d.findStart();
  Explorer* e = d.getExplorer();
  bool end = true;
  do{
    d.drawRows();
    char pick = d.get_input(str1, 'm', 's');
    char direction = d.get_input(str2, 'w', 'a', 's', 'd' );
    if( pick == 'm'){
      e->move(direction);
    }else{
      if( e->getArrows() > 0){
        d.fireArrow(direction);
        std::cout<<"you have "<<e->getArrows()<<" arrows left."<<std::endl;
      }else{
        std::cout<<"Out of arrows!"<<std::endl;
      }
    }
    d.investigateSurroundings(); // Probe ca ves nsew for percepts.
    int flag = d.checkPlayer();
    if(flag == 0){
      end = false;
    }else if(flag == 1){
      std::cout<<"Game Over"<<std::endl;
      end = true;
    }else if(flag == 2){
      std::cout<<"You win!!"<<std::endl;
      end = true;
    }
  }while(!end);
  return 0;
}
