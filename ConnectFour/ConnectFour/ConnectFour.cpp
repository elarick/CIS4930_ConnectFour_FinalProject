#include <iostream>
#include <vector>
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

struct C4 {
	int grid[ROW][COL];
};

int heuristic(C4 board);
int score(int line);
void init_board(C4 &board);
void display_board(C4 board);
bool game_over(C4 board);

int main(int argc, char** argv) {

// variables declaration/initialization
	C4 board;
	char init_input;
	int player = INVALID;

// initializations
	init_board(board);

// game start
	cout << "~~~~~****~~~~~ Welcome to ConnectFour! ~~~~~****~~~~~" << endl << endl
		<< "Please choose to be Red or Black.  (enter 'R' or 'B')" << endl;
		
	while (player == INVALID) {
		init_input = cin.get();
		if (init_input == 'R' || init_input == 'r') {
			player = RED;
		}
		else if (init_input == 'B' || init_input == 'b') {
			player = BLACK;
		}
		else {
			player = INVALID;
			cout << "Incorrect input.  Please enter 'R' or 'B'" << endl;
			cin.get();
		}
	}
	
	display_board(board);
	


	cin.get();
	cin.get();

	return 0;
	
}

//Heuristic function searches grid and finds each possible 4-in-a-row line.
//Each line is then scored and totaled to yield a heuristic for the grid
int heuristic(C4 board, int player) {
	int line = 0, total = 0;
	int r, c;

	//Checks all columns, left to right
	for (c = 0; c<7; ++c) {
		for (r = 5; r>2; --r) {
			line = board.grid[r][c] + board.grid[r - 1][c] + board.grid[r - 2][c] + board.grid[r - 3][c];
			total += score(line);
		}
	}
	//Checks all rows, top to bottom
	for (r = 0; r<6; ++r) {
		for (c = 0; c<4; ++c) {
			line = board.grid[r][c] + board.grid[r][c + 1] + board.grid[r][c + 2] + board.grid[r][c + 3];
			total += score(line);
		}
	}
	//Checks all diagonals
	//First check starts from top of grid
	for (r = 0; r<3; ++r) {
		switch (r) {
		case 0:
			//Checks top-left to bottom-right
			for (c = 0; c<3; ++c) {
				line = board.grid[r][c] + board.grid[r + 1][c + 1] + board.grid[r + 2][c + 2] + board.grid[r + 3][c + 3];
				total += score(line);
			}
			//Checks top-right to bottom-left
			for (c = 6; c>3; --c) {
				line = board.grid[r][c] + board.grid[r + 1][c - 1] + board.grid[r + 2][c - 2] + board.grid[r + 3][c - 3];
				total += score(line);
			}
			break;
		case 1:
			for (c = 0; c<2; ++c) {
				line = board.grid[r][c] + board.grid[r + 1][c + 1] + board.grid[r + 2][c + 2] + board.grid[r + 3][c + 3];
				total += score(line);
			}
			for (c = 6; c>4; --c) {
				line = board.grid[r][c] + board.grid[r + 1][c - 1] + board.grid[r + 2][c - 2] + board.grid[r + 3][c - 3];
				total += score(line);
			}
			break;
		case 2:
			line = board.grid[r][0] + board.grid[r + 1][1] + board.grid[r + 2][2] + board.grid[r + 3][3];
			total += score(line);
			line = board.grid[r][6] + board.grid[r + 1][5] + board.grid[r + 2][4] + board.grid[r + 3][3];
			total += score(line);
			break;
		default:
			break;
		}
	}
	//Second check starts from bottom of grid
	for (r = 5; r>2; --r) {
		switch (r) {
		case 5:
			//Checks bottom-right to top-left
			for (c = 6; c>3; --c) {
				line = board.grid[r][c] + board.grid[r - 1][c - 1] + board.grid[r - 2][c - 2] + board.grid[r - 3][c - 3];
				total += score(line);
			}
			//Checks bottom-left to top-right
			for (c = 0; c<3; ++c) {
				line = board.grid[r][c] + board.grid[r - 1][c + 1] + board.grid[r - 2][c + 2] + board.grid[r - 3][c + 3];
				total += score(line);
			}
			break;
		case 4:
			for (c = 6; c>4; --c) {
				line = board.grid[r][c] + board.grid[r - 1][c - 1] + board.grid[r - 2][c - 2] + board.grid[r - 3][c - 3];
				total += score(line);
			}
			for (c = 0; c<2; ++c) {
				line = board.grid[r][c] + board.grid[r - 1][c + 1] + board.grid[r - 2][c + 2] + board.grid[r - 3][c + 3];
				total += score(line);
			}
			break;
		case 3:
			line = board.grid[r][6] + board.grid[r - 1][5] + board.grid[r - 2][4] + board.grid[r - 3][3];
			total += score(line);
			line = board.grid[r][0] + board.grid[r - 1][1] + board.grid[r - 2][2] + board.grid[r - 3][3];
			total += score(line);
			break;
		default:
			break;
		}
	}
	return total;
}

//Score for a line is based on the chips
//The AI's chips = 1 and the player's chips = -1
//For example: if the AI is red and the player is black  ------>   R00R=10  RB0B=-1  R0RR=500  BBBB=-10000
int score(int line) {
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

//init_board function sets all elements in grid to 0
void init_board(C4 &board) {
	int i;
	for (i = 0; i<ROW; ++i) {
		for (int j = 0; j<COL; ++j) {
			board.grid[i][j] = 0;
		}
	}
}

void display_board(C4 board) {
	int i;
	cout << "      a   b   c   d   e   f   g" << endl;
	for (i = 0; i < ROW; ++i) {
		cout << " " << (6 - i) << " ||";
		for (int j = 0; j<COL; ++j) {
			if (board.grid[i][j] == 0) {
				cout << " " << " " << " |";
			}
			else {
				cout << " " << board.grid[i][j] << " |";
			}
		}
		cout << "|" << endl;
	}
}

//game_over function searches grid exactly as heuristic function
//but returns true if any 4-in-a-row line is found
bool game_over(C4 board) {
	int line = 0, r, c;
	bool win = false;

	//Checks all columns, left to right
	for (c = 0; c<7; ++c) {
		for (r = 5; r>2; --r) {
			line = board.grid[r][c] + board.grid[r - 1][c] + board.grid[r - 2][c] + board.grid[r - 3][c];
			if (line == 4 || line == -4) {
				win = true;
			}
		}
	}
	//Checks all rows, top to bottom
	for (r = 0; r<6; ++r) {
		for (c = 0; c<4; ++c) {
			line = board.grid[r][c] + board.grid[r][c + 1] + board.grid[r][c + 2] + board.grid[r][c + 3];
			if (line == 4 || line == -4) {
				win = true;
			}
		}
	}
	//Checks all diagonals
	//First check starts from top of grid
	for (r = 0; r<3; ++r) {
		switch (r) {
		case 0:
			//Checks top-left to bottom-right
			for (c = 0; c<3; ++c) {
				line = board.grid[r][c] + board.grid[r + 1][c + 1] + board.grid[r + 2][c + 2] + board.grid[r + 3][c + 3];
				if (line == 4 || line == -4) {
					win = true;
				}
			}
			//Checks top-right to bottom-left
			for (c = 6; c>3; --c) {
				line = board.grid[r][c] + board.grid[r + 1][c - 1] + board.grid[r + 2][c - 2] + board.grid[r + 3][c - 3];
				if (line == 4 || line == -4) {
					win = true;
				}
			}
			break;
		case 1:
			for (c = 0; c<2; ++c) {
				line = board.grid[r][c] + board.grid[r + 1][c + 1] + board.grid[r + 2][c + 2] + board.grid[r + 3][c + 3];
				if (line == 4 || line == -4) {
					win = true;
				}
			}
			for (c = 6; c>4; --c) {
				line = board.grid[r][c] + board.grid[r + 1][c - 1] + board.grid[r + 2][c - 2] + board.grid[r + 3][c - 3];
				if (line == 4 || line == -4) {
					win = true;
				}
			}
			break;
		case 2:
			line = board.grid[r][0] + board.grid[r + 1][1] + board.grid[r + 2][2] + board.grid[r + 3][3];
			if (line == 4 || line == -4) {
				win = true;
			}
			line = board.grid[r][6] + board.grid[r + 1][5] + board.grid[r + 2][4] + board.grid[r + 3][3];
			if (line == 4 || line == -4) {
				win = true;
			}
			break;
		default:
			break;
		}
	}
	//Second check starts from bottom of grid
	for (r = 5; r>2; --r) {
		switch (r) {
		case 5:
			//Checks bottom-right to top-left
			for (c = 6; c>3; --c) {
				line = board.grid[r][c] + board.grid[r - 1][c - 1] + board.grid[r - 2][c - 2] + board.grid[r - 3][c - 3];
				if (line == 4 || line == -4) {
					win = true;
				}
			}
			//Checks bottom-left to top-right
			for (c = 0; c<3; ++c) {
				line = board.grid[r][c] + board.grid[r - 1][c + 1] + board.grid[r - 2][c + 2] + board.grid[r - 3][c + 3];
				if (line == 4 || line == -4) {
					win = true;
				}
			}
			break;
		case 4:
			for (c = 6; c>4; --c) {
				line = board.grid[r][c] + board.grid[r - 1][c - 1] + board.grid[r - 2][c - 2] + board.grid[r - 3][c - 3];
				if (line == 4 || line == -4) {
					win = true;
				}
			}
			for (c = 0; c<2; ++c) {
				line = board.grid[r][c] + board.grid[r - 1][c + 1] + board.grid[r - 2][c + 2] + board.grid[r - 3][c + 3];
				if (line == 4 || line == -4) {
					win = true;
				}
			}
			break;
		case 3:
			line = board.grid[r][6] + board.grid[r - 1][5] + board.grid[r - 2][4] + board.grid[r - 3][3];
			if (line == 4 || line == -4) {
				win = true;
			}
			line = board.grid[r][0] + board.grid[r - 1][1] + board.grid[r - 2][2] + board.grid[r - 3][3];
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
