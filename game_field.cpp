#include "game_field.h"

namespace gameField {
	void init(GameField& gf, const position& size) {
		gf.height = size.row;
		gf.width = size.column;
		unsigned int border_cnt = 2 * (size.column + size.row - 2);
		gf.borders.resize(border_cnt);
		setBorders(gf);
	}

	void setBorders(GameField& gf) {
		long item = 0;
		for (int i = 0; i < gf.width; ++i) {
			gf.borders[item++] = { 0, i };
			gf.borders[item++] = { gf.height - 1, i };
		}
		for (int i = 1; i < gf.height - 1; ++i) {
			gf.borders[item++] = { i, 0 };
			gf.borders[item++] = { i, gf.width - 1 };
		}
			
	}

	bool hasCollide (const GameField& gf, const position& pos) {
		return pos.column == 0 || pos.row == 0 ||
			pos.column == gf.width - 1 || pos.row == gf.height - 1;
	}

	const std::vector<position>& getBorders(const GameField& gf) {
		return gf.borders;
	}
}
