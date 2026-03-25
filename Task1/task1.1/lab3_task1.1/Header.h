#include <string>

// Установка русской локали
void setRussianLocale();

// Проверка, состоит ли строка только из букв (русских или английских)
bool isOnlyLetters(const std::string& str);

// Альтернативная функция проверки (только латиница)
bool isOnlyLettersSimple(const std::string& str);

// Перемешивание букв в слове в случайном порядке
std::string shuffleWord(std::string word);
