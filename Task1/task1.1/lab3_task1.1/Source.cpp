#include "Header.h"
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <cctype>

void setRussianLocale()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
}

bool isOnlyLetters(const std::string& str)
{
    if (str.empty()) return false;

    for (char c : str)
    {
        // Проверяем, является ли символ буквой (латинской или кириллической)
        // Для кириллицы в Windows-1251: А-Я = 192-223, а-я = 224-255
        // Для латиницы: A-Z = 65-90, a-z = 97-122
        unsigned char uc = static_cast<unsigned char>(c);

        bool isRussianLetter = (uc >= 192 && uc <= 255) && uc != 216; // 216 - это 'Ё', но лучше обработать отдельно
        bool isRussianYo = (uc == 168 || uc == 184); // Ё и ё в Windows-1251
        bool isEnglishLetter = (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');

        if (!isRussianLetter && !isRussianYo && !isEnglishLetter)
        {
            return false;
        }
    }
    return true;
}

bool isOnlyLettersSimple(const std::string& str)
{
    if (str.empty()) return false;

    for (char c : str)
    {
        // Проверяем только латиницу и пробелы
        if (!std::isalpha(static_cast<unsigned char>(c)))
        {
            return false;
        }
    }
    return true;
}

std::string shuffleWord(std::string word)
{
    std::string shuffled = word;

    // Перемешиваем буквы с помощью простого обмена
    for (int i = 0; i < shuffled.length(); i++)
    {
        int j = rand() % shuffled.length();
        std::swap(shuffled[i], shuffled[j]);
    }

    return shuffled;
}