#include <string>

// Узел дерева
struct Node
{
    int value;
    Node* left;
    Node* right;

    Node(int val);
    bool isOperator() const;
    bool isMultiplication() const;
};

// Преобразование оператора в код
int operatorToCode(char op);

// Построение дерева из ОПЗ
Node* buildTreeFromRPN(const std::string& filename);

// Вычисление поддерева
int evaluate(Node* node);

// Проверка наличия умножения в поддереве
bool containsMultiplication(Node* node);

// Удаление дерева
void deleteTree(Node* node);

// Преобразование дерева (удаление операций умножения)
Node* transformTree(Node* node);

// Вывод дерева
void printTree(Node* node, int level = 0);

// Создание тестового файла
void createTestFile();
