#include "bats.hpp"
#include "event.hpp"
#include <iostream>
Bats::Bats() :  Event() {}


void Bats::percept(){
  std::cout<<"You hear wings flapping."<<std::endl;
}

char Bats::symbol(){
  return 'b';
}

int Bats::encounter(){
  std::cout<<"You found da bats"<<std::endl;
  return 3;
}
