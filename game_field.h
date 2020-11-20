#pragma once
#include <vector>
#include "position.h"

namespace gameField {
	struct GameField {
		int height;
		int width;
		std::vector<position> borders;
	};
	void init(GameField&, const position&);
	bool hasCollide(const GameField&, const position&);
	const std::vector<position>& getBorders(const GameField&);
	void setBorders(GameField&);
}


