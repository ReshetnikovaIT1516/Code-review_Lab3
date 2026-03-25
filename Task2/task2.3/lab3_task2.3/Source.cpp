#include "Header.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <cctype>

// Реализация конструктора Node
Node::Node(int val)
    : value(val)
    , left(nullptr)
    , right(nullptr)
{
}

// Функция для визуального отображения знаков в дереве
std::string GetOpSym(int Code)
{
    if (Code == -1) return "+";
    if (Code == -2) return "-";
    if (Code == -3) return "*";
    if (Code == -4) return "/";
    if (Code == -5) return "%";

    return std::to_string(Code);
}

// Печать дерева со знаками
void PrintTree(Node* Root, int Depth)
{
    if (!Root)
    {
        return;
    }

    for (int i = 0; i < Depth; ++i)
    {
        std::cout << "  ";
    }

    std::cout << GetOpSym(Root->value) << std::endl;

    PrintTree(Root->left, Depth + 1);
    PrintTree(Root->right, Depth + 1);
}

int Evaluate(Node* Root)
{
    if (!Root)
    {
        return 0;
    }

    if (Root->value >= 0)
    {
        return Root->value;
    }

    int Left = Evaluate(Root->left);
    int Right = Evaluate(Root->right);

    switch (Root->value)
    {
    case -1: return Left + Right;
    case -2: return Left - Right;
    case -3: return Left * Right;
    case -4: return (Right != 0) ? Left / Right : 0;
    case -5: return (Right != 0) ? Left % Right : 0;
    default:  return 0;
    }
}

void DeleteSubtree(Node* NodePtr)
{
    if (!NodePtr)
    {
        return;
    }

    DeleteSubtree(NodePtr->left);
    DeleteSubtree(NodePtr->right);

    delete NodePtr;
}

Node* Transform(Node* Root)
{
    if (!Root)
    {
        return nullptr;
    }

    Root->left = Transform(Root->left);
    Root->right = Transform(Root->right);

    if (Root->value == -3)
    {
        int Result = Evaluate(Root);

        DeleteSubtree(Root->left);
        DeleteSubtree(Root->right);

        Root->left = nullptr;
        Root->right = nullptr;
        Root->value = Result;
    }

    return Root;
}

bool IsValidToken(const std::string& Token)
{
    if (Token == "+" || Token == "-" || Token == "*" ||
        Token == "/" || Token == "%")
    {
        return true;
    }

    if (!Token.empty() && std::isdigit(Token[0]))
    {
        return true;
    }

    return false;
}

Node* BuildTreeFromFile(const std::string& Filename, bool& ErrorOccurred)
{
    std::ifstream File(Filename);

    if (!File.is_open())
    {
        std::cerr << "Ошибка: Файл " << Filename << " не найден!" << std::endl;
        ErrorOccurred = true;
        return nullptr;
    }

    std::stack<Node*> Stack;
    std::string Token;

    while (File >> Token)
    {
        if (!IsValidToken(Token))
        {
            std::cerr << "Ошибка: Недопустимый символ: " << Token << std::endl;
            ErrorOccurred = true;
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
                ErrorOccurred = true;
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

    if (ErrorOccurred || Stack.size() != 1)
    {
        if (!ErrorOccurred)
        {
            std::cerr << "Ошибка: Некорректное выражение!" << std::endl;
            ErrorOccurred = true;
        }

        while (!Stack.empty())
        {
            DeleteSubtree(Stack.top());
            Stack.pop();
        }

        return nullptr;
    }

    return Stack.top();
}