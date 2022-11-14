#include <iostream>
#include <utility>
#include <cstdlib>
#include <windows.h>
#include <ctime>
#include <algorithm>

#ifndef SQUARE_GAME_PLAYER_H
#define SQUARE_GAME_PLAYER_H

class Player {
public:
    Player(std::string name, char symbol) : _name(std::move(name)), _symbol(symbol) {};
    void set_name(std::string &name) {
        _name = name;
    }

    void set_symbol(char &symbol) {
        _symbol = symbol;
    }

    void upd_square(unsigned &a, unsigned &b) {
        _square += a * b;
    }

    [[nodiscard]] std::string get_name() const {
        return _name;
    }

    [[nodiscard]] char get_symbol() const {
        return _symbol;
    }

    [[nodiscard]] unsigned get_square() const {
        return _square;
    }

private:
    std::string _name;
    char _symbol;
    unsigned _square = 0;
};

#endif //SQUARE_GAME_PLAYER_H
