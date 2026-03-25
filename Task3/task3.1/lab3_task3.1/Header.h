#include <string>
#include <vector>

// Структура для хранения информации о графе
struct FlightGraph
{
    int CityCount;
    std::vector<std::vector<int>> AdjacencyMatrix;

    FlightGraph(int count);
    bool LoadFromFile(const std::string& filename);
    bool ValidateMatrix() const;
};

// Класс для поиска путей в графе
class FlightPathFinder
{
private:
    const FlightGraph& graph;
    std::vector<int> distances;

public:
    FlightPathFinder(const FlightGraph& g);

    // Поиск кратчайших расстояний от начального города
    void FindShortestPaths(int startCity);

    // Получение городов, достижимых с не менее чем L пересадками
    std::vector<int> GetCitiesWithMinTransfers(int startCity, int minTransfers) const;

    // Проверка корректности входных данных
    static bool ValidateInput(int cityCount, int startCity, int minTransfers);
};

// Функция для вывода результата
void PrintResult(const std::vector<int>& cities);

