#include <windows.h>
#include <iostream>
#include <conio.h>
#include "console_handler.h"

namespace consoleOut {
	void showConsoleCursor(bool showFlag)
	{
		HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_CURSOR_INFO     cursorInfo;
		GetConsoleCursorInfo(out, &cursorInfo);
		cursorInfo.bVisible = showFlag;
		SetConsoleCursorInfo(out, &cursorInfo);
	}

	void cursor_to_xy(const int& x, const int& y) {
		COORD c;
		c.X = x;
		c.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	}

	void displayBorders(const snakeGame::SnakeGame& game) {
		cursor_to_xy(0, 0);
		for (size_t i = 0; i < game.gf.borders.size(); ++i) {
			cursor_to_xy(game.gf.borders[i].column, game.gf.borders[i].row);
			std::cout << border_pic;
		}
	}

	void displaySnake(const snakeGame::SnakeGame& game) {
		cursor_to_xy(game.snake.items[0].column, game.snake.items[0].row);
		std::cout << head_pic;
		for (size_t i = 1; i < game.snake.items.size(); ++i) {
			cursor_to_xy(game.snake.items[i].column, game.snake.items[i].row);
			std::cout << body_pic;
		}
	}

	void displayFood(const snakeGame::SnakeGame& game) {
		cursor_to_xy(game.food_pos.column, game.food_pos.row);
		std::cout << food_pic;
		cursor_to_xy(0, 25);
		/*
		HWND myconsole = GetConsoleWindow();
		//Get a handle to device context
		HDC mydc = GetDC(myconsole);

		int pixel = 0;

		//Choose any color
		COLORREF COLOR = RGB(255, 10, 5);

		//Draw pixels
		for (double i = 0; i < 3.14 * 4; i += 0.05)
		{
			SetPixel(mydc, pixel, (int)(50 + 25 * cos(i)), COLOR);
			pixel += 1;
		}

		ReleaseDC(myconsole, mydc);
		*/
	}

	void clearField(const snakeGame::SnakeGame& game) {
		cursor_to_xy(game.snake.items[0].column, game.snake.items[0].row);
		std::cout << ' ';
		for (size_t i = 1; i < game.snake.items.size(); ++i) {
			cursor_to_xy(game.snake.items[i].column, game.snake.items[i].row);
			std::cout << ' ';
		}
		cursor_to_xy(game.food_pos.column, game.food_pos.row);
		std::cout << ' ';
	}

	void clearBorders(const gameField::GameField& gf) {
		for (size_t i = 0; i < gf.borders.size(); ++i) {
			cursor_to_xy(gf.borders[i].column, gf.borders[i].row);
			std::cout << ' ';
		}
	}

	void displayGame(const snakeGame::SnakeGame& game) {
		showConsoleCursor(false);
		if (!game.started) {
			displayBorders(game);
		}
		displaySnake(game);
		displayFood(game);
	}
	void displayQuitMesg(const snakeGame::SnakeGame& game) {
		clearField(game);
		clearBorders(game.gf);
		cursor_to_xy(game.gf.width / 2, game.gf.height / 2 - game.gf.height / 4);
		std::cout << "See you next time!\n\n"; 
		cursor_to_xy((game.gf.width / 2) + 4 , game.gf.height / 2 - game.gf.height / 4 + 2);
		std::cout << final_pic << "\n\n"; 
		cursor_to_xy((game.gf.width / 2) - 6, game.gf.height / 2 - game.gf.height / 4 + 4);
		std::cout << "Press Enter to close this window\n";
		std::cin.get();
	}
}

namespace consoleIn {
	direction getInput() {
		if (_kbhit()) {
			switch (_getch()) {
			case 'w':
				return direction::UP;
			case 's':
				return direction::DOWN;
			case 'a':
				return direction::LEFT;
			case 'd':
				return direction::RIGHT;
			case 'p':
				return direction::QUIT;
			}
		}
		return direction::NONE;
	}


}
