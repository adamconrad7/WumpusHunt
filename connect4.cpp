/******************************************************
 * ** Program: connect_four.cpp
 * ** Author: Adam Conrad
 * ** Date: 12/2/2018
 * ** Description: This game allows users to play the game of connect 4. 
 * ** Input: Number of players, rows, and columns. 
 * ** Output: Gameboard 
 * ******************************************************/
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <string>

using namespace std;
int argcheck(int argcount, char** argv, int&, int& , int&);
void display(int** board, int n, int m);
bool turn( char** array, int nrows, int ncols, char mark, int);
void chararray(int type, int ncols, char** arr, int r, char mark, int currentrow);
char wincheck( char** arr, int nrows, int mcols, char, bool);

int main(int argc, char** argv){
	int nplayers;
	int r;
	int c;
	string inp;
	char mark1;
	char mark2;
	char mark;
	int pn;
	int good = argcheck(argc, argv, nplayers, r, c);
	bool playagain = false;
	char** gameboard = new char*[r];
	if(good){
		do{
			bool win;
			char winner;
			bool firstturn = true;
			char pick;
			int count = 0;
			playagain = false;
			for(int rows =0; rows<r; rows++){
				gameboard[rows] = new char[c];
			}
			if(nplayers == 1){
					cout<<"Enter which symbol you would like to use for a marker."<<endl;
					do{
						cin>>inp;
						if( inp.length() != 1){
							cout<<"Enter a single charachter."<<endl;
						}else{
							mark1 = inp[0];
						}
					}while(inp.length() != 1);
					cout<<"Would you like to move (f)irst, or (s)econd?"<<endl;
					do{
						cin>> inp;
						pick = inp[0];
						if( pick != 'f' && pick != 's'){
							cout<<"Enter an f or an s."<<endl;
						}else if( pick != 'f'){
							firstturn = false;
						}
					}while( pick != 'f' && pick != 's');
				}else{
					cout<<"Choose a symbol for player 1."<<endl;
					do{
						cin>>inp;
						if( inp.length() != 1){
							cout<<"Enter a single charachter."<<endl;
						}else{
							mark1 = inp[0];
						}
					}while(inp.length() != 1);

					cout<<"Choose a symbol for player 2."<<endl;
					do{
						cin>>inp;
						if( inp.length() != 1){
							cout<<"Enter a single charachter."<<endl;
						}else{
							mark2 = inp[0];
						}
					}while(inp.length() != 1);

				}
				do{
					if(count != r*c){
						if(nplayers == 1){
							if(firstturn){
								winner = turn(gameboard, r, c, mark1, 1);
							}else{
								winner = turn(gameboard, r, c, '*', 0);
							}
													}else{
							if(firstturn){
								winner = turn(gameboard, r, c, mark1, 1);
							}else{
								winner = turn(gameboard, r, c, mark2, 2);
							}
													}
						if( winner != '\0'){
							win = true;
										}else{
						win = false;
					}
					firstturn = !firstturn;
					count += 1;
					cout<<"The program counts "<<count<<" symbols."<<endl;
					}else{
						cout<<"There are no more moves to be made. Game over."<<endl;
						win = true;
					}
				}while(!win);
				int currentrow;
				for(currentrow=0; currentrow<r; currentrow++){
					for(int k=1;  k< 5; k++){
						if(k%4 != 0){
							chararray(k, 4*c+1, gameboard, r, winner, currentrow);
						
						}else{
							chararray(2, 4*c+1, gameboard, r, winner, currentrow);
						}
					}
				}
				chararray(1, 4*c+1, gameboard, r, winner, currentrow);
				cout<<"Would you like to (p)lay again, or (q)uit?"<<endl;
				char blickey;
				cin>>blickey;
				if(blickey == 'p'){
					playagain = true;
					cin.clear();
				}else{
					playagain = false;
					cin.clear();
				}
			}while(playagain);

			for(int k=0; k<r; k++){
				delete[] gameboard[k];
			}
			delete[] gameboard;

			return 0;
		}else{
			return 1;
		}
	}

/******************************************************
 * ** Function: argcheck
 * ** Description: Checks if command line arguements are valid.
 * ** Parameters: Count of arguements, array of arguements, rference paramters to be assigned to command line arguements.
 * ** Pre-Conditions: none
 * ** Post-Conditions: none
 * ******************************************************/ 
int argcheck(int argcount, char** argv, int &n, int &x, int &y){
		if(argcount == 4){
			for(int k=1; k<4; k++){
				if( atoi(argv[k]) > 0){
					if( isdigit( *argv[k]) ){
						n = atoi(argv[1]);
						x = atoi(argv[2]);
						y  = atoi(argv[3]);
					}else{
						cout<<"Enter positive integers."<<endl;
						return 0;
					}
				}else{
					cout<<"Enter positive integers."<<endl;
					return 0;
				}
			}
			return 1;
		}else{
			cout<<"Enter a number of players, rows, and columns, respectively."<<endl;
			return 0;
		}				
	}
/******************************************************
 * ** Function: chararray
 * ** Description: Builds strings that make the gameboard.
 * ** Parameters: Type of string to be built, number of columns and rows, token of player, current row of gameboard.
 * ** Pre-Conditions: none
 * ** Post-Conditions: none
 * ******************************************************/ 
void  chararray(int type, int ncols, char** arr, int r, char mark, int currentrow){
				char str[ncols];
		switch (type) {
			case 1:
				for(int k=0; k<ncols; k++){
					str[k] = '~';
				}
				break;
			case 2:
				for(int k=0; k<ncols; k++){
					if(k%4 == 0){
						str[k] = '|';
					}else{
						str[k] = ' ';
					}
				}	
				str[0] = '[';
				str[ncols-1] = ']';
				break;
			case 3:
				for(int k=0; k<ncols; k++){
					if(k%4 == 0){
						str[k] = '|';
					}else{
						str[k] = ' ';
					}
				}
				for(int k=2; k<ncols; k+=4){
					if( arr[currentrow][(k-2)/4] != '\000'){
						str[k] = arr[currentrow][(k-2)/4];
					}
				}
				str[0] = '[';
				str[ncols-1] = ']';
				break;
		}
		cout<<str<<endl;
	//	return str;
}
	
/******************************************************
 * ** Function: turn
 * ** Description: handles a single turn of the game.
 * ** Parameters: array of game piece positions, number of rows and columns, token for player, and player identifier number.
 * ** Pre-Conditions: none
 * ** Post-Conditions: none
 * ******************************************************/ 
bool turn( char** array, int nrows, int mcols, char mark, int playernum){
		//call display function within turn function
		int currentrow;
		int colchoice;
		int colint;
		bool validcol = true;
		int count = 0;
		bool flag = false;
		char colchar;
		string inp;
		do{
			if(playernum != 0){
				cout<<"\n\n Player"<<playernum<<"'s turn:"<<endl;
				for(currentrow=0; currentrow<nrows; currentrow++){
					for(int k=1;  k< 5; k++){
						if(k%4 != 0){
							chararray(k, 4*mcols+1, array, nrows, mark, currentrow);					
						}else{
							chararray(2, 4*mcols+1, array, nrows, mark, currentrow);
						}

					}
				}
				chararray(1, 4*mcols+1, array, nrows, mark, currentrow);
				cout<<"Select a column to place your "<<mark<<" token." <<endl;
				do{
					cin>>inp;
					colchar = inp[0];
					colint = (int)colchar; 
					colchoice = colint - 48;					
					validcol = true;
					if( colint < 49 ||  colint > mcols+48 || inp.length() != 1){
						cout<<"Enter a valid column number."<<endl;
					}
				}while( colint < 49 ||  colint > mcols+48 || inp.length() != 1);
			}else{
				colchoice = rand() % (mcols ) +1;
				cout<<"The computer has chosen comlumn "<<colchoice<<endl;
				validcol = true;
			}
			if( array[0][colchoice-1] != '\000'){
				cout<<"That column is full!"<<endl;
				validcol=false;
				count -= 1;
			}
		}while(validcol == false);
			int r = 0;
			while( r<nrows ){
				if( r == nrows-1 ){
					array[r][colchoice-1] = mark;
					break;	
				}else if( array[r+1][colchoice-1] != '\000'){
					array[r][colchoice-1] = mark;
					break;
				}else{
					r++;
				}
			}
			//Function that checks if the game has been won after, called after each turn
			return wincheck(array, nrows, mcols, mark, flag);
			for(int k=0; k<mcols; k++){
				delete array[k];
			}
			delete[] array;
		}

		char wincheck( char** arr, int nrows, int mcols, char winner, bool flag){
			bool win = false;
			int count;
			for(int r =0; r<nrows-3; r++){
				for(int c=0; c<mcols-3; c++){
					if( arr[r][c] != '\000'){
						if( arr[r][c] == arr[r+1][c+1] && arr[r][c] == arr[r+2][c+2] && arr[r][c] == arr[r+3][c+3]){
							win = true;
						}
					}
				}
			}
			for(int c =0; c<mcols-3; c++){
				for(int r=0; r<nrows; r++){
					if( arr[r][c] != '\000'){
						if( arr[r][c] == arr[r][c+1] && arr[r][c] == arr[r][c+2] && arr[r][c] == arr[r][c+3]){
							win = true;
						}
					}
				}
			}
			for(int r =0; r<nrows-3; r++){
				for(int c=0; c<mcols; c++){
					if( arr[r][c] != '\000'){
						if( arr[r][c] == arr[r+1][c] && arr[r][c] == arr[r+2][c] && arr[r][c] == arr[r+3][c]){
							win = true;
						}
					}
				}
			}
			for(int r=0; r<nrows; r++){
				for(int c=0; c<mcols; c++){
					if( arr[r][c] != '\000'){
						count += 1;
					}
				}
			}
				if(flag){
				return winner;	
			}else if(win){
				cout<<"\n\n\nGame Over!"<<endl;
				return winner;
			}else{
				return '\0';
			}
		}




























