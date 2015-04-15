#include <iostream>
#include <vector>
#include "defines.h"
#include "Connect4.h"

using namespace std;

/*	 0 1 2 3 4 5 6
0	|_|_|_|_|_|_|_|
1	|_|_|_|_|_|_|_|
2	|_|_|_|_|_|_|_|
3	|_|_|_|_|_|_|_|
4	|_|_|_|_|_|_|_|
5	|_|_|_|_|_|_|_|
*/
//Connect4 Class allows you to play against an AI
int main(int argc, char** argv) {
	//Implementation as a class; most of the code in Connect4.cpp
	//X = 1 , O = -1 , EMPTY = 0

	Connect4 game1;
	game1.play_game();
	cin.get();
	cin.get();
	return 0;
}