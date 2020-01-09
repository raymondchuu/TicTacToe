#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "TicTacToeHelper.h"

int main()
{
	struct Player player1, player2;
	// y by x
	char ticTacToeGrid[3][3] = { ' ', ' ', ' ',  //row 1, cols 1-3
								 ' ', ' ', ' ',  //row 2, cols 1-3
								 ' ', ' ', ' ' };//row 3, cols 1-3

	int winningPlayer = -1;
	int gridCount = 0;
	int rc;
	int isValid;
	FILE* fp = fopen("stats.txt", "r");
	if (fp == NULL) {//The file does not exist
		//Initialize wins, losses and ties for both players
		player1.wins = 0;
		player1.losses = 0;
		player1.ties = 0;
		player2.wins = 0;
		player2.losses = 0;
		player2.ties = 0;
	}
	else {//The file exists. Scan in the wins, losses and ties for each player
		fscanf(fp, "%d;%d;%d", &player1.wins, &player1.losses, &player1.ties);
		fscanf(fp, "%d;%d;%d", &player2.wins, &player2.losses, &player2.ties);
		fclose(fp);
	}

	do {
		do {
			isValid = 0;
			printf("Player 1 enter an X (ypos, xpos): ");
			rc = scanf("%d, %d", &player1.play.y, &player1.play.x);
			if (rc == 2 &&//Did we scan two integers
				player1.play.y > 0 && player1.play.y < 4 &&//Is y between 1 and 3
				player1.play.x > 0 && player1.play.x < 4 &&//Is x between 1 and 3
				ticTacToeGrid[player1.play.y - 1][player1.play.x - 1] == ' ') {//Is the space empty
				isValid = 1;
			}
			else {
				printf("Invalid position!\n");
			}
		} while (isValid == 0);
		ticTacToeGrid[player1.play.y - 1][player1.play.x - 1] = 'X';
		++gridCount;
		DisplayGrid(ticTacToeGrid);
		winningPlayer = WinningPlayer(ticTacToeGrid);
		if (winningPlayer == -1 && gridCount < 9) {
			do {
				isValid = 0;
				printf("Player 2 enter an O (ypos, xpos): ");
				rc = scanf("%d, %d", &player2.play.y, &player2.play.x);
				if (rc == 2 &&//Did we scan two integers
					player2.play.y > 0 && player2.play.y < 4 &&//Is y between 1 and 3
					player2.play.x > 0 && player2.play.x < 4 &&//Is x between 1 and 3
					ticTacToeGrid[player2.play.y - 1][player2.play.x - 1] == ' ') {//Is the space empty
					isValid = 1;
				}
				else {
					printf("Invalid position!\n");
				}
			} while (isValid == 0);
			ticTacToeGrid[player2.play.y - 1][player2.play.x - 1] = 'O';
			++gridCount;
			DisplayGrid(ticTacToeGrid);
			winningPlayer = WinningPlayer(ticTacToeGrid);
		}
	} while (winningPlayer == -1 && gridCount < 9);

	if (winningPlayer != -1) {
		printf("\nGAME OVER: PLAYER %d has won in %d moves\n", winningPlayer, gridCount);
	}
	else {
		printf("\nGAME OVER: No one won\n");
	}
	if (winningPlayer == -1) {
		++player1.ties;
		++player2.ties;
	}
	else if (winningPlayer == 1) {
		++player1.wins;
		++player2.losses;
	}
	else if (winningPlayer == 2) {
		++player2.wins;
		++player1.losses;
	}
	//double winningRatio;
	printf("Player 1 has a record of %d wins %d losses and %d ties\n", player1.wins, player1.losses, player1.ties);
	printf("Player 2 has a record of %d wins %d losses and %d ties\n", player2.wins, player2.losses, player2.ties);
	fp = fopen("stats.txt", "w");
	if (fp != NULL) {//Store the updated wins, losses and ties to the file
		fprintf(fp, "%d;%d;%d\n", player1.wins, player1.losses, player1.ties);
		fprintf(fp, "%d;%d;%d\n", player2.wins, player2.losses, player2.ties);
		fclose(fp);
	}
	return 0;
}