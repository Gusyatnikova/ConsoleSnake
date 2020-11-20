#include "snake_game.h"
//todo: delete afer testing!
#include <iostream>

namespace snakeGame {
	position generateFoodPosition(const GameField&, const Snake&, position = { -1, -1 });
	void init(SnakeGame& game, const position& size,
		const position& start_pos, const direction& start_dir) {
		gameField::init(game.gf, { size.row + 1, size.column + 1 });
		snake::init(game.snake, start_pos, start_dir);
		game.food_pos = generateFoodPosition(game.gf, game.snake);
		game.prev_dir = direction::NONE;
		game.game_over = false;
		game.started = false;
	}

	void update(SnakeGame& game, const direction& dir) {
		if (game.snake.items.size() > 2) {
			int a = 4;
		}
		game.started = true;
		if (direction::NONE == dir) {
			snake::moveTo(game.snake, game.prev_dir);
		}
		else {
			snake::moveTo(game.snake, dir);
			game.prev_dir = dir;
		}
		position head_pos = snake::getHeadPos(game.snake);
		if (head_pos.column == game.food_pos.column &&
			head_pos.row == game.food_pos.row) {
			snake::addItem(game.snake);
			game.food_pos = generateFoodPosition(game.gf, game.snake, game.food_pos);
			
		}
		if (gameField::hasCollide(game.gf, head_pos) ||
			snake::hasCollide(game.snake, head_pos)) {
			game.game_over = true;
		}
	}

	position generateFoodPosition(const GameField& gf, const Snake& snake, position prev_food_pos) {
		//todo: generator dont't work
		std::random_device generator;
		std::mt19937 mt(generator());
		std::uniform_int_distribution<int> height_distribution(1, gf.height - 1);
		std::uniform_int_distribution<int> width_distribution(1, gf.width - 1);
		position generated_pos;
		bool is_initial = false;
		bool equal_to_prev = false;
		if (prev_food_pos.column < 0 && prev_food_pos.row < 0) is_initial = true;
		do {
			generated_pos = { height_distribution(mt), width_distribution(mt) };
			if (!is_initial)
				equal_to_prev = (prev_food_pos.column == generated_pos.column) &&
				(prev_food_pos.row == generated_pos.row);
		} while (gameField::hasCollide(gf, generated_pos) ||
			snake::onSnake(snake, generated_pos) || equal_to_prev);
		return generated_pos;
	}
}