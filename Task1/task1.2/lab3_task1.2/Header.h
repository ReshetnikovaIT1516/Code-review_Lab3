#include <string>

// Проверка: строка не содержит цифр и спецсимволов
bool IsLettersOnly(const std::string& Input);

// Установка русской локали
void SetRussianLocale();

// Перемешивание слова и подсчет попыток
int ShuffleWordUntilMatch(const std::string& Original, std::string& Shuffled, void(*PrintFunction)(const std::string&));

