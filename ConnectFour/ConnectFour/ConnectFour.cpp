#include <iostream>
#include <vector>
#include "Connect4.h"
#include "defines.h"

using namespace std;

/*	 0 1 2 3 4 5 6	  c
  0	|_|_|_|_|_|_|_|
  1	|_|_|_|_|_|_|_|
  2	|_|_|_|_|_|_|_|
  3	|_|_|_|_|_|_|_|
  4	|_|_|_|_|_|_|_|
  5	|_|_|_|_|_|_|_|
  
  y
*/

int main(int argc, char** argv) {
	//Implementation as a class; most of the code in Connect4.cpp
	//X = 1 , O = -1 , EMPTY = 0
	Connect4 game;
	game.show_grid();

	game.play_chip(X, 4);
	game.play_chip(O, 3);
	game.play_chip(X, 5);
	game.show_grid();
	cin.get();
	return 0;
}