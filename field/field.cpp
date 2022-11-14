#include "field.h"
#include "../player/player.h"

Playing_field::Playing_field(unsigned int n_rows, unsigned int n_cols) {
    _set_size(n_rows, n_cols);

    _field = (char **) malloc(sizeof(char *) * _n_rows);
    for (unsigned i_rows = 0; i_rows < _n_rows; i_rows++)
        _field[i_rows] = (char *) malloc(sizeof(char) * _n_cols);

    for (unsigned i_row = 0; i_row < _n_rows; i_row++)
        for (unsigned i_col = 0; i_col < _n_cols; i_col++)
            _field[i_row][i_col] = '.';
}

Playing_field::Playing_field() {
    unsigned n_rows = 20, n_cols = 20;
    _set_size(n_rows, n_cols);

    _field = (char **) malloc(sizeof(char *) * _n_rows);
    for (unsigned i_rows = 0; i_rows < _n_rows; i_rows++)
        _field[i_rows] = (char *) malloc(sizeof(char) * _n_cols);

    for (unsigned i_row = 0; i_row < _n_rows; i_row++)
        for (unsigned i_col = 0; i_col < _n_cols; i_col++)
            _field[i_row][i_col] = '.';
}

void Playing_field::_set_size(unsigned int n_rows, unsigned int n_cols) {
    _n_rows = n_rows;
    _n_cols = n_cols;

    _field = (char **) malloc(sizeof(char *) * _n_rows);
    for (unsigned i_rows = 0; i_rows < _n_rows; i_rows++)
        _field[i_rows] = (char *) malloc(sizeof(char) * _n_cols);

    for (unsigned i_row = 0; i_row < _n_rows; i_row++)
        for (unsigned i_col = 0; i_col < _n_cols; i_col++)
            _field[i_row][i_col] = '.';
}

void Playing_field::_change_player_step() {
    _is_first_player_step = !_is_first_player_step;
}

void Playing_field::_print_field() {
    unsigned n_rows = _get_rows();
    unsigned n_cols = _get_cols();

    for (unsigned i_col = 0; i_col < _n_cols + 1; i_col++) {
        if (!i_col) {
            std::cout << 0 << "  ";
        } else if (i_col < 9) {
            std::cout << i_col << ' ' << ' ';
        } else {
            std::cout << i_col << ' ';
        }
    }
    std::cout << '\n';

    for (unsigned i_row = 0; i_row < n_rows; i_row++) {
        if (i_row < 9) {
            std::cout << 1 + i_row << ' ' << ' ';
        } else {
            std::cout << 1 + i_row << ' ';
        }
        for (unsigned i_col = 0; i_col < n_cols; i_col++)
            if (i_col < 8) {
                std::cout << _field[i_row][i_col] << ' ' << ' ';
            } else if (i_col == 8) {
                std::cout << _field[i_row][i_col] << ' ';
            } else {
                std::cout << ' ' << _field[i_row][i_col] << ' ';
            }
        std::cout << '\n';
    }
}

void Playing_field::_build_square(unsigned int &x_start, unsigned int &y_start,
                                  unsigned int x_end, unsigned int y_end,
                                  Player &p) {
    for (unsigned i_row = y_start - 1; i_row < y_end; i_row++) {
        for (unsigned i_col = x_start - 1; i_col < x_end; i_col++) {
            _field[i_row][i_col] = p.get_symbol();
        }
    }
}