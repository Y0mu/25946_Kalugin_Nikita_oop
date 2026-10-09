#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <string>
#include <utility>
#include <vector>

using namespace std;

namespace {

// Читает числа из файла и возвращает вектор плюс признак успеха.
pair<vector<int>, bool> ReadNumbers(const string& fileName) {
    ifstream input(fileName);
    vector<int> numbers;

    if (!input.is_open()) {
        cout << "Не удалось открыть файл " << fileName << '\n';
        return { numbers, false };
    }

    int value = 0;
    while (input >> value) {
        numbers.push_back(value);
    }

    return { numbers, true };
}
// Сколько раз встречается каждое число в векторе.
map<int, int> CountValues(const vector<int>& numbers) {
    map<int, int> counts;
    for (const int& value : numbers) {
        counts[value] += 1;
    }
    return counts;
}
// Печатает "число (сколько раз)" через запятую.
void PrintValuesWithCounts(const vector<int>& values,
                           const map<int, int>& counts) {
    for (size_t i = 0; i < values.size(); ++i) {
        cout << values[i] << " (" << counts.at(values[i]) << " раз)";
        if (i + 1 < values.size()) {
            cout << ", ";
        }
    }
    cout << '\n';
}
}
int main() {
    pair<vector<int>, bool> firstRead = ReadNumbers("data1.txt");
    pair<vector<int>, bool> secondRead = ReadNumbers("data2.txt");

    if (!firstRead.second || !secondRead.second) {
        cout << "Файлы data1.txt и data2.txt должны лежать рядом с программой\n";
        return 1;
    }

    vector<int> firstVector = firstRead.first;
    vector<int> secondVector = secondRead.first;

    // Первый вектор — больший, второй — меньший.
    if (firstVector.size() < secondVector.size()) {
        swap(firstVector, secondVector);
    }

    cout << "первый вектор: " << firstVector.size() << " чисел\n";
    cout << "второй вектор: " << secondVector.size() << " чисел\n";

    const map<int, int> firstCounts = CountValues(firstVector);
    const map<int, int> secondCounts = CountValues(secondVector);

    // ==== 1) Результат бинарной операции через accumulate ====
    cout << "\n=== 1) Результат бинарной операции (accumulate) ===\n";

    // Бинарная операция — вычитание: берём стартовое значение и вычитаем каждый элемент.
    auto subtract = [](int accumulator, int value) {
        return accumulator - value;
    };

    const int firstBinaryResult =
        accumulate(firstVector.begin(), firstVector.end(), 0, subtract);
    const int secondBinaryResult =
        accumulate(secondVector.begin(), secondVector.end(), 0, subtract);

    cout << "первый вектор: 0 - (все элементы) = " << firstBinaryResult << '\n';
    cout << "второй вектор: 0 - (все элементы) = " << secondBinaryResult << '\n';

    // Для сравнения — та же бинарная операция, но записанная функцией, а не лямбдой:
    // accumulate умеет принимать и указатель на функцию.
    cout << "проверка через обычную функцию: "
              << accumulate(firstVector.begin(), firstVector.end(), 0,
                                 [](int accumulator, int value) { return accumulator - value; })
              << '\n';

    // ==== 2) Дублирующиеся числа ====
    cout << "\n=== 2) Дублирующиеся числа ===\n";

    // Числа второго вектора, которые встречаются 2 и более раз.
    vector<int> secondDuplicates;
    for (const pair<const int, int>& item : secondCounts) {
        if (item.second >= 2) {
            secondDuplicates.push_back(item.first);
        }
    }

    // Числа первого вектора, которые встречаются более 3 раз.
    vector<int> firstFrequent;
    for (const pair<const int, int>& item : firstCounts) {
        if (item.second > 3) {
            firstFrequent.push_back(item.first);
        }
    }

    cout << "во втором векторе 2 и более раз встречаются: ";
    PrintValuesWithCounts(secondDuplicates, secondCounts);

    cout << "в первом векторе более 3 раз встречаются:    ";
    PrintValuesWithCounts(firstFrequent, firstCounts);

    // ==== 3) Пересечение: числа, подходящие под оба условия ====
    cout << "\n=== 3) Пересечение (в первом > 3 раз, во втором >= 2 раз) ===\n";

    // Способ 1: цикл for с итераторами.
    // Идём по дубликатам второго вектора и ищем их в первом через find.
    vector<int> intersectionByLoop;
    for (vector<int>::iterator it = secondDuplicates.begin();
         it != secondDuplicates.end(); ++it) {
        if (find(firstFrequent.begin(), firstFrequent.end(), *it) != firstFrequent.end()) {
            intersectionByLoop.push_back(*it);
        }
    }

    cout << "способ 1 (цикл for):\n";
    for (const int& value : intersectionByLoop) {
        cout << "  число " << value
                  << ": в первом векторе " << firstCounts.at(value) << " раз"
                  << ", во втором векторе " << secondCounts.at(value) << " раз\n";
    }

    // Способ 2: copy_if с лямбдой.
    // Копируем из дубликатов второго вектора те числа, которые есть в списке частых.
    vector<int> intersectionByAlgorithm;
    copy_if(secondDuplicates.begin(), secondDuplicates.end(),
                 back_inserter(intersectionByAlgorithm),
                 [&firstFrequent](int value) {
                     return find(firstFrequent.begin(), firstFrequent.end(), value)
                            != firstFrequent.end();
                 });

    cout << "способ 2 (<algorithm> + лямбда):\n";
    for (const int& value : intersectionByAlgorithm) {
        cout << "  число " << value
                  << ": в первом векторе " << firstCounts.at(value) << " раз"
                  << ", во втором векторе " << secondCounts.at(value) << " раз\n";
    }

    cout << "оба способа дали одинаковый результат: "
              << (intersectionByLoop == intersectionByAlgorithm ? "да" : "нет") << '\n';

    // Небольшая проверка "на пальцах": посчитаем вхождения одного числа
    // ещё раз, но уже алгоритмом count_if с лямбдой.
    if (!intersectionByLoop.empty()) {
        const int sample = intersectionByLoop.front();
        const ptrdiff_t sampleCount =
            count_if(firstVector.begin(), firstVector.end(),
                          [sample](int value) { return value == sample; });
        cout << "проверка: count_if для числа " << sample
                  << " дал " << sampleCount << " вхождений\n";
    }

    return 0;
}