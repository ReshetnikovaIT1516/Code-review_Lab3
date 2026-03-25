//В текстовом файле с именем filename дано арифметическое выражение в обратной
//польской записи.Операндами в выражении являются целые числа из промежутка.от 0 до 9. Используемые операции : сложение(+), вычитание(-), умножение(*), деление нацело(/ ) и целочисленный остаток от деления(%).Постройте дерево, соответствующее данному выражению.Знаки
//операций кодируйте числами : сложение(-1), вычитание(-2), умножение(-3), деление нацело(-4)
//и целочисленный остаток от деления(-5).Преобразуйте дерево так, чтобы в нем не было операции
//умножения(замените поддеревья, в которых есть умножение значением данного поддерева).Выведите указатель на корень полученного дерева.
//
// https://chat.deepseek.com/


#include "Header.h"
#include <iostream>
#include <fstream>
#include <string>

//FIX ME: Убрала глобальное использование std
//FIX ME: Разделила на модули
//FIX ME: Перенесла все фигурные скобки на новую строку
//FIX ME: Переименовала некоторые названия функций и переменных
//FIX ME: Изменила пользовательский интерфейс
//FIX ME: Дополнила функции проверок
//FIX ME: Добавила необходимые библиотеки

int main()
{
    setlocale(LC_ALL, "rus");

    std::string filename = "filename.txt";

    std::ifstream testFile(filename);

    if (!testFile.is_open())
    {
        std::cout << "Файл не найден. Создаю...\n";
        createTestFile();
    }
    else
    {
        std::cout << "Файл найден\n";

        std::ifstream readFile(filename);
        std::string line;

        std::cout << "Содержимое файла:\n";

        while (std::getline(readFile, line))
        {
            std::cout << line << '\n';
        }
    }

    std::cout << "\n--- Построение дерева ---\n";

    Node* root = buildTreeFromRPN(filename);

    if (!root)
    {
        std::cerr << "Ошибка при построении дерева\n";
        return 1;
    }

    std::cout << "\n--- Исходное дерево ---\n";
    printTree(root);

    std::cout << "\n--- Преобразование ---\n";

    Node* transformedRoot = transformTree(root);

    std::cout << "\n--- Результирующее дерево ---\n";
    printTree(transformedRoot);

    std::cout << "\n--- Результат ---\n";
    std::cout << "Указатель на корень: " << transformedRoot << '\n';
    std::cout << "Значение корня: " << transformedRoot->value << '\n';

    deleteTree(transformedRoot);

    std::cout << "Память очищена\n";

    return 0;
}