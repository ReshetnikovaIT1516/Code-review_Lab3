
#include <string>

// Установка русской локали
void SetRussianLocale();

// Проверка, состоит ли строка только из букв
bool IsOnlyLetters(const std::wstring& str);

// Ввод слова от пользователя
std::wstring GetWordFromUser();

// Перемешивание слова до совпадения с оригиналом
void ShuffleUntilMatch(const std::wstring& original);

