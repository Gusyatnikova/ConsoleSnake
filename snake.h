#pragma once
#include <deque>
#include "position.h"
#include "direction.h"

namespace snake {
	struct Snake {
		std::deque<position> items;
		direction dir;
		position tail;
	};

	void init(Snake&, const position&, direction);
	position getHeadPos(const Snake&);
	void moveTo(Snake&, const direction&);
	bool hasCollide(const Snake&, const position&);
	bool onSnake(const Snake&, const position&);
	void addItem(Snake&);
}