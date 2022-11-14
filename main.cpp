#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <ctime>
#include <cmath>

#include "field/field.h"
#include "player/player.h"
#include "Cubes/cubes.h"

unsigned user_choice;

unsigned get_choice(unsigned min, unsigned max) {
    std::cin >> user_choice;

    while (user_choice < min || user_choice > max) {
        std::cerr << "Неверное значение! Попробуйте ещё раз >>>\n";
        std::cin >> user_choice;
    }

    return user_choice;
}

unsigned abs(unsigned x) {
    return x > 0 ? x : -x;
}

unsigned get_main_menu_choice() {
    std::cout << "\t\t\tМЕНЮ\n"
                 "\t\t 1. Играть \n"
                 "\t\t 2. Правила \n"
                 "\t\t 3. Настройки игроков \n";

    return get_choice(1, 3);
}

void change_player_settings(Player &player) {
    std::cout << "Имя: " << player.get_name() << '\n'
              << "Символ: " << player.get_symbol() << '\n';
    std::cout << "Изменить? \n"
                 "1. Да \n"
                 "2. Нет\n";

    user_choice = get_choice(1, 2);
    if (user_choice == 1) {
        std::cout << "Имя >>> \n";
        std::string name;
        std::cin >> name;
        player.set_name(name);

        std::cout << "Символ >>> \n";
        char symbol;
        std::cin >> symbol;
        player.set_symbol(symbol);
    };
}

void get_players_settings_menu(Player &player1, Player &player2) {
    std::cout << "\t\t 1. Настройки игрока " << player1.get_name() << '\n'
              << "\t\t 2. Настройки игрока " << player2.get_name() << '\n'
              << "\t\t 3. В меню \n";

    user_choice = get_choice(1, 3);
    if (user_choice == 1) {
        change_player_settings(player1);
    } else if (user_choice == 2) {
        change_player_settings(player2);
    }
}


void press_enter_to_continue() {
    std::cout << "Нажмите Enter для продолжения...";

    fflush(stdin);

    while (getchar() != '\n');
}

void print_rules() {
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
                 "\t 7. Побеждает тот, чья территория больше\n\n";

    press_enter_to_continue();
}

unsigned get_game_mode() {
    std::cout << "Выберите режим игры: \n"
                 "1. Против ИИ \n"
                 "2. Против игрока \n";

    return get_choice(1, 2);
}

unsigned get_field_size() {
    std::cout << "Укажите размер игрового поля: \n"
                 "1. Маленькое (20 x 20) \n"
                 "2. Среднее (30 x 30) \n"
                 "3. Большое (39 x 39) \n"
                 "4. Вернуться в меню\n";

    return get_choice(1, 4);
}

void building_field(Playing_field &f, unsigned size) {
    switch (size) {
        case 1: {
            f._set_size(20, 20);
            break;
        }
        case 2: {
            f._set_size(30, 30);
            break;
        }
        case 3: {
            f._set_size(39, 39);
            break;
        }
        default:
            f._set_size(20, 20);
    }
}

unsigned get_start_numbers(Player &p) {
    std::cout << p.get_name() << ", введите число от 2 до 12 >>>\n";

    return get_choice(2, 12);
}

unsigned _get_choice_player_step(Player &p) {
    std::cout << "Ход игрока " << p.get_name() << "\n"
                                                  "1. Бросить кубики\n"
                                                  "2. Сдаться\n";
    return get_choice(1, 2);
}

bool is_can_be_accomodate(Playing_field &f, Player &p,
                          unsigned x_start, unsigned y_start,
                          unsigned x_end, unsigned y_end) {
    unsigned x_steps = x_end - x_start + 1;
    unsigned y_steps = y_end - y_start + 1;
    for (unsigned i_row = x_start - 1; i_row < x_steps; i_row++) {
        for (unsigned i_col = y_start - 1; i_col < y_steps; i_col++) {
            if (f._get_field()[i_row][i_col] != '.')
                return false;
        }
    }

    return true;
}

unsigned start_game_with_player(Player &p1, Player &p2, Cubes &c,
                                Playing_field &f) {
    std::cout << "\t\t\tУдачной игры!!!!\n";

    unsigned p1_number = get_start_numbers(p1);
    unsigned p2_number = get_start_numbers(p2);

    c.roll_the_dice();
    unsigned sum_numbers = c.get_sum();
    std::cout << "---------------------------------------\n" <<
              "Выпало: " << sum_numbers << '\n' <<
              "---------------------------------------\n";

    unsigned res1 = abs(sum_numbers > p1_number ? sum_numbers - p1_number
                                                : p1_number - sum_numbers);
    unsigned res2 = abs(sum_numbers > p2_number ? sum_numbers - p2_number
                                                : p2_number - sum_numbers);

    if (res1 < res2) {
        f._change_player_step();
        return _get_choice_player_step(p1);
    } else return _get_choice_player_step(p2);
}

void start_game_with_AI() {

}

void print_winner(const Player &p) {
    std::cout << "Побеждает" << ' '
              << p.get_name() << ' ' << "со счетом"
              << ' ' << p.get_square();
}

void end_the_game(Player &p1, Player &p2) {
    std::cout << "Игра окончена.\n";
    if (p1.get_square() > p2.get_square())
        print_winner(p1);
    else if (p2.get_square() > p1.get_square())
        print_winner(p2);
    else
        std::cout << "Победил разработчик";
}

void get_coordinates(unsigned &x_start, unsigned &y_start,
                     unsigned &x_end, unsigned &y_end, Playing_field &f) {
    std::cout << "Укажите координаты верхнего левого угла:\n"
                 "x >>>";
    x_start = get_choice(1, f._get_cols());

    std::cout << "y >>>";
    y_start = get_choice(1, f._get_cols());

    std::cout << "Укажите координаты нижнего правого угла:\n"
                 "x >>>";
    x_end = get_choice(1, f._get_cols());

    std::cout << "y >>>";
    y_end = get_choice(1, f._get_cols());

}

void make_step(Cubes &cube, Playing_field &field, Player &p) {
    cube.roll_the_dice();
    std::pair<unsigned, unsigned> numbers =
            cube.get_numbers();

    std::cout << "---------------------------------------\n" <<
              "Выпало:" << ' ' << numbers.first <<
              ';' << numbers.second
              << "\n--------------------------------------\n";

    p.upd_square(numbers.first, numbers.second);

    unsigned x_start, y_start, x_end, y_end;
    get_coordinates(x_start, y_start, x_end, y_end, field);

    unsigned x_steps = x_end - x_start + 1;
    unsigned y_steps = y_end - y_start + 1;

    while (!(x_steps == numbers.first || x_steps == numbers.second &&
                                         y_steps == numbers.first || y_steps == numbers.second)) {
        std::cerr << "Неверные значения!!!!!";
        std::cout << "\n";
        press_enter_to_continue();

        get_coordinates(x_start, y_start, x_end, y_end, field);

        x_steps = x_end - x_start + 1;
        y_steps = y_end - y_start + 1;
    }

    while (!is_can_be_accomodate(field, p, x_start, y_start, x_end, y_end)) {
        std::cerr << "Территория занята \n";
        system("pause");
        std::cout << '\n';
        press_enter_to_continue();
        get_coordinates(x_start, y_start, x_end, y_end, field);
    }

    field._build_square(x_start, y_start, x_end, y_end, p);
}

Player get_player_step(Player &p1, Player &p2, Playing_field &f) {
    return (Player) (f._get_step() ? p1 : p2);
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    srand(time(nullptr));

    Player player1("sancheese", '@');
    Player player2("Игрок 2", '#');

    while (true) {
        user_choice = get_main_menu_choice();

        if (user_choice == 3) {
            get_players_settings_menu(player1, player2);
        } else if (user_choice == 2) {
            print_rules();
        } else if (user_choice == 1) {
            user_choice = get_game_mode();
            if (user_choice == 1) {
                start_game_with_AI();
            } else {
                unsigned size = get_field_size();
                Playing_field field;
                building_field(field, size);
                std::cout << "Поле создано \n";

                Cubes cube;
                user_choice = start_game_with_player(
                        player1, player2, cube, field);

                while (true) {
                    if (user_choice == 1) {
                        field._print_field();
                        Player t = get_player_step(player1, player2, field);
                        make_step(cube, field, t);
                        field._change_player_step();
                        field._print_field();
                        press_enter_to_continue();
                        t = get_player_step(player1, player2, field);
                        _get_choice_player_step(t);
                    } else {
                        end_the_game(player1, player2);
                        return 1;
                    }
                }
            }
        }
    }
}