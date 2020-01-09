#ifndef TICTACTOEHELPER_H
#define TICTACTOEHELPER_H

struct Play
{
	int x, y;
};

struct Player
{
	int wins;
	int losses;
	int ties;
	struct Play play;
};

void DisplayGrid(char grid[][3]);

int WinningPlayer(char grid[][3]);

#endif //TICTACTOEHELPER_H