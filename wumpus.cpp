#include "wumpus.hpp"
#include "event.hpp"
#include <iostream>
Wumpus::Wumpus() :  Event() {}


void Wumpus::percept(){
  std::cout<<"You smell a terrible stench"<<std::endl;
}

char Wumpus::symbol(){
  return 'w';
}

int Wumpus::encounter(){
  std::cout<<"You got eaten by the wumpus!"<<std::endl;
  return 1;
}
