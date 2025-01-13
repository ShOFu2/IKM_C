﻿#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Функция для проверки, делится ли число на заданный делитель
bool isDivisible(const string& num, int divisor) {
    int remainder = 0;
    for (char digit : num) {
        remainder = remainder * 10 + (digit - '0'); // Постепенно формируем остаток
        remainder %= divisor; // Обновляем остаток
    }
    return remainder == 0; // Если остаток равен 0, число делится на divisor
}

// Функция для деления числа на заданный делитель
pair<string, int> divide(const string& num, int divisor) {
    string quotient; // Результат деления
    int remainder = 0; // Остаток от деления
    for (char digit : num) {
        remainder = remainder * 10 + (digit - '0'); // Постепенно формируем остаток
        quotient += (remainder / divisor) + '0'; // Добавляем цифру к результату
        remainder %= divisor; // Обновляем остаток
    }
    // Удаляем ведущие нули из результата
    size_t startpos = quotient.find_first_not_of('0');
    if (startpos != string::npos)
        quotient = quotient.substr(startpos);
    else
        quotient = "0"; // Если результат равен 0
    return { quotient, remainder }; // Возвращаем результат и остаток
}

// Основная функция
int main() {
    setlocale(LC_ALL, "Russian");

    while (true) { // Основной цикл для повторного запроса
        string num;
        cout << "Введите n-значное число (n > 20): ";
        cin >> num;

        // Обработка отрицательных чисел
        if (num[0] == '-') {
            num = num.substr(1); // Убираем знак минуса
        }

        // Проверка корректности ввода
        bool is_valid = true;
        for (char ch : num) {
            if (!isdigit(ch)) {
                cout << "Ошибка: введены недопустимые символы.\n";
                is_valid = false;
                break;
            }
        }

        // Если ввод некорректен, повторяем запрос
        if (!is_valid) {
            cout << "Пожалуйста, попробуйте снова.\n";
            continue;
        }

        // Факторизация числа
        string n = num; // Копируем число для работы
        vector<pair<int, int>> factors; // Пары (делитель, степень)

        // Проверяем делимость на числа от 2 до 10 000
        for (int p = 2; p <= 10000; ++p) {
            if (isDivisible(n, p)) {
                int exp = 0; // Степень делителя
                while (isDivisible(n, p)) {
                    exp++;
                    auto result = divide(n, p); // Делим число на p
                    n = result.first; // Обновляем число
                }
                factors.push_back({ p, exp }); // Сохраняем делитель и его степень
                if (n == "1") break; // Если число полностью разложено
            }
        }

        // Если остаток больше 1, он тоже является простым множителем
        if (n != "1") {
            // Если число не делится ни на один из проверяемых делителей, оно простое
            factors.push_back({ -1, 1 }); // Используем -1 как маркер для большого простого множителя
        }

        // Подсчёт количества делителей
        int num_divisors = 1;
        for (auto& factor : factors) {
            if (factor.first == -1) {
                // Если множитель больше 10 000, считаем его как один простой множитель
                num_divisors *= 2; // (1 + 1)
            }
            else {
                num_divisors *= (factor.second + 1); // Формула для подсчёта делителей
            }
        }

        // Вывод результата
        cout << "Количество делителей: " << num_divisors << endl;

        // Запрос на повторный ввод
        cout << "Хотите ввести ещё одно число? (y/n): ";
        char choice;
        cin >> choice;
        if (choice != 'y' && choice != 'Y') {
            break; // Завершаем программу, если пользователь не хочет продолжать
        }
    }

    cout << "Программа завершена. Спасибо за использование!\n";
    return 0;
}