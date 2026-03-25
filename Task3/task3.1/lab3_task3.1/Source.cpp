#include "Header.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <algorithm>

// Реализация структуры FlightGraph
FlightGraph::FlightGraph(int count)
    : CityCount(count)
    , AdjacencyMatrix(count, std::vector<int>(count, 0))
{
}

bool FlightGraph::LoadFromFile(const std::string& filename)
{
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cout << "Ошибка: не удалось открыть файл\n";
        return false;
    }

    file >> CityCount;

    if (CityCount <= 0 || CityCount > 15)
    {
        std::cout << "Ошибка: некорректное количество городов\n";
        return false;
    }

    // Изменяем размер матрицы
    AdjacencyMatrix.assign(CityCount, std::vector<int>(CityCount, 0));

    // Чтение матрицы
    for (int row = 0; row < CityCount; ++row)
    {
        for (int col = 0; col < CityCount; ++col)
        {
            file >> AdjacencyMatrix[row][col];
        }
    }

    return ValidateMatrix();
}

bool FlightGraph::ValidateMatrix() const
{
    for (int row = 0; row < CityCount; ++row)
    {
        for (int col = 0; col < CityCount; ++col)
        {
            if (AdjacencyMatrix[row][col] != 0 && AdjacencyMatrix[row][col] != 1)
            {
                std::cout << "Ошибка: матрица должна содержать только 0 и 1\n";
                return false;
            }
        }
    }
    return true;
}

// Реализация класса FlightPathFinder
FlightPathFinder::FlightPathFinder(const FlightGraph& g)
    : graph(g)
    , distances(g.CityCount, -1)
{
}

void FlightPathFinder::FindShortestPaths(int startCity)
{
    // Сброс расстояний
    std::fill(distances.begin(), distances.end(), -1);

    std::queue<int> queue;

    distances[startCity] = 0;
    queue.push(startCity);

    while (!queue.empty())
    {
        int currentCity = queue.front();
        queue.pop();

        for (int nextCity = 0; nextCity < graph.CityCount; ++nextCity)
        {
            if (graph.AdjacencyMatrix[currentCity][nextCity] == 1 &&
                distances[nextCity] == -1)
            {
                distances[nextCity] = distances[currentCity] + 1;
                queue.push(nextCity);
            }
        }
    }
}

std::vector<int> FlightPathFinder::GetCitiesWithMinTransfers(int startCity, int minTransfers) const
{
    std::vector<int> result;

    for (int city = 0; city < graph.CityCount; ++city)
    {
        // Пропускаем начальный город
        if (city == startCity)
        {
            continue;
        }

        // Проверяем, достижим ли город и с не менее чем minTransfers пересадками
        if (distances[city] >= minTransfers)
        {
            result.push_back(city + 1); // Приводим к нумерации с 1
        }
    }

    std::sort(result.begin(), result.end());

    return result;
}

bool FlightPathFinder::ValidateInput(int cityCount, int startCity, int minTransfers)
{
    if (startCity < 1 || startCity > cityCount)
    {
        std::cout << "Ошибка: неверный номер города\n";
        return false;
    }

    if (minTransfers < 0)
    {
        std::cout << "Ошибка: L не может быть отрицательным\n";
        return false;
    }

    return true;
}

// Функция для вывода результата
void PrintResult(const std::vector<int>& cities)
{
    std::cout << "\n=== РЕЗУЛЬТАТ ===\n";

    if (cities.empty())
    {
        std::cout << -1 << std::endl;
    }
    else
    {
        for (size_t index = 0; index < cities.size(); ++index)
        {
            std::cout << cities[index];

            if (index + 1 < cities.size())
            {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}