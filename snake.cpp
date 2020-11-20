#include "snake.h"

namespace snake {
	void init(Snake& snake, const position& head, direction dir) {
		snake.items.push_front({ head.column + 1, head.row + 1 });
		snake.dir = dir;
		snake.tail = snake.items[0];
	}

	position getHeadPos(const Snake& snake) {
		return { snake.items[0].row, snake.items[0].column };
	}

	void setDir(Snake& snake, const direction& dir) {
		switch (dir)
		{
		case direction::UP:
			if (snake.dir != direction::DOWN || snake.items.size() == 1)
				snake.dir = direction::UP;
			break;
		case direction::DOWN:
			if (snake.dir != direction::UP || snake.items.size() == 1)
				snake.dir = direction::DOWN;
			break;
		case direction::LEFT:
			if (snake.dir != direction::RIGHT || snake.items.size() == 1)
				snake.dir = direction::LEFT;
			break;
		case direction::RIGHT:
			if (snake.dir != direction::LEFT || snake.items.size() == 1)
				snake.dir = direction::RIGHT;
			break;
		case direction::QUIT:
			snake.dir = direction::QUIT;
			break;
		default:
			break;
		}
	}

	void moveTo(Snake& snake, const direction& dir) {
		direction prev_dir = snake.dir;
		snake.tail = *std::prev(snake.items.end());
		setDir(snake, dir);
		position head = snake.items[0];
		snake.items.pop_back();
		switch (snake.dir)
		{
		case direction::UP:
			snake.items.push_front({
				head.row - 1 , head.column });
			break;
		case direction::DOWN:
			snake.items.push_front({
				head.row + 1 , head.column });
			break;
		case direction::LEFT:
			snake.items.push_front({
				head.row, head.column - 1 });
			break;
		case direction::RIGHT:
			snake.items.push_front({
				head.row, head.column + 1 });
			break;
		default:
			snake.items.push_back(head);
			break;
		}
	}
	bool hasCollide(const Snake& snake, const position& p) {
		if (snake.items.size() > 3) {
			for (auto it = std::next(snake.items.begin(), 3); it != snake.items.end(); ++it) {
				if (it->row == p.row && it->column == p.column) return true;
			}
		}
		return false;
	}
	bool onSnake(const Snake& snake, const position& p) {
		for (auto it = snake.items.begin(); it != snake.items.end(); ++it) {
			if (it->row == p.row && it->column == p.column) return true;
		}
		return false;
	}
	void addItem(Snake& snake) {
		snake.items.push_back(snake.tail);
	}
}