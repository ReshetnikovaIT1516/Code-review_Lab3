//Юный путешественник решил изучить схему авиационного сообщения Схема авиационного сообщения задана 
// в текстовом файле с именем FileName.в виде матрицы смежности.Первая
//строка файла содержит количество городов(n) n <= 15, связанных авиационным сообщением, а
//следующие n строк хранят матрицу(m), m[i][j] = 0, если не имеется возможности перелета из 
// города i в город j, иначе m[i][j] = 1. Определить номера городов, в которые из города K можно
// долететь не менее чем с L пересадками и более коротких путей к таким городам не существует.
// Перечислите номера таких городов в порядке возрастания.Нумерация городов начинается с 1. Если
//таких городов нет, выведите число(-1).
// 
// https://chat.deepseek.com/


#include "Header.h"
#include <iostream>

//FIX ME: Убрала глобальное использование std
//FIX ME: Разделила на модули
//FIX ME: Перенесла все фигурные скобки на новую строку
//FIX ME: Переименовала некоторые названия функций и переменных
//FIX ME: Изменила пользовательский интерфейс
//FIX ME: Дополнила функции проверок
//FIX ME: Добавила необходимые библиотеки

int main()
{
    setlocale(LC_ALL, "Russian");

    const std::string FileName = "FileName.txt";

    // Создаем и загружаем граф
    FlightGraph graph(0);

    if (!graph.LoadFromFile(FileName))
    {
        return 1;
    }

    // Ввод данных от пользователя
    int startCity = 0;
    int minTransfers = 0;

    std::cout << "Введите номер города K: ";
    std::cin >> startCity;

    std::cout << "Введите минимальное число пересадок L: ";
    std::cin >> minTransfers;

    // Проверка корректности ввода
    if (!FlightPathFinder::ValidateInput(graph.CityCount, startCity, minTransfers))
    {
        return 1;
    }

    // Поиск кратчайших путей
    FlightPathFinder pathFinder(graph);
    pathFinder.FindShortestPaths(startCity - 1); // Приводим к нумерации с 0

    // Получение результата
    std::vector<int> result = pathFinder.GetCitiesWithMinTransfers(startCity - 1, minTransfers);

    // Вывод результата
    PrintResult(result);

    return 0;
}