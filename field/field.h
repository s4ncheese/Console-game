#include <iostream>
#include <utility>
#include <cstdlib>
#include <windows.h>
#include <ctime>
#include <algorithm>

#include "../player/player.h"

#ifndef SQUARE_GAME_FIELD_H
#define SQUARE_GAME_FIELD_H

struct Playing_field {

    Playing_field(unsigned n_rows, unsigned n_cols);

    Playing_field();

    void _set_size(unsigned n_rows, unsigned n_cols);

    void _change_player_step();

    [[nodiscard]] unsigned _get_rows() const {
        return _n_rows;
    }

    [[nodiscard]] unsigned _get_cols() const {
        return _n_cols;
    }

    [[nodiscard]] bool _get_step() const {
        return _is_first_player_step;
    }

    void _print_field();

    char** _get_field() {
        return _field;
    }

private:
    unsigned _n_rows, _n_cols;
    char **_field;
    bool _is_first_player_step = false;
    unsigned _square = 0;
public:
    void _build_square(unsigned &x_start, unsigned &y_start,
                       unsigned x_end, unsigned y_end, Player &p);
};

#endif //SQUARE_GAME_FIELD_H
