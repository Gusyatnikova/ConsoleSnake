#include "snake_game.h"
#include "console_handler.h"
#include <thread>

int main() {
	snakeGame::SnakeGame game;
	snakeGame::init(game, {15, 20}, {15 / 2, 20 / 2}, direction::NONE);

	while (!game.game_over) {
		consoleOut::displayGame(game);
		std::this_thread::sleep_for(std::chrono::milliseconds(130));
		direction dir = consoleIn::getInput();
		if (direction::QUIT == dir) {
			game.game_over = true;
		} else {
			consoleOut::clearField(game);
			snakeGame::update(game, dir);
		}
	}
	consoleOut::displayQuitMesg(game);
	return 0;
}