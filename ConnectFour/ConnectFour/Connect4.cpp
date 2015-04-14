#include "Connect4.h"
#include<iostream>
#include<vector>
using namespace std;

Connect4::Connect4()
{
	for (int i = 0; i < ROW; ++i) {
		for (int j = 0; j < COL; ++j) {
			grid[i][j] = EMPTY;
		}
	}
}

void Connect4::show_grid()
{
	cout << "\t  1 2 3 4 5 6 7\n";
	for (int i = 0; i < ROW; ++i) {
		cout << "\t|";
		for (int j = 0; j < COL; ++j) {
			cout << " ";
			switch (grid[i][j])
			{
			case X:
				cout << "X";
				break;
			case O:
				cout << "O";
				break;
			default:
				cout << "_";
			}
		}
		cout << " |" << endl;
	}
	cout << endl;
}

void Connect4::play_chip(int chip, int slot)
{
	while (true)
	{
		while (slot < 1 || slot > 7)
		{
			cout << "ERROR: Enter a valid slot (1~7)" << endl;
			cin >> slot;
		}

		for (int x = 5; x >= 0; --x)
		{
			if (grid[x][slot - 1] == EMPTY && (chip == O || chip == X))
			{
				grid[x][slot - 1] = chip;
				return;
			}
		}
		cout << "Invalid Slot or Chip.\n";
		return;
	}
}

int Connect4::score(int line)
{
	int score;
	switch (line) {
	case 4:
		score = 10000;
		break;
	case -4:
		score = -10000;
		break;
	case 3:
		score = 500;
		break;
	case -3:
		score = -500;
		break;
	case 2:
		score = 10;
		break;
	case -2:
		score = -10;
		break;
	case 1:
		score = 1;
		break;
	case -1:
		score = -1;
		break;
	default:
		score = 0;
	}
	return score;
}

int Connect4::heuristic()
{
	int line, total;
	line = 0;
	total = 0;
	int x, y;

	//Checks all columns, left to right
	for (y = 0; y<7; ++y) {
		for (x = 5; x>2; --x) {
			line = grid[x][y] + grid[x - 1][y] + grid[x - 2][y] + grid[x - 3][y];
			total += score(line);
		}
	}
	//Checks all rows, top to bottom
	for (x = 0; x<6; ++x) {
		for (y = 0; y<4; ++y) {
			line = grid[x][y] + grid[x][y + 1] + grid[x][y + 2] + grid[x][y + 3];
			total += score(line);
		}
	}
	//Checks all diagonals
	//First check starts from top of grid
	for (x = 0; x<3; ++x) {
		switch (x) {
		case 0:
			//Checks top-left to bottom-right
			for (y = 0; y<3; ++y) {
				line = grid[x][y] + grid[x + 1][y + 1] + grid[x + 2][y + 2] + grid[x + 3][y + 3];
				total += score(line);
			}
			//Checks top-right to bottom-left
			for (y = 6; y>3; --y) {
				line = grid[x][y] + grid[x + 1][y - 1] + grid[x + 2][y - 2] + grid[x + 3][y - 3];
				total += score(line);
			}
			break;
		case 1:
			for (y = 0; y<2; ++y) {
				line = grid[x][y] + grid[x + 1][y + 1] + grid[x + 2][y + 2] + grid[x + 3][y + 3];
				total += score(line);
			}
			for (y = 6; y>4; --y) {
				line = grid[x][y] + grid[x + 1][y - 1] + grid[x + 2][y - 2] + grid[x + 3][y - 3];
				total += score(line);
			}
			break;
		case 2:
			line = grid[x][0] + grid[x + 1][1] + grid[x + 2][2] + grid[x + 3][3];
			total += score(line);
			line = grid[x][6] + grid[x + 1][5] + grid[x + 2][4] + grid[x + 3][3];
			total += score(line);
			break;
		default:
			break;
		}
	}
	//Second check starts from bottom of grid
	for (x = 5; x>2; --x) {
		switch (x) {
		case 5:
			//Checks bottom-right to top-left
			for (y = 6; y>3; --y) {
				line = grid[x][y] + grid[x - 1][y - 1] + grid[x - 2][y - 2] + grid[x - 3][y - 3];
				total += score(line);
			}
			//Checks bottom-left to top-right
			for (y = 0; y<3; ++y) {
				line = grid[x][y] + grid[x - 1][y + 1] + grid[x - 2][y + 2] + grid[x - 3][y + 3];
				total += score(line);
			}
			break;
		case 4:
			for (y = 6; y>4; --y) {
				line = grid[x][y] + grid[x - 1][y - 1] + grid[x - 2][y - 2] + grid[x - 3][y - 3];
				total += score(line);
			}
			for (y = 0; y<2; ++y) {
				line = grid[x][y] + grid[x - 1][y + 1] + grid[x - 2][y + 2] + grid[x - 3][y + 3];
				total += score(line);
			}
			break;
		case 3:
			line = grid[x][6] + grid[x - 1][5] + grid[x - 2][4] + grid[x - 3][3];
			total += score(line);
			line = grid[x][0] + grid[x - 1][1] + grid[x - 2][2] + grid[x - 3][3];
			total += score(line);
			break;
		default:
			break;
		}
	}
	return total;
}

bool Connect4::game_over()
{
	int line, x, y;
	line = 0;
	bool win = false;

	//Checks top row of grid. If they are all not empty, game is over
	for (y = 0; y < COL; ++y)
	{
		if (grid[0][y] == EMPTY)
			break;
		if (y == 6 && grid[0][y] != EMPTY)
			win = true;
	}

	//Checks all columns, left to right
	for (y = 0; y<COL; ++y) {
		for (x = 5; x>2; --x) {
			line = grid[x][y] + grid[x - 1][y] + grid[x - 2][y] + grid[x - 3][y];
			if (line == 4 || line == -4) {
				win = true;
			}
		}
	}
	//Checks all rows, top to bottom
	for (x = 0; x<ROW; ++x) {
		for (y = 0; y<4; ++y) {
			line = grid[x][y] + grid[x][y + 1] + grid[x][y + 2] + grid[x][y + 3];
			if (line == 4 || line == -4) {
				win = true;
			}
		}
	}
	//Checks all diagonals
	//First check starts from top of grid
	for (x = 0; x<3; ++x) {
		switch (x) {
		case 0:
			//Checks top-left to bottom-right
			for (y = 0; y<3; ++y) {
				line = grid[x][y] + grid[x + 1][y + 1] + grid[x + 2][y + 2] + grid[x + 3][y + 3];
				if (line == 4 || line == -4) {
					win = true;
				}
			}
			//Checks top-right to bottom-left
			for (y = 6; y>3; --y) {
				line = grid[x][y] + grid[x + 1][y - 1] + grid[x + 2][y - 2] + grid[x + 3][y - 3];
				if (line == 4 || line == -4) {
					win = true;
				}
			}
			break;
		case 1:
			for (y = 0; y<2; ++y) {
				line = grid[x][y] + grid[x + 1][y + 1] + grid[x + 2][y + 2] + grid[x + 3][y + 3];
				if (line == 4 || line == -4) {
					win = true;
				}
			}
			for (y = 6; y>4; --y) {
				line = grid[x][y] + grid[x + 1][y - 1] + grid[x + 2][y - 2] + grid[x + 3][y - 3];
				if (line == 4 || line == -4) {
					win = true;
				}
			}
			break;
		case 2:
			line = grid[x][0] + grid[x + 1][1] + grid[x + 2][2] + grid[x + 3][3];
			if (line == 4 || line == -4) {
				win = true;
			}
			line = grid[x][6] + grid[x + 1][5] + grid[x + 2][4] + grid[x + 3][3];
			if (line == 4 || line == -4) {
				win = true;
			}
			break;
		default:
			break;
		}
	}
	//Second check starts from bottom of grid
	for (x = 5; x>2; --x) {
		switch (x) {
		case 5:
			//Checks bottom-right to top-left
			for (y = 6; y>3; --y) {
				line = grid[x][y] + grid[x - 1][y - 1] + grid[x - 2][y - 2] + grid[x - 3][y - 3];
				if (line == 4 || line == -4) {
					win = true;
				}
			}
			//Checks bottom-left to top-right
			for (y = 0; y<3; ++y) {
				line = grid[x][y] + grid[x - 1][y + 1] + grid[x - 2][y + 2] + grid[x - 3][y + 3];
				if (line == 4 || line == -4) {
					win = true;
				}
			}
			break;
		case 4:
			for (y = 6; y>4; --y) {
				line = grid[x][y] + grid[x - 1][y - 1] + grid[x - 2][y - 2] + grid[x - 3][y - 3];
				if (line == 4 || line == -4) {
					win = true;
				}
			}
			for (y = 0; y<2; ++y) {
				line = grid[x][y] + grid[x - 1][y + 1] + grid[x - 2][y + 2] + grid[x - 3][y + 3];
				if (line == 4 || line == -4) {
					win = true;
				}
			}
			break;
		case 3:
			line = grid[x][6] + grid[x - 1][5] + grid[x - 2][4] + grid[x - 3][3];
			if (line == 4 || line == -4) {
				win = true;
			}
			line = grid[x][0] + grid[x - 1][1] + grid[x - 2][2] + grid[x - 3][3];
			if (line == 4 || line == -4) {
				win = true;
			}
			break;
		default:
			break;
		}
	}
	return win;
}

Connect4 & Connect4::operator=(const Connect4 &rhs)
{
	if (this == &rhs)
		return *this;

	int x, y;
	for (x = 0; x < ROW; ++x)
	{
		for (y = 0; y < COL; ++y)
		{
			grid[x][y] = rhs.grid[x][y];
		}
	}
	return *this;
}

void Connect4::play_game()
{
	int turn, slot, x, y;
	Connect4 next_move;
	vector<Connect4> next_moves;

	cout << "~~~~~****~~~~~ Welcome To A Connect Four Game! ~~~~~****~~~~~" << endl << endl
		<< "Would you like to go first or second.  (enter 1 or 2): ";
	cin >> turn;

	while (turn != 1 && turn != 2) 
	{
		cout << "ERROR:  Please enter \"1\" or \"2\"" << endl;
		cin >> turn;
	}

	while (true)
	{
		if (turn == 1)
		{
			if (!game_over())
			{
				//Occasionally, a certain slot is not played
				//Player picks
				show_grid();
				cout << "-----------------------------------" << endl;
				cout << "\nEnter slot: ";
				cin >> slot;
				play_chip(O, slot);
				show_grid();
			}
			else {
				show_grid();
				cout << "\nYou Lose\n";
				break;
			}
			turn = 2;
		}
		else if (turn == 2)
		{
			if (!game_over())
			{
				//AI picks
				for (y = 0; y < COL; ++y)
				{
					for (x = 5; x >= 0; --x)
					{
						if (grid[x][y] == EMPTY)
						{
							next_move = *this;
							next_move.grid[x][y] = 1;
							next_moves.push_back(next_move);
							break;
						}
					}
				}
				next_move = next_moves.at(0);
				for (int i = 1; i < next_moves.size(); ++i)
				{
					if (next_move.heuristic() < next_moves.at(i).heuristic())
						next_move = next_moves.at(i);
				}
				*this = next_move;
				cout << "\nComputer has picked a move\n\n";
			}
			else {
				show_grid();
				cout << "\nYou Win\n";
				break;
			}
			turn = 1;
		}
		else
		{
			//default
			turn = 1;	
		}
	}
}