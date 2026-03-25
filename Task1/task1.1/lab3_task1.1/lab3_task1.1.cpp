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
//// https://chat.deepseek.com/

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <cctype>
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
    setRussianLocale();
    srand(time(NULL));

    std::string originalWord;
    std::string currentWord;
    int attempts = 0;
    bool validInput = false;

    std::cout << "Введите слово: ";

    // Цикл для проверки ввода
    do
    {
        std::getline(std::cin, originalWord);

        // Удаляем пробелы в начале и в конце
        size_t start = originalWord.find_first_not_of(" \t");
        size_t end = originalWord.find_last_not_of(" \t");

        if (start != std::string::npos)
        {
            originalWord = originalWord.substr(start, end - start + 1);
        }

        if (originalWord.empty())
        {
            std::cout << "Слово не может быть пустым! Попробуйте снова: ";
            continue;
        }

        if (!isOnlyLetters(originalWord))
        {
            std::cout << "Ошибка! Можно вводить только буквы (русские или английские). Попробуйте снова: ";
            continue;
        }

        validInput = true;

    } while (!validInput);

    currentWord = originalWord;

    std::cout << std::endl;

    do
    {
        currentWord = shuffleWord(currentWord);
        std::cout << currentWord << std::endl;
        attempts++;

        if (currentWord == originalWord)
        {
            break;
        }

    } while (true);

    std::cout << "Количество попыток" << attempts - 1 << std::endl;

    return 0;
}