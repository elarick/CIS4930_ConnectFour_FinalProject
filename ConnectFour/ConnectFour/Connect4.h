#ifndef CONNECT4_H
#define CONNECT4_H
#include<vector>
#include "defines.h"
using namespace std;

class Connect4
{
public:
	Connect4();
	void show_grid();
	void play_chip(int chip, int slot);
	Connect4 & Connect4::operator=(const Connect4 &rhs);
	void play_game();
	int heuristic();
	int score(int line);
	bool game_over();
private:
	int grid[ROW][COL];
};
#endif