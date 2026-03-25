#include "Header.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <random>
#include <cwctype>
#include <Windows.h>

void SetRussianLocale()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
}

bool IsOnlyLetters(const std::wstring& str)
{
    for (wchar_t ch : str)
    {
        if (!std::iswalpha(ch))
        {
            return false;
        }
    }
    return true;
}

std::wstring GetWordFromUser()
{
    std::wstring word;

    while (true)
    {
        std::wcout << L"Введите слово: ";

        if (!(std::wcin >> word))
        {
            std::wcin.clear();
            std::wcin.ignore(10000, L'\n');
            continue;
        }

        if (IsOnlyLetters(word))
        {
            return word;
        }

        std::wcout << L"Ошибка! Вводите только буквы.\n";
    }
}

void ShuffleUntilMatch(const std::wstring& original)
{
    std::wstring current = original;
    long long attempts = 0;
    const long long MAX_ATTEMPTS = 1000000;

    std::random_device randomDevice;
    std::mt19937 randomGenerator(randomDevice());

    do
    {
        std::shuffle(current.begin(), current.end(), randomGenerator);

        std::wcout << current << std::endl;
        ++attempts;

        if (attempts > MAX_ATTEMPTS)
        {
            std::wcout << L"Слишком много попыток, прерывание..." << std::endl;
            break;
        }

    } while (current != original);

    std::wcout << L"Количество попыток: " << (attempts - 1) << std::endl;
}