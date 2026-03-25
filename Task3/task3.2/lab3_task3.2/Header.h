#include <string>
#include <vector>

// Структура для хранения графа авиасообщений
struct AirGraph
{
    int CityCount;
    std::vector<std::vector<int>> Matrix;

    // Конструктор
    AirGraph(int count = 0);

    // Загрузка графа из файла
    bool LoadFromFile(const std::string& FileName);

    // Проверка корректности матрицы
    bool ValidateMatrix() const;
};

// Класс для поиска путей в графе
class AirPathFinder
{
private:
    const AirGraph& Graph;
    std::vector<int> Distances;

public:
    // Конструктор
    AirPathFinder(const AirGraph& graph);

    // Поиск кратчайших расстояний от начального города
    void FindShortestPaths(int StartCity);

    // Получение городов с минимальным количеством пересадок
    std::vector<int> GetCitiesWithMinTransfers(int StartCity, int MinTransfers) const;

    // Проверка корректности входных данных
    static bool ValidateInput(int CityCount, int K, int L);
};

// Функция для вывода результата
void PrintResult(const std::vector<int>& Cities);

