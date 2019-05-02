#ifndef _explorer
#define _explorer

class Explorer{
  int n_arrows;
  int xpos;
  int ypos;
  int dimension;
  bool hasDied;
  bool hasGold;
  bool killedWumpus;
public:
  Explorer();
  void placeExplorer(int, int, int);
  int getXpos();
  int getYpos();
  void move(char);
  void death();
  void bag();
  void killedWump();
  bool getDeath();
  bool getBag();
  bool getWumpus();
  void decArrow();
  int getArrows();
};

#endif
