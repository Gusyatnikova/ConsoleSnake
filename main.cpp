#include <iostream>
#include <ctime>
#include <conio.h>
#include <cstdlib>
#include <cstdio>
#include <chrono>
#include <thread>
#include <windows.h>

#include "config.h"

bool game_over = false;
uint8_t snake_size = 0;
//todo: change arrays to dynamic() and calculate is it much faster?
uint8_t snake_x[GameField::height * GameField::width]{};
uint8_t snake_y[GameField::height * GameField::width]{};
uint8_t food_x, food_y;
enum class direction { //scoped enum
    UP, DOWN, LEFT, RIGHT, EXIT
} snake_dir;

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO     cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag;
    SetConsoleCursorInfo(out, &cursorInfo);
}

void gotoxy(const int& x, const int& y) {
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void PrintFood() {
    gotoxy(int(food_x + 1), int(food_y + 1));
    std::cout << GameField::food_pic;
}

void PrintSnake() {
    //todo: int(val) VS static_cast<int>(val)
    gotoxy(int(snake_x[0] + 1), int(snake_y[0] + 1));
    std::cout << GameField::head_pic;
    if (snake_size > 1) {
        for (uint8_t i = 1; i < snake_size; i++) {
            gotoxy(int(snake_x[i] + 1), int(snake_y[i]) + 1);
            std::cout << GameField::body_pic;
        }
    }
}

void Draw() {
    //todo: check gotoxy from conio.h, it can make printing easily
    system("cls");
    //todo: calculate time of this two ways
    //todo: create this 2 cersion as different output ways: console output part_clear and console_output entire field cleare
    //todo: don't draw all field! clear snake and food and then draw it
    for (uint8_t i = 0; i < GameField::width + 2; ++i) {
        std::cout << GameField::border_pic;
    }
    std::cout << std::endl;
    for (uint8_t i = 0; i < GameField::height; ++i) {
        std::cout << GameField::border_pic;
        for (uint8_t j = 0; j < GameField::width; ++j) {
            std::cout << ' ';
        }
        std::cout << GameField::border_pic;
        std::cout << std::endl;
    }
    for (uint8_t i = 0; i < GameField::width + 2; ++i) {
        std::cout << GameField::border_pic;
    }
    PrintSnake();
    PrintFood();
    gotoxy(int(GameField::width + 1), int(GameField::height + 1));
}

//todo: fix all functions^ use const and references
bool isFreeCoord(uint8_t& x, uint8_t& y) {
    if (x == 0 || x == GameField::width ||
        y == 0 || y == GameField::height) {
        return false;
    }
    for (int i = 0; i < snake_size; ++i) {
        if (x == snake_x[i] && y == snake_y[i]) {
            return false;
        }
    }
    return true;
}

void SetFood() {
    do {
        //todo: use smth modern for random?
        food_x = rand() % GameField::width;
        food_y = rand() % GameField::height;
    } while (!isFreeCoord(food_x, food_y));
}

void Init() {
    snake_size = 1;
    snake_x[0] = GameLogic::start_pos_x;
    snake_y[0] = GameLogic::start_pos_y;
    std::srand(time(0));
    SetFood();
}

void GetInput() {
    //todo: try change on events: https://stackoverflow.com/questions/24708700/c-detect-when-user-presses-arrow-key
    if (_kbhit()) {
        switch (_getch()) {
            case 'w':
                snake_dir = direction::UP;
                break;
            case 's':
                snake_dir = direction::DOWN;
                break;
            case 'a':
                snake_dir = direction::LEFT;
                break;
            case 'd':
                snake_dir = direction::RIGHT;
                break;
            case '.':
                snake_dir = direction::EXIT;
                break;
        }
    }
}

void MoveSnake() {
    for (uint8_t i = snake_size - 1; i > 0; --i) {
        snake_x[i] = snake_x[i - 1];
        snake_y[i] = snake_y[i - 1];
    }
    switch (snake_dir) {
        case direction::UP:
            snake_y[0]--;
            break;
        case direction::DOWN:
            snake_y[0]++;
            break;
        case direction::LEFT:
            snake_x[0]--;
            break;
        case direction::RIGHT:
            snake_x[0]++;
            break;
        case direction::EXIT:
            exit(0);
    }
}

bool isOutOfField() {
    return snake_x[0] >= GameField::width || snake_y[0] >= GameField::height;
}

bool isOnFood() {
    return snake_x[0] == food_x && snake_y[0] == food_y;
}

bool isOnBody() {
    for (uint8_t i = 1; i < snake_size; ++i) {
        if (snake_x[0] == snake_x[i] && snake_y[0] == snake_y[i]) {
            return true;
        }
    }
    return false;
}

void Iteration() {
    //todo: change approach with 2 variables
    uint8_t last_x = snake_x[snake_size - 1];
    uint8_t last_y = snake_y[snake_size - 1];
    MoveSnake();
    if (isOnFood()) {
        snake_size++;
        snake_x[snake_size - 1] = last_x;
        snake_y[snake_size - 1] = last_y;
        SetFood();
    }

    if (isOutOfField() || isOnBody()) {
        game_over = true;
        return;
    }

}

//todo: add scores, levels, run via walls, detect why blinking

int main() {
    ShowConsoleCursor(false);
    Init();
    while (!game_over) {
        Draw();
        GetInput();
        Iteration();
        std::chrono::milliseconds msec(70);
        std::this_thread::sleep_for(msec);
    }
    return 0;
}
