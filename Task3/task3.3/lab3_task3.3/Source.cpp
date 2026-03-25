#include "Header.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <algorithm>

// Реализация структуры AirGraph
AirGraph::AirGraph(int count)
    : CityCount(count)
    , Matrix(count, std::vector<int>(count, 0))
{
}

bool AirGraph::LoadFromFile(const std::string& FileName)
{
    std::ifstream File(FileName);

    if (!File.is_open())
    {
        std::cerr << "Ошибка: Файл " << FileName << " не найден." << std::endl;
        return false;
    }

    if (!(File >> CityCount))
    {
        std::cerr << "Ошибка: не удалось прочитать количество городов" << std::endl;
        return false;
    }

    if (CityCount <= 0 || CityCount > 15)
    {
        std::cerr << "Ошибка: некорректное количество городов (должно быть от 1 до 15)" << std::endl;
        return false;
    }

    // Изменяем размер матрицы
    Matrix.assign(CityCount, std::vector<int>(CityCount, 0));

    // Чтение матрицы
    for (int Row = 0; Row < CityCount; ++Row)
    {
        for (int Col = 0; Col < CityCount; ++Col)
        {
            File >> Matrix[Row][Col];
        }
    }

    return ValidateMatrix();
}

bool AirGraph::ValidateMatrix() const
{
    for (int Row = 0; Row < CityCount; ++Row)
    {
        for (int Col = 0; Col < CityCount; ++Col)
        {
            if (Matrix[Row][Col] != 0 && Matrix[Row][Col] != 1)
            {
                std::cerr << "Ошибка: матрица должна содержать только 0 и 1" << std::endl;
                return false;
            }
        }
    }
    return true;
}

// Реализация класса PathFinder
PathFinder::PathFinder(const AirGraph& graph)
    : Graph(graph)
    , Distances(graph.CityCount, -1)
{
}

void PathFinder::FindShortestPaths(int StartCity)
{
    // Сброс расстояний
    std::fill(Distances.begin(), Distances.end(), -1);

    std::queue<int> Queue;

    Distances[StartCity] = 0;
    Queue.push(StartCity);

    while (!Queue.empty())
    {
        int Current = Queue.front();
        Queue.pop();

        for (int Next = 0; Next < Graph.CityCount; ++Next)
        {
            if (Graph.Matrix[Current][Next] == 1 && Distances[Next] == -1)
            {
                Distances[Next] = Distances[Current] + 1;
                Queue.push(Next);
            }
        }
    }
}

std::vector<int> PathFinder::GetCitiesWithMinTransfers(int StartCity, int MinTransfers) const
{
    std::vector<int> Result;

    for (int City = 0; City < Graph.CityCount; ++City)
    {
        // Пропускаем начальный город
        if (City != StartCity && Distances[City] >= MinTransfers)
        {
            Result.push_back(City + 1); // Приводим к нумерации с 1
        }
    }

    // Сортируем в порядке возрастания
    std::sort(Result.begin(), Result.end());

    return Result;
}

bool PathFinder::ValidateInput(int CityCount, int K, int L)
{
    if (K < 1 || K > CityCount)
    {
        std::cout << "-1" << std::endl;
        return false;
    }

    if (L < 0)
    {
        std::cout << "-1" << std::endl;
        return false;
    }

    return true;
}

// Функция для вывода результата
void PrintResult(const std::vector<int>& Cities)
{
    if (Cities.empty())
    {
        std::cout << "-1" << std::endl;
    }
    else
    {
        for (size_t i = 0; i < Cities.size(); ++i)
        {
            std::cout << Cities[i];

            if (i + 1 < Cities.size())
            {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}

// Основная функция решения задачи
void Solve()
{
    const std::string FileName = "FileName.txt";

    // Создаем и загружаем граф
    AirGraph graph;

    if (!graph.LoadFromFile(FileName))
    {
        return;
    }

    // Ввод данных от пользователя
    int K = 0;
    int L = 0;

    std::cout << "Введите город K (1-" << graph.CityCount << "): ";
    std::cin >> K;

    std::cout << "Введите минимальное число пересадок L: ";
    std::cin >> L;

    // Проверка корректности ввода
    if (!PathFinder::ValidateInput(graph.CityCount, K, L))
    {
        return;
    }

    // Поиск кратчайших путей
    PathFinder pathFinder(graph);
    int StartCity = K - 1; // Приводим к нумерации с 0

    pathFinder.FindShortestPaths(StartCity);

    // Получение результата
    std::vector<int> Result = pathFinder.GetCitiesWithMinTransfers(StartCity, L);

    // Вывод результата
    PrintResult(Result);
}