#include "dungeon.hpp"
#include "room.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "explorer.hpp"
#include "bats.hpp"

Dungeon::Dungeon(int n){
  dim = n;
  for(int i = 0; i<n; i++){
    std::vector<Room> rooms; //create a vector of rooms
    for(int j = 0; j<n; j++){
      Room r;             //create a room
      rooms.push_back(r); //put room into vector of rooms
    }
      caves.push_back(rooms); //put vector of rooms into caves
  }
}

Dungeon::~Dungeon(){
  for(int i =0; i<dim; i++){
    for(int j= 0; j<dim; j++){
      if(caves[i][j].getEvent() != NULL){
        delete caves[i][j].getEvent();
      }
    }
  }
}

/*********************************************************************
** Function: fillDungeon
** Description: Stores event pointers in the first six rooms.
** Parameters: n/a
** Pre-Conditions: n/a
** Post-Conditions: First rooms of array have an Event pointer that isn't null.
*********************************************************************/
void Dungeon::fillDungeon(){
  char eventID[] = { 'b', 'p', 'w', 'g'};
  for(int i = 0; i<4; i++){
    caves[0][i].fillRoom(eventID[i]);
  }
  for(int i = 0; i<2; i++){
    caves[1][i].fillRoom(eventID[i]);
  }
}

/*********************************************************************
** Function: getCaves
** Description: Returns 2-d vector of 'room' classes.
** Parameters: n/a
** Pre-Conditions: n/a
** Post-Conditions: Balance is increased if monkeys are owned.
*********************************************************************/
std::vector< std::vector<Room> >& Dungeon::getCaves() {
  return caves;
}

/*********************************************************************
** Function: shuffle
** Description: Takes i 2-d vector of rooms, copies that vector into a single dimension, shuffles this 1-d vector, and then splits it back into two dimensions.
** Parameters: n/a
** Pre-Conditions: n/a
** Post-Conditions: Rooms will be in random order.
*********************************************************************/
void Dungeon::shuffle(){
 srand(time(NULL));
 std::random_device rd;
 std::mt19937 eng(rd());
 std::vector<Room> r;
 for(int i=0; i<dim; i++){
   for(int j=0; j<dim; j++){
     r.push_back(caves[i][j]);//Combine vectors of rooms into a single vector of rooms r.
   }
 }
 std::shuffle(r.begin(), r.end(), eng);//Shuffle r
 int ind = 0;
 for(int i=0; i<dim; i++){
   for(int j=0; j<dim; j++){
     caves[i][j] = r[ind];//Break r into size n vectors and put them back into cave.
     ind++;
   }
 }
}

/*********************************************************************
** Function: drawRows
** Description: Draws the game at it's current s†ate to the command window.
** Parameters: n/a
** Pre-Conditions: n/a
** Post-Conditions: n/a
*********************************************************************/
void Dungeon::drawRows(){
  for(int j = 0; j<dim; j++){
    for(int r = 0; r < 4; r++){ //This loop creates a single length n * 4 string each loop, and creates a single row of caves.
        char str[dim * 4 +1];
        for(int i = 0; i<dim*4 + 1; i++){//This loop puts a single character into a string each loop, and creates a length n*4 string.
          switch(r){
            case 0:{
                str[i] = '~';
              break;
            }
            case 1:
            case 3:
            {
                if(i%4 == 0 || i == 0){
                  str[i] = '|';
                }else{
                  str[i] = ' ';
                }
              break;
            }
            case 2:{
              if(i%4 == 0 || i == 0){
                str[i] = '|';
              }else if(i%2 == 0 && player.getXpos() == j && player.getYpos() == i/4){
                str[i] = 'X';
              }else{
                str[i] = ' ';
              }
              break;
            }
          }
        }
        str[dim * 4 + 1] = '\0';
        std::cout<<str<<std::endl;
      }
  }
  char str[dim * 4 + 1];
  for(int i = 0; i<dim*4 + 1; i++){
   str[i] = '-';
 } //One more loop for last line
  str[dim * 4 + 1] = '\0';
  std::cout<<str<<std::endl;
}

/*********************************************************************
** Function: findStatrt
** Description: Finds empty room within dungeon and calls player constructor with this initial position.
** Parameters: n/a
** Pre-Conditions: n/a
** Post-Conditions: n/a
*********************************************************************/
void Dungeon::findStart(){
   srand(time(NULL));
   std::random_device rd;
   std::mt19937 eng(rd());
   std::uniform_int_distribution<> distr(0, dim - 1);
   int x, y;
   do{
      x = distr(eng);
      y = distr(eng);
   }while(caves[x][y].getEvent() != NULL );
   player.placeExplorer(x,y,dim);
   intX = x;
   intY = y;
}

/*********************************************************************
** Function: bats
** Description: Moves player to a random empty room.
** Parameters: n/a
** Pre-Conditions: n/a
** Post-Conditions: Balance is increased if monkeys are owned.
*********************************************************************/
void Dungeon::bats(){
  srand(time(NULL));
  std::random_device rd;
  std::mt19937 eng(rd());
  std::uniform_int_distribution<> distr(0, dim - 1);
  int x, y;
  do{
     x = distr(eng);
     y = distr(eng);
  }while(caves[x][y].getEvent() != NULL );
  player.placeExplorer(x,y,dim);
  std::cout<<"Player got carried to: "<<x<<", "<<y<<std::endl;
}

/*********************************************************************
** Function: investigateSurroundings
** Description: Checks players position against room they are currently in and the rooms immedieately to their north, south, east, and west.
** Parameters: n/a
** Pre-Conditions: n/a
** Post-Conditions: n/a
*********************************************************************/
void Dungeon::investigateSurroundings(){
  //Take player's position and look at caves nse and west for percepts.
  //Need to add bounds checking incase player is on edge of dungeon.
  int x = player.getXpos();
  int y = player.getYpos();
  if(caves[x][y].getEvent() != NULL){
    int code = caves[x][y].getEvent()->encounter();
    if(code == 1){
      player.death();
    }else if(code == 2){
      player.bag();
    }else if(code == 3){
      bats();
    }
  }else{
    if(x > 0){
      if(caves[x-1][y].getEvent() != NULL){//above
        caves[x-1][y].getEvent()->percept();
      }
    }
    if(x < dim - 1){
      if(caves[x+1][y].getEvent() != NULL){//below
        caves[x+1][y].getEvent()->percept();
      }
    }
    if(y > 0){
      if(caves[x][y-1].getEvent() != NULL ){//left
        caves[x][y-1].getEvent()->percept();
      }
    }
    if(y < dim -1 ){
      if(caves[x][y+1].getEvent() != NULL ){//right
        caves[x][y+1].getEvent()->percept();
      }
    }
  }
}

/*********************************************************************
** Function: getExplorer
** Description: Returns explorer by reference.
** Parameters: n/a
** Pre-Conditions: n/a
** Post-Conditions: n/a
*********************************************************************/
Explorer* Dungeon::getExplorer(){
  return &player;
}

/*********************************************************************
** Function: get_input
** Description: Displays a prompt and validates input until an acceptable response is recivied.
** Parameters: string to be displayed, acceptable responses.
** Pre-Conditions: n/a
** Post-Conditions: n/a
*********************************************************************/
char Dungeon::get_input(std::string prompt, char c1, char c2, char c3, char c4){
  bool flag = false;
  char in = '0';
  do{
    std::cout<<prompt<<std::endl;
    std::cin>> in;
    if(in != c1 && in != c2 && in != c3 && in != c4){
      std::cout<<"Please enter a valid choice."<<std::endl;
      flag = true;
    }else{
      flag = false;
    }
  }while(flag);
  return in;
}

char Dungeon::get_input(std::string prompt, char c1, char c2){
  bool flag = false;
  char in = '0';
  do{
    std::cout<<prompt<<std::endl;
    std::cin>> in;
    if(in != c1 && in != c2){
      std::cout<<"Please enter a valid choice."<<std::endl;
      flag = true;
    }else{
      flag = false;
    }
  }while(flag);
  return in;
}

/*********************************************************************
** Function: checkPlayer
** Description: Checks boolean values of player and returns and integer based on them.
** Parameters: n/a
** Pre-Conditions: n/a
** Post-Conditions: n/a
*********************************************************************/
int Dungeon::checkPlayer(){
  int flag;
  if(player.getDeath() == true){
    flag = 1;
  }else if(player.getBag() == true && player.getWumpus() == true && player.getXpos() == intX && player.getYpos() == intY){
    flag = 2;
  }else{
    flag = 0;
  }
  return flag;
}

/*********************************************************************
** Function: fireArrow
** Description: Checks the next three squares in the direction specidied by the parameter and kills the Wumpus if it is in one of those squares, or wakes it up if not.
** Parameters: char specifying which direction to shoot arrow.
** Pre-Conditions: n/a
** Post-Conditions: n/a
*********************************************************************/
void Dungeon::fireArrow(char c){
  int d = 0;
  player.decArrow();
  int pos = player.getYpos();
  if(c == 'w' || c == 's'){
    pos = player.getXpos();
    if(c == 'w'){
      d = pos;
    }else{
      d = dim - pos - 1;
    }
  }else if(c == 'a'){
    d = pos;
  }else{
    d = dim - pos - 1;
  }
  if( d > 3){
    d = 3;
  }
  bool hit = false;
  for( int i= 0; i<=d; i++){
    switch(c){
      case 'w':{
        if(caves[player.getXpos() - i][player.getYpos()].getEvent() != NULL){//Shooting up, decrease row index
          if( caves[player.getXpos() - i][player.getYpos()].getEvent()->symbol() == 'w'){
            hit = true;
            caves[player.getXpos() - i][player.getYpos()].clearRoom();
          }
        }
        break;
      }
      case 's':{
        if(caves[player.getXpos() + i][player.getYpos()].getEvent() != NULL){//Shooting down, increase row index
          if( caves[player.getXpos() + i][player.getYpos()].getEvent()->symbol() == 'w'){
            hit = true;
            caves[player.getXpos() + i][player.getYpos()].clearRoom();
          }
        }
        break;
      }
      case 'a':{
        if(caves[player.getXpos()][player.getYpos() - i].getEvent() != NULL){
          if( caves[player.getXpos()][player.getYpos() - i].getEvent()->symbol() == 'w'){
            hit = true;
            caves[player.getXpos()][player.getYpos() - i].clearRoom();
          }
        }
        break;
      }
      case 'd':{
        if(caves[player.getXpos()][player.getYpos() + i].getEvent() != NULL){
          if( caves[player.getXpos()][player.getYpos() + i].getEvent()->symbol() == 'w'){
            hit = true;
            caves[player.getXpos()][player.getYpos() + i].clearRoom();
          }
        }
        break;
      }
    }
  }
  if(hit){
    std::cout<<"You killed the wumpus with your arrow!"<<std::endl;
    player.killedWump();
  }else{
    std::cout<<"You missed the wumpus with your arrow!"<<std::endl;
    awakeWumpus();
  }
}

/*********************************************************************
** Function: awakeWumpus
** Description: Moves the wumpus to a random empty cave 75% of the time.
** Parameters: n/a
** Pre-Conditions: n/a
** Post-Conditions: Wumpus is moved 75% of the time.
*********************************************************************/
void Dungeon::awakeWumpus(){
  srand(time(NULL));
  std::random_device rd;
  std::mt19937 eng(rd());
  std::uniform_real_distribution<> distr(0, 1);
  std::uniform_int_distribution<> distrCaves(0, dim - 1);
  float f = distr(eng);
  int x, y;
  for(int i =0; i<dim; i++){
    for(int j= 0; j<dim; j++){
      if(caves[i][j].getEvent() != NULL){
        if( caves[i][j].getEvent()->symbol() == 'w'){
          if(f > .25){
             caves[i][j].clearRoom();
             do{
                x = distrCaves(eng);
                y = distrCaves(eng);
             }while(caves[x][y].getEvent() != NULL && i != x && j != y);
             caves[x][y].fillRoom('w');
          }
        }
      }
    }
  }
}
