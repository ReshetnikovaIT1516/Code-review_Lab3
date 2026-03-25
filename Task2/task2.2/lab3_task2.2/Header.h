#include <string>

// Узел дерева
struct Node
{
    int Value;
    Node* Left;
    Node* Right;

    Node(int InValue);
};

// Преобразование оператора в код
int OperatorToCode(char InOperator);

// Проверка корректности токена
bool IsValidToken(const std::string& Token);

// Построение дерева из файла
Node* BuildTreeFromFile(const std::string& FileName);

// Вычисление значения поддерева
int Evaluate(Node* Root);

// Проверка наличия умножения в поддереве
bool ContainsMultiplication(Node* Root);

// Удаление дерева
void DeleteTree(Node* Root);

// Преобразование дерева (замена умножения на значение)
Node* TransformTree(Node* Root);

// Вывод дерева
void PrintTree(Node* Root, int Depth = 0);

// Создание тестового файла
void CreateTestFile();
