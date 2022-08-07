#include <iostream>
#include <vector>
#include <cstdlib>
#include <windows.h>
#include <ctime>
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

        _field = (char **) malloc(sizeof(char *) * _n_rows);
        for (unsigned i_rows = 0; i_rows < _n_rows; i_rows++)
            _field[i_rows] = (char *) malloc(sizeof(char) * _n_cols);

        for (unsigned i_row = 0; i_row < _n_rows; i_row++)
            for (unsigned i_col = 0; i_col < _n_cols; i_col++)
                _field[i_row][i_col] = '.';
    }

    unsigned _get_rows() const {
        return _n_rows;
    }

    unsigned _get_cols() const {
        return _n_cols;
    }

    void print_field() {
        unsigned n_rows = _get_rows();
        unsigned n_cols = _get_cols();

        for (unsigned i_col = 0; i_col < _n_cols + 1; i_col++) {
            if (!i_col) {
                std::cout << 0 << "  ";
            } else if (i_col < 9) {
                std::cout << 0 + i_col << ' ' << ' ';
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

    unsigned get_sum() const {
        return first_cube + second_cube;
    }
};

void get_choice(unsigned min, unsigned max, unsigned &change) {
    std::cin >> change;
    while (change < min || change > max) {
        std::cerr << "Неверное значение! Попробуйте ещё раз >>>\n";
        std::cin >> change;
    }
}


int main() {
    SetConsoleOutputCP(CP_UTF8);
    srand(time(NULL));
    menu:
    std::cout << "\t\t\tМЕНЮ\n"
                 "\t\t 1. Играть \n"
                 "\t\t 2. Правила \n";

    unsigned user_choice;
    get_choice(1, 2, user_choice);

    if (user_choice == 2) {
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
        get_choice(1, 1, user_choice);
        goto menu;

    } else if (user_choice == 1) {
        std::cout << "Выберите режим игры:\n"
                     "1. Против ИИ\n"
                     "2. Против игрока\n";

        get_choice(1, 2, user_choice);
        if (user_choice == 1) {

        } else {
            choice_size:
            std::cout << "Укажите размер игрового поля: \n"
                         "1. Маленькое (20 x 20) \n"
                         "2. Среднее (30 x 30) \n"
                         "3. Большое (39 x 39) \n"
                         "4. Вернуться в меню\n";

            unsigned size;
            get_choice(1, 4, size);

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
                    field._set_size(39, 39);
                }
                case 4:
                    goto menu;
            }

            std::cout << "Поле создано. Начать игру? \n"
                         "1. Да\n"
                         "2. Нет\n";

            get_choice(1, 2, user_choice);

            if (user_choice == 2) {
                std::cout << "Вернуться к выбору размера игрового поля? \n"
                             "1. Да\n"
                             "2. Нет\n";

                get_choice(1, 2, user_choice);
                if (user_choice == 1) goto choice_size;
            } else {
                std::cout << "\t\t\tУдачной игры!!!!\n";

                std::cout << "Игрок 1, введите число от 2 до 12 >>>\n";
                get_choice(2, 12, user_choice);
                unsigned player1_number = user_choice;

                std::cout << "Игрок 2, введите число от 2 до 12 >>>\n";
                get_choice(2, 12, user_choice);
                unsigned player2_number = user_choice;

                Cubes first_step;
                first_step.roll_the_dice();
                unsigned sum_numbers = first_step.get_sum();
                std::cout << "Выпало: " << sum_numbers << '\n';

                unsigned res1 = sum_numbers - player1_number;
                unsigned res2 = sum_numbers - player2_number;

                if (res1 < res2) {
                    goto player1_step;
                } else {
                    goto player2_step;
                }

                player1_step:
                std::cout << "Ход игрока 1. \n"
                             "1. Бросить кубики\n"
                             "2. Сдаться\n";
                get_choice(1, 2, user_choice);

                player2_step:
                std::cout << "Ход игрока 2. \n"
                             "1. Бросить кубики\n"
                             "2. Сдаться\n";
                get_choice(1, 2, user_choice);
            }
        }
    }

    return 0;
}
