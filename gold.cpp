#include "gold.hpp"
#include "event.hpp"
#include <iostream>
Gold::Gold() :  Event() {}


void Gold::percept(){
  std::cout<<"You notice a faint glimmer."<<std::endl;
}

char Gold::symbol(){
  return '$';
}

int Gold::encounter(){
 std::cout<<"You found the gold!"<<std::endl;
 return 2;
}
