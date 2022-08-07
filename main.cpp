#include <iostream>
#include <vector>
#include <stdlib.h>
#include <windows.h>
#include <ctime>
#include <vector>

struct Playing_field {

    Playing_field(unsigned size) {
        std::vector<std::vector<char>> _field;

    }

    unsigned _get_size() {
        return _size;
    }

    void print_field() {

    }

private:
    unsigned _size;
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
                std::cerr << "Неверное значение!!! Попробуйте ещё раз >>> \n";
                std::cin >> size;
            }

            Playing_field f(size);
            f.print_field();

            std::cout << "Поле создано. Начать игру? \n"
                         "1. Да\n"
                         "2. Нет\n";
        }
    }

    return 0;
}
