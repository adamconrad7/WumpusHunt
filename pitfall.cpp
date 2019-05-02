#include "pitfall.hpp"
#include "event.hpp"
#include <iostream>
Pitfall::Pitfall() :  Event() {}

void Pitfall::percept(){
  std::cout<<"You feel a breeze"<<std::endl;
}

char Pitfall::symbol(){
  return 'p';
}

int Pitfall::encounter(){
  std::cout<<"You fell down a hole!"<<std::endl;
  return 1;
}
