//Ввести с клавиатуры любое слово.Используя генерацию случайных чисел, переставить
//буквы этого слова в случайном порядке.Делать это до тех пор, пока полученное слово не совпадёт
//с начальным словом.Выводить слово после каждой перестановки и посчитать общее количество
//выведенных слов(не считая исходного).Пример выполнения программы :
//Введите слово : корова
//воакро
//вокроа
//ароовк
//краоов
//крваоо
//оокавр
//ооквра
//вкраоо
//корова
//9 попыток
//
//https://chatgpt.com/

#include <iostream>
#include <algorithm>
#include <string>
#include <random>
#include <cctype>
#include <windows.h>
#include "Header.h"

//FIX ME: Убрала глобальное использование std
//FIX ME: Разделила на модули
//FIX ME: Перенесла все фигурные скобки на новую строку
//FIX ME: Переименовала некоторые названия функций и переменных
//FIX ME: Изменила пользовательский интерфейс
//FIX ME: Дополнила функции проверок
//FIX ME: Добавила необходимые библиотеки

int main()
{
    setlocale(LC_ALL, "RUS");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::string Original;
    std::string Shuffled;

    do
    {
        std::cout << "Введите слово (только буквы): ";
        std::cin >> Original;

        if (!IsLettersOnly(Original))
        {
            std::cout << "Ошибка: вводите только буквы!\n";
        }

    } while (!IsLettersOnly(Original));

    Shuffled = Original;

    std::random_device RandomDevice;
    std::mt19937 Generator(RandomDevice());

    int Count = 0;

    do
    {
        std::shuffle(Shuffled.begin(), Shuffled.end(), Generator);
        std::cout << Shuffled << std::endl;
        Count++;
    } while (Shuffled != Original);

    std::cout << "Количество попыток:" << Count - 1 << std::endl;

    return 0;
}