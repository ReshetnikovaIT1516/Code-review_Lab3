#include <string>

// Узел дерева
struct Node
{
    int value;
    Node* left;
    Node* right;

    Node(int val);
};

// Функция для получения символьного представления оператора
std::string GetOpSym(int Code);

// Печать дерева
void PrintTree(Node* Root, int Depth = 0);

// Вычисление значения поддерева
int Evaluate(Node* Root);

// Удаление поддерева
void DeleteSubtree(Node* NodePtr);

// Преобразование дерева (удаление умножения)
Node* Transform(Node* Root);

// Проверка корректности токена
bool IsValidToken(const std::string& Token);

// Построение дерева из файла
Node* BuildTreeFromFile(const std::string& Filename, bool& ErrorOccurred);
