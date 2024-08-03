#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include "screen.h"

#define WIDTH 8
#define HEIGHT 8

#define ENEMY_COLOR TEXT_RED
#define PLAYER_COLOR TEXT_BLUE

void resetColor() {
	std::cout << "\033[0;0m";
}

void setConsoleStyle(int command) {
	std::cout << "\033[" << command << "m";
}

int main() {
	// Create and Populate Matrix
	int pixels[WIDTH][HEIGHT];

	// Populate Matrix with 0
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++)
			pixels[j][i] = 0;
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j <= 6; j+=2) {
			pixels[i][j+i%2] = 1;
		}
	}
	for (int i = 5; i < 8; i++) {
		for (int j = 0; j <= 6; j+=2) {
			pixels[i][j+i%2] = -1;
		}
	}

	int player = 1, point_player=0, point_enemy=0;
	// 1 = blue
	// -1 = red

	// Game Loop
	while(true) {
		system("cls");
		setConsoleStyle(NEGRITO);
		resetColor();

		bool t = false;

		setConsoleStyle(FOREGROUND_CYAN);
		setConsoleStyle(TEXT_WHITE);
		std::cout << "y";

		setConsoleStyle(TEXT_WHITE);
		std::cout << "\\";

		setConsoleStyle(FOREGROUND_YELLOW);
		setConsoleStyle(TEXT_WHITE);
		std::cout << "x";

		for (char i = 'A'; i <= 'H'; i++) {
			std::cout << " " << i << " ";
		}
		setConsoleStyle(player==1 ? FOREGROUND_BLUE : FOREGROUND_RED);
		std::cout << "   " << std::endl;

		for (int i = 0; i < WIDTH; i++) {
			setConsoleStyle(FOREGROUND_CYAN);
			setConsoleStyle(TEXT_WHITE);
			std::cout << " " << i << " ";

			for (int j = 0; j < HEIGHT; j++) {
				setConsoleStyle(
					t ? FOREGROUND_WHITE : FOREGROUND_BLACK);

				if (pixels[i][j] != 0) {
					setConsoleStyle(pixels[i][j]==1 ? TEXT_BLUE : TEXT_RED);
					std::cout << " S ";
				}
				else
					std::cout << "   ";

				t = !t;
			}

			t = !t;
			setConsoleStyle(player==1 ? FOREGROUND_BLUE : FOREGROUND_RED);
			std::cout << "   " << std::endl;
		}

		if (player == 1)
			setConsoleStyle(FOREGROUND_BLUE);
		else
			setConsoleStyle(FOREGROUND_RED);

		for (int i = 0; i <= WIDTH+1; i++) {
			char p = i < (player==1?point_player:point_enemy) ? 'S': ' ';
			std::cout << " " << p << " ";
		}

		resetColor();
		std::cout << std::endl;

		int posY, destY;
		char crudePosX, crudeDestX;

		std::cout << ": ";
		std::cin >> crudePosX >> posY;
		std::cout << ": ";
		std::cin >> crudeDestX >> destY;

		int posX = ((int) crudePosX) - ((int) 'A');
		int destX = ((int) crudeDestX) - ((int) 'A');

		if (player == pixels[posY][posX]) {
			if (   (destX == posX+1 || destX == posX-1)
				&& (destY == posY+1 || destY == posY-1)
			) {
				if (-player == pixels[destY][destX]) {
					if (player == 1)
						point_player++;
					else
						point_enemy++;

					pixels[destY][destX] = 0;
					pixels[destY+(destY-posY)][destX+(destX-posX)] = pixels[posY][posX];
				} else {
					pixels[destY][destX] = pixels[posY][posX];
				}

				player *= -1;
				pixels[posY][posX] = 0;
				continue;
			} else {
				std::cout << "Can't Go There";
			}
		} else {
			std::cout << "Play with YOUR pieces";
		}
	
		std::cout << std::endl << "Try Again!!";
		getch();
	}

	return 0;
}