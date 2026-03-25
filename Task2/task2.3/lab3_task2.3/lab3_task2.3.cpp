//В текстовом файле с именем filename дано арифметическое выражение в обратной
//польской записи.Операндами в выражении являются целые числа из промежутка.от 0 до 9. Используемые операции : сложение(+), вычитание(-), умножение(*), деление нацело(/ ) и целочисленный остаток от деления(%).Постройте дерево, соответствующее данному выражению.Знаки
//операций кодируйте числами : сложение(-1), вычитание(-2), умножение(-3), деление нацело(-4)
//и целочисленный остаток от деления(-5).Преобразуйте дерево так, чтобы в нем не было операции
//умножения(замените поддеревья, в которых есть умножение значением данного поддерева).Выведите указатель на корень полученного дерева.
//
//https://gemini.google.com/

#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <iomanip>
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
    setlocale(LC_ALL, "rus");

    std::ifstream File("filename.txt");

    if (!File.is_open())
    {
        std::cerr << "Ошибка: Файл filename.txt не найден!" << std::endl;
        return 1;
    }

    std::stack<Node*> Stack;
    std::string Token;

    bool bErrorOccurred = false;

    while (File >> Token)
    {
        if (!IsValidToken(Token))
        {
            std::cerr << "Ошибка: Недопустимый символ: " << Token << std::endl;
            bErrorOccurred = true;
            break;
        }

        if (std::isdigit(Token[0]))
        {
            Stack.push(new Node(std::stoi(Token)));
        }
        else
        {
            if (Stack.size() < 2)
            {
                std::cerr << "Ошибка: Некорректная ОПЗ в файле!" << std::endl;
                bErrorOccurred = true;
                break;
            }

            int Code = (Token == "+") ? -1 :
                (Token == "-") ? -2 :
                (Token == "*") ? -3 :
                (Token == "/") ? -4 : -5;

            Node* Right = Stack.top(); Stack.pop();
            Node* Left = Stack.top(); Stack.pop();

            Node* NewNode = new Node(Code);
            NewNode->left = Left;
            NewNode->right = Right;

            Stack.push(NewNode);
        }
    }

    if (bErrorOccurred || Stack.size() != 1)
    {
        if (!bErrorOccurred)
        {
            std::cerr << "Ошибка: Некорректное выражение!" << std::endl;
        }

        while (!Stack.empty())
        {
            DeleteSubtree(Stack.top());
            Stack.pop();
        }

        return 1;
    }

    Node* Root = Stack.top();

    std::cout << "\n--- Исходное дерево ---" << std::endl;
    PrintTree(Root);

    Root = Transform(Root);

    std::cout << "\n--- Результат (без умножения) ---" << std::endl;
    PrintTree(Root);

    std::cout << "\n================================" << std::endl;
    std::cout << "Указатель на корень: " << Root << std::endl;
    std::cout << "Значение корня:      " << Root->value << std::endl;
    std::cout << "================================" << std::endl;

    DeleteSubtree(Root);

    return 0;
}