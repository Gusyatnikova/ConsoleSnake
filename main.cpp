#include <iostream>
#include <ctime>
#include <conio.h>
#include <cstdlib>
#include <cstdio>
#include <chrono>
#include <thread>
#include <windows.h>
#include <array>

#include "config.h"

bool game_over = false;
uint8_t snake_size = 0;
//todo: change arrays to dynamic() and calculate is it much faster?
std::array<uint8_t, GameField::height * GameField::width> snake_x;
std::array<uint8_t, GameField::height * GameField::width> snake_y;
//uint8_t snake_x[GameField::height * GameField::width]{};
//uint8_t snake_y[GameField::height * GameField::width]{};
uint8_t food_x, food_y;
//prev: todo: check is it useful thing
int prev_food_x = -1, prev_food_y = -1;
std::array<uint8_t, GameField::height * GameField::width> prev_snake_x;
std::array<uint8_t, GameField::height * GameField::width> prev_snake_y;
//uint8_t prev_snake_x[GameField::height * GameField::width]{};
//uint8_t prev_snake_y[GameField::height * GameField::width]{};
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

void ClearField() {
    //clear food
    gotoxy(int(prev_food_x + 1), int(prev_food_y + 1));
    std::cout << ' ';
    //clear snake
    for (uint8_t i = 0; i < snake_size; i++) {
        gotoxy(prev_snake_x[i] + 1, prev_snake_y[i] + 1);
        std::cout << ' ';
    }
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

void PrintField() {
    gotoxy(0, 0);
    for (uint8_t i = 0; i < GameField::width + 2; ++i) {
        std::cout << GameField::border_pic;
    }
    std::cout << std::endl;
    for (uint8_t i = 0; i < GameField::height + 1; ++i) {
        std::cout << GameField::border_pic;
        //for (uint8_t j = 0; j < GameField::width; ++j) {
        //todo: is i reallu need this nected cucles? -> (try print vertical borders with goto)
        //std::cout << ' ';
        //}
        gotoxy(GameField::width + 1, i);
        std::cout << GameField::border_pic;
        std::cout << std::endl;
    }
    for (uint8_t i = 0; i < GameField::width + 2; ++i) {
        std::cout << GameField::border_pic;
    }
}

void PrintInfo() {
    gotoxy(int(GameField::width + 3), int(GameField::height + 3));
    std::cout << "snake_x: " << int(snake_x[0]) << "      " << "snake_y: " << int(snake_y[0]) << std::endl;
}


//Consistent draw

void Draw() {
    //todo: check gotoxy from conio.h, it can make printing faster
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
            if (food_y == i && food_x == j) {
                std::cout << GameField::food_pic;
                continue;
            }
            else {
                bool is_printed = false;
                for (uint8_t k = 0; k < snake_size; k++) {
                    if (snake_x[k] == j && snake_y[k] == i) {
                        k == 0 ? std::cout << GameField::head_pic : std::cout << GameField::body_pic;
                        is_printed = true;
                        break;
                    }
                }
                if (!is_printed) {
                    std::cout << ' ';
                }
            }
        }
        std::cout << GameField::border_pic;
        std::cout << std::endl;
    }
    for (uint8_t i = 0; i < GameField::width + 2; ++i) {
        std::cout << GameField::border_pic;
    }
}

//Draw with gotoxy(int, int)

void DrawGoTo() {
    //todo: check gotoxy from conio.h, it can make printing faster
    //system("cls");
    ClearField();
    //todo: calculate time of this two ways
    //todo: create this 2 cersion as different output ways: console output part_clear and console_output entire field cleare
    //todo: don't draw all field! clear snake and food and then draw it
    if (prev_food_x == -1) {
        PrintField();
    }
    PrintSnake();
    PrintFood();
    PrintInfo();
    //gotoxy(int(GameField::width + 1), int(GameField::height + 1));
}


//todo: fix all functions^ use const and references
//todo: check is ok with this?
bool isFreeCoord(const uint8_t& x, const uint8_t& y) {
    uint8_t console_x = x + 1, console_y = y + 1;
    if (console_x == 0 || console_x == GameField::width ||
        console_y == 0 || console_y == GameField::height) {
        return false;
    }
    for (int i = 0; i < snake_size; ++i) {
        if (console_x == snake_x[i] && console_y == snake_y[i]) {
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
        case direction::DOWN:
            snake_y[0]++;
            break;
        case direction::UP:
            snake_y[0]--;
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

//todo: fix == 255 when decide how size of field will be setup
bool isOutOfField() {
    return snake_x[0] == GameField::width || snake_x[0] == 255 ||
           snake_y[0] == GameField::height || snake_y[0] == 255;
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

void SaveState() {
    prev_food_x = food_x;
    prev_food_y = food_y;
    prev_snake_x = snake_x;
    prev_snake_y = snake_y;
}

void Iteration() {
    SaveState();
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
    }
}

//todo: add scores, levels, run via walls, detect why blinking

int main() {
    ShowConsoleCursor(false);
    Init();
    std::chrono::milliseconds msec(100);
    while (!game_over) {
        //Draw();
        DrawGoTo();
        std::this_thread::sleep_for(msec);
        GetInput();
        Iteration();
        std::this_thread::sleep_for(msec);
    }
    return 0;
}
