#include "Header.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <cctype>

// Реализация конструктора Node
Node::Node(int InValue)
    : Value(InValue)
    , Left(nullptr)
    , Right(nullptr)
{
}

// Преобразование оператора в код
int OperatorToCode(char InOperator)
{
    switch (InOperator)
    {
    case '+': return -1;
    case '-': return -2;
    case '*': return -3;
    case '/': return -4;
    case '%': return -5;
    default: return 0;
    }
}

// Проверка корректности токена
bool IsValidToken(const std::string& Token)
{
    if (Token == "+" || Token == "-" || Token == "*" ||
        Token == "/" || Token == "%")
    {
        return true;
    }

    if (Token.empty())
    {
        return false;
    }

    for (char C : Token)
    {
        if (!std::isdigit(C))
        {
            return false;
        }
    }

    int Number = std::stoi(Token);
    return Number >= 0 && Number <= 9;
}

// Построение дерева из файла
Node* BuildTreeFromFile(const std::string& FileName)
{
    std::ifstream File(FileName);

    if (!File.is_open())
    {
        std::cerr << "Ошибка: не удалось открыть файл\n";
        return nullptr;
    }

    std::stack<Node*> NodeStack;
    std::string Token;

    while (File >> Token)
    {
        if (!IsValidToken(Token))
        {
            std::cerr << "Ошибка: недопустимый символ: " << Token << std::endl;
            return nullptr;
        }

        if (Token == "+" || Token == "-" || Token == "*" ||
            Token == "/" || Token == "%")
        {
            if (NodeStack.size() < 2)
            {
                std::cerr << "Ошибка: некорректное выражение\n";
                return nullptr;
            }

            Node* RightNode = NodeStack.top();
            NodeStack.pop();

            Node* LeftNode = NodeStack.top();
            NodeStack.pop();

            Node* NewNode = new Node(OperatorToCode(Token[0]));
            NewNode->Left = LeftNode;
            NewNode->Right = RightNode;

            NodeStack.push(NewNode);
        }
        else
        {
            NodeStack.push(new Node(std::stoi(Token)));
        }
    }

    if (NodeStack.size() != 1)
    {
        std::cerr << "Ошибка: некорректное выражение\n";
        return nullptr;
    }

    return NodeStack.top();
}

// Вычисление значения поддерева
int Evaluate(Node* Root)
{
    if (!Root->Left && !Root->Right)
    {
        return Root->Value;
    }

    int LeftValue = Evaluate(Root->Left);
    int RightValue = Evaluate(Root->Right);

    switch (Root->Value)
    {
    case -1: return LeftValue + RightValue;
    case -2: return LeftValue - RightValue;
    case -3: return LeftValue * RightValue;
    case -4: return LeftValue / RightValue;
    case -5: return LeftValue % RightValue;
    default: return 0;
    }
}

// Проверка наличия умножения в поддереве
bool ContainsMultiplication(Node* Root)
{
    if (!Root)
    {
        return false;
    }

    if (Root->Value == -3)
    {
        return true;
    }

    return ContainsMultiplication(Root->Left) ||
        ContainsMultiplication(Root->Right);
}

// Удаление дерева
void DeleteTree(Node* Root)
{
    if (!Root)
    {
        return;
    }

    DeleteTree(Root->Left);
    DeleteTree(Root->Right);
    delete Root;
}

// Преобразование дерева
Node* TransformTree(Node* Root)
{
    if (!Root)
    {
        return nullptr;
    }

    Root->Left = TransformTree(Root->Left);
    Root->Right = TransformTree(Root->Right);

    if (ContainsMultiplication(Root))
    {
        int Result = Evaluate(Root);

        DeleteTree(Root->Left);
        DeleteTree(Root->Right);

        Root->Left = nullptr;
        Root->Right = nullptr;
        Root->Value = Result;
    }

    return Root;
}

// Вывод дерева
void PrintTree(Node* Root, int Depth)
{
    if (!Root)
    {
        return;
    }

    for (int i = 0; i < Depth; i++)
    {
        std::cout << "  ";
    }

    switch (Root->Value)
    {
    case -1: std::cout << "+"; break;
    case -2: std::cout << "-"; break;
    case -3: std::cout << "*"; break;
    case -4: std::cout << "/"; break;
    case -5: std::cout << "%"; break;
    default: std::cout << Root->Value; break;
    }

    std::cout << '\n';

    PrintTree(Root->Left, Depth + 1);
    PrintTree(Root->Right, Depth + 1);
}

// Создание тестового файла
void CreateTestFile()
{
    std::ofstream File("filename.txt");

    if (!File.is_open())
    {
        std::cerr << "Ошибка: не удалось создать файл\n";
        return;
    }

    File << "3 4 5 * +\n";

    std::cout << "Создан тестовый файл\n";
}