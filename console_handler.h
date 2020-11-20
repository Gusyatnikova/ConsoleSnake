#pragma once
#include <string>
#include "snake_game.h"


namespace consoleOut {
	const unsigned char border_pic = 176;
	const char body_pic = 'o';
	const char head_pic = 'O';
	const char food_pic = 'F';
	void displayGame(const snakeGame::SnakeGame&);
	void displayQuitMesg(const snakeGame::SnakeGame&);
	void clearField(const snakeGame::SnakeGame&);
	const std::string final_pic = "( ^_^)/";

}

namespace consoleIn{
	direction getInput();
}