#pragma once

using uint8_t = unsigned char ;

//todo: is namespace useful here?

namespace GameField {
    const uint8_t width = 20;
    const uint8_t height = 10;
    const uint8_t border_pic = 176;
    const uint8_t body_pic = 'x';
    const uint8_t head_pic = 'X';
    const uint8_t food_pic = 'F';
}

namespace GameLogic {
    const uint8_t max_tail_size = 100;
    const uint8_t start_pos_x = 5;
    const uint8_t start_pos_y = 5;
}



