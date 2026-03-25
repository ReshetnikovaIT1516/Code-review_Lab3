#include "Header.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <random>
#include <cctype>
#include <windows.h>

bool IsLettersOnly(const std::string& Input)
{
    for (char Char : Input)
    {
        if (std::isdigit(static_cast<unsigned char>(Char)) ||
            std::ispunct(static_cast<unsigned char>(Char)))
        {
            return false;
        }
    }

    return true;
}

void SetRussianLocale()
{
    setlocale(LC_ALL, "RUS");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
}

int ShuffleWordUntilMatch(const std::string& Original, std::string& Shuffled, void(*PrintFunction)(const std::string&))
{
    std::random_device RandomDevice;
    std::mt19937 Generator(RandomDevice());

    int Count = 0;

    do
    {
        std::shuffle(Shuffled.begin(), Shuffled.end(), Generator);

        if (PrintFunction != nullptr)
        {
            PrintFunction(Shuffled);
        }

        Count++;
    } while (Shuffled != Original);

    return Count;
}