#include "Header.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <cctype>

// Реализация методов структуры Node
Node::Node(int val)
    : value(val)
    , left(nullptr)
    , right(nullptr)
{
}

bool Node::isOperator() const
{
    return value < 0;
}

bool Node::isMultiplication() const
{
    return value == -3;
}

// Преобразование оператора в код
int operatorToCode(char op)
{
    switch (op)
    {
    case '+': return -1;
    case '-': return -2;
    case '*': return -3;
    case '/': return -4;
    case '%': return -5;
    default:  return 0;
    }
}

// Построение дерева из ОПЗ
Node* buildTreeFromRPN(const std::string& filename)
{
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Ошибка: не удалось открыть файл\n";
        return nullptr;
    }

    std::stack<Node*> st;
    std::string token;

    while (file >> token)
    {
        bool isNumber = true;

        for (char c : token)
        {
            if (!isdigit(c))
            {
                isNumber = false;
                break;
            }
        }

        if (!isNumber && token != "+" && token != "-" &&
            token != "*" && token != "/" && token != "%")
        {
            std::cerr << "Ошибка: недопустимый символ в файле: " << token << '\n';
            return nullptr;
        }

        if (token == "+" || token == "-" || token == "*" ||
            token == "/" || token == "%")
        {
            if (st.size() < 2)
            {
                std::cerr << "Ошибка: недостаточно операндов\n";
                return nullptr;
            }

            Node* right = st.top(); st.pop();
            Node* left = st.top(); st.pop();

            Node* node = new Node(operatorToCode(token[0]));
            node->left = left;
            node->right = right;

            st.push(node);

            std::cout << "Добавлен оператор: " << token << '\n';
        }
        else
        {
            int num = std::stoi(token);

            if (num < 0 || num > 9)
            {
                std::cerr << "Ошибка: операнд вне диапазона 0-9: " << num << '\n';
                return nullptr;
            }

            st.push(new Node(num));

            std::cout << "Добавлен операнд: " << num << '\n';
        }
    }

    if (st.size() != 1)
    {
        std::cerr << "Ошибка: некорректное выражение\n";
        return nullptr;
    }

    return st.top();
}

// Вычисление поддерева
int evaluate(Node* node)
{
    if (!node->isOperator())
    {
        return node->value;
    }

    int leftVal = evaluate(node->left);
    int rightVal = evaluate(node->right);

    switch (node->value)
    {
    case -1: return leftVal + rightVal;
    case -2: return leftVal - rightVal;
    case -3: return leftVal * rightVal;
    case -4: return leftVal / rightVal;
    case -5: return leftVal % rightVal;
    }

    return 0;
}

// Проверка наличия умножения в поддереве
bool containsMultiplication(Node* node)
{
    if (!node)
    {
        return false;
    }

    if (node->value == -3)
    {
        return true;
    }

    return containsMultiplication(node->left) ||
        containsMultiplication(node->right);
}

// Удаление дерева
void deleteTree(Node* node)
{
    if (!node)
    {
        return;
    }

    deleteTree(node->left);
    deleteTree(node->right);

    delete node;
}

// Преобразование дерева
Node* transformTree(Node* node)
{
    if (!node)
    {
        return nullptr;
    }

    node->left = transformTree(node->left);
    node->right = transformTree(node->right);

    if (containsMultiplication(node))
    {
        std::cout << "Найдено умножение, вычисляем...\n";

        int result = evaluate(node);

        std::cout << "Результат: " << result << '\n';
        std::cout << "Умножение заменено на число: " << result << '\n';

        deleteTree(node->left);
        deleteTree(node->right);

        node->left = nullptr;
        node->right = nullptr;
        node->value = result;
    }

    return node;
}

// Вывод дерева
void printTree(Node* node, int level)
{
    if (!node)
    {
        return;
    }

    for (int i = 0; i < level; ++i)
    {
        std::cout << "  ";
    }

    switch (node->value)
    {
    case -1: std::cout << "+"; break;
    case -2: std::cout << "-"; break;
    case -3: std::cout << "*"; break;
    case -4: std::cout << "/"; break;
    case -5: std::cout << "%"; break;
    default:  std::cout << node->value; break;
    }

    std::cout << '\n';

    printTree(node->left, level + 1);
    printTree(node->right, level + 1);
}

// Создание тестового файла
void createTestFile()
{
    std::ofstream file("filename.txt");

    if (!file.is_open())
    {
        std::cerr << "Ошибка: не удалось создать файл\n";
        return;
    }

    file << "3 4 5 * +\n";

    std::cout << "Создан тестовый файл\n";
}