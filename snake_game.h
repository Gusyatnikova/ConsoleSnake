#pragma once
#include <random>
#include "game_field.h"
#include "snake.h"

namespace snakeGame {
	using gameField::GameField;
	using snake::Snake;
	struct SnakeGame {
		GameField gf;
		Snake snake;
		position food_pos;
		direction prev_dir;
		bool game_over;
		bool started;
	};
	void init(SnakeGame&, const position&, const position&, const direction&);
	void update(SnakeGame&, const direction&);
}
