#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <ctime>

#ifndef SQUARE_GAME_CUBES_H
#define SQUARE_GAME_CUBES_H

struct Cubes {
private:
    unsigned first_cube = 0;
    unsigned second_cube = 0;
public:
    void roll_the_dice() {
        first_cube = 1 + rand() % 6;
        second_cube = 1 + rand() % 6;
    };

    void print_numbers() const {
        std::cout << first_cube << ' ' << second_cube << '\n';
    }

    std::pair<unsigned, unsigned > get_numbers() {
        return std::pair{first_cube, second_cube};
    }

    [[nodiscard]] unsigned get_sum() const {
        return first_cube + second_cube;
    }
};

#endif //SQUARE_GAME_CUBES_H
