#include <iostream>
#include <vector>
#include <stdlib.h>
#include <windows.h>
#include <ctime>
#include <vector>
#include <algorithm>

#define MIN_SIZE 21

struct Playing_field {

    Playing_field(unsigned n_rows, unsigned n_cols) {
        _set_size(n_rows, n_cols);

        _field = (char **) malloc(sizeof(char *) * _n_rows);
        for (unsigned i_rows = 0; i_rows < _n_rows; i_rows++)
            _field[i_rows] = (char *) malloc(sizeof(char) * _n_cols);

        for (unsigned i_row = 0; i_row < _n_rows; i_row++)
            for (unsigned i_col = 0; i_col < _n_cols; i_col++)
                _field[i_row][i_col] = '.';
    }

    Playing_field() {
        unsigned n_rows = 20, n_cols = 20;
        _set_size(n_rows, n_cols);

        _field = (char **) malloc(sizeof(char *) * _n_rows);
        for (unsigned i_rows = 0; i_rows < _n_rows; i_rows++)
            _field[i_rows] = (char *) malloc(sizeof(char) * _n_cols);

        for (unsigned i_row = 0; i_row < _n_rows; i_row++)
            for (unsigned i_col = 0; i_col < _n_cols; i_col++)
                _field[i_row][i_col] = '.';
    }

    void _set_size(unsigned n_rows, unsigned n_cols) {
        _n_rows = n_rows;
        _n_cols = n_cols;
    }

    unsigned _get_rows(){
        return _n_rows;
    }

    unsigned _get_cols(){
        return _n_cols;
    }

    void print_field() {
        unsigned n_rows = _get_rows();
        unsigned n_cols = _get_cols();

        for (unsigned i_col = 0; i_col < _n_cols + 1; i_col++) {
            if (!i_col) {
                std::cout << 0 << "  ";
            } else {
                std::cout << 0 + i_col << ' ';
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
                if (i_col < 9) {
                    std::cout << _field[i_row][i_col] << ' ';
                } else {
                    std::cout << ' ' << _field[i_row][i_col] << ' ';
                }
            std::cout << '\n';
        }
    }

private:
    unsigned _n_rows, _n_cols;
    char **_field;
public:
};

struct Cubes {
private:
    unsigned first_cube = 0;
    unsigned second_cube = 0;
public:
    void roll_the_dice() {
        first_cube = 1 + rand() % 6;
        second_cube = 1 + rand() % 6;
    };

    void get_numbers() const {
        std::cout << first_cube << ' ' << second_cube << '\n';
    }
};

int main() {
    SetConsoleOutputCP(CP_UTF8);
    srand(time(NULL));
    menu:
    std::cout << "\t\t\tМЕНЮ\n"
                 "\t\t 1. Играть \n"
                 "\t\t 2. Правила \n";

    unsigned user_change;
    std::cin >> user_change;

    if (user_change == 2) {
        std::cout << "\t\t\t ПРАВИЛА \n"
                     "\t 1. Сгенерируйте два случайных числа\n"
                     "\t 2. Сделайте прямоугольник со сторонами, равными \n "
                     "\t    значениям сгенерированных чисел \n"
                     "\t 3. Прямоугольник должен быть присоединен к вашей \n"
                     "\t    существующей территории\n"
                     "\t 4. Первый прямоугольник игрока помещается в угол, \n"
                     "\t    прямоугольник соперника - в противоположный \n"
                     "\t 5. Если вы не можете сделать сгенерированный прямоугольник,\n"
                     "\t    вы пропускаете ход \n"
                     "\t 6. Игра считается оконченной, когда всё пространство\n"
                     "\t    заполнено\n"
                     "\t 7. Побеждает тот, чья территория больше\n\n"
                     "Вернуться в главное меню? \n"
                     "1. Да \n";
        std::cin >> user_change;

        if (user_change == 1)
            goto menu;
        else {
            while (user_change != 1) {
                std::cerr << "Неверное значение!!! Попробуйте ещё раз >>>";
                std::cin >> user_change;
            }
            goto menu;
        }
    } else if (user_change == 1) {
        std::cout << "Выберите режим игры:\n"
                     "1. Против ИИ\n"
                     "2. Против игрока\n";

        std::cin >> user_change;
        while (user_change != 1 && user_change != 2) {
            std::cerr << "Неверное значение!!! Попробуйте ещё раз >>> \n";
            std::cin >> user_change;
        }
        if (user_change == 1) {

        } else {

            std::cout << "Укажите размер игрового поля: \n"
                         "1. Маленькое (20 x 20) \n"
                         "2. Среднее (30 x 30) \n"
                         "3. Большое (40 x 40) \n";

            unsigned size;
            std::cin >> size;

            while (size < 1 || size > 3) {
                std::cerr << "Неверное значение!!! Попробуйте ещё раз >>>\n";
                std::cin >> size;
            }

            Playing_field field;
            switch (size) {
                case 1: {
                    field._set_size(20, 20);
                    break;
                }
                case 2: {
                    field._set_size(30, 30);
                    break;
                }
                case 3: {
                    field._set_size(40, 40);
                }
            }

            std::cout << "Поле создано. Начать игру? \n"
                         "1. Да\n"
                         "2. Нет\n";

            std::cin >> user_change;
            while (user_change != 1 && user_change != 2) {
                std::cerr << "Неверное значение!!! Попробуйте ещё раз >>>\n";
                std::cin >> user_change;
            }

            field.print_field();
        }
    }

    return 0;
}
