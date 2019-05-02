#ifndef _dungeon
#define _dungeon
#include "event.hpp"
#include "room.hpp"
#include <vector>
#include <iostream>
#include "explorer.hpp"

class Dungeon{
  std::vector< std::vector<Room> > caves;
  int dim;
  Explorer player;
  int intX;
  int intY;
public:
  Dungeon(int n);
  ~Dungeon();
  void fillDungeon();
  void print();
  std::vector< std::vector<Room> >& getCaves();
  void shuffle();
  void drawRows();
  void findStart();
  void investigateSurroundings();
  void move(char);
  Explorer* getExplorer();
  char get_input(std::string prompt, char c1, char c2, char c3, char c4);
  char get_input(std::string prompt, char c1, char c2);
  int getDimension();
  int checkPlayer();
  void fireArrow(char);
  void bats();
  void awakeWumpus();
};

#endif
