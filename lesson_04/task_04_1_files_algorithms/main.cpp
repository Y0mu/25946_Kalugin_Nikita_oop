#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <string>
#include <utility>
#include <vector>

using namespace std;

namespace {

// Чтение данных из файла
// Возвращаем пару: вектор чисел и признак успеха (чтобы понять, открылся ли файл).
pair<vector<int>, bool> ReadNumbers(const string& fileName) {
    ifstream input(fileName);
    vector<int> numbers;

    if (!input.is_open()) {
        cout << "Не удалось открыть файл " << fileName << '\n';
        return { numbers, false };
    }

    int value = 0;
    // Читаем до тех пор, пока из файла приходят числа.
    while (input >> value) {
        numbers.push_back(value);
    }

    return { numbers, true };
}

// Подсчёт количества каждого числа (способ 1: цикл)
// Получаем map, где ключ — число, а значение — сколько раз оно встретилось.
// Обратите внимание: цикл range-based, как и просили в задании.
map<int, int> CountByLoop(const vector<int>& numbers) {
    map<int, int> counts;
    for (const int& value : numbers) {
        counts[value] += 1;   // если числа ещё не было, map создаст его со значением 0
    }
    return counts;
}

//  Подсчёт количества каждого числа (способ 2: алгоритм + лямбда)
// for_each проходит по вектору, а лямбда увеличивает счётчик в map.
// Переменную counts захватываем по ссылке, чтобы изменения были видны снаружи.
map<int, int> CountByAlgorithm(const vector<int>& numbers) {
    map<int, int> counts;
    for_each(numbers.begin(), numbers.end(), [&counts](int value) {
        counts[value] += 1;
    });
    return counts;
}

// Печатает "число: сколько раз" в одну строку.
void PrintCounts(const map<int, int>& counts) {
    for (const pair<const int, int>& item : counts) {
        cout << item.first << ": " << item.second << "  ";
    }
    cout << '\n';
}

// Сумма первых 10 элементов без циклов 
// Здесь нет ни for, ни while: только accumulate по части диапазона.
int SumFirstTen(const vector<int>& numbers) {
    if (numbers.empty()) {
        return 0;
    }

    // Сколько элементов реально можем взять: 10 или меньше, если вектор короче.
    const size_t count = min<size_t>(10, numbers.size());
    const vector<int>::const_iterator last = numbers.begin() + count;

    return accumulate(numbers.begin(), last, 0);
}

}  // namespace

int main() {
    cout << "=== 1) Читаем два набора чисел из файлов ===\n";

    pair<vector<int>, bool> firstRead = ReadNumbers("data1.txt");
    pair<vector<int>, bool> secondRead = ReadNumbers("data2.txt");

    if (!firstRead.second || !secondRead.second) {
        cout << "Файлы data1.txt и data2.txt должны лежать рядом с программой\n";
        return 1;
    }

    vector<int> firstVector = firstRead.first;
    vector<int> secondVector = secondRead.first;

    // По условию первый вектор — больший, второй — меньший.
    if (firstVector.size() < secondVector.size()) {
        swap(firstVector, secondVector);
        cout << "(файлы пришлось поменять местами: первый вектор должен быть больше)\n";
    }

    // 2) Количество чисел в каждом векторе
    cout << "\n=== 2) Количество чисел ===\n";
    cout << "первый вектор: " << firstVector.size() << " чисел\n";
    cout << "второй вектор: " << secondVector.size() << " чисел\n";

    // 3) Сколько раз встречается каждое число — двумя способами
    cout << "\n=== 3) Сколько раз встречается каждое число ===\n";

    const map<int, int> firstCountsLoop = CountByLoop(firstVector);
    const map<int, int> firstCountsAlgorithm = CountByAlgorithm(firstVector);

    cout << "первый вектор (цикл for):        ";
    PrintCounts(firstCountsLoop);
    cout << "первый вектор (<algorithm>):     ";
    PrintCounts(firstCountsAlgorithm);

    const map<int, int> secondCountsLoop = CountByLoop(secondVector);
    const map<int, int> secondCountsAlgorithm = CountByAlgorithm(secondVector);

    cout << "второй вектор (цикл for):        ";
    PrintCounts(secondCountsLoop);
    cout << "второй вектор (<algorithm>):     ";
    PrintCounts(secondCountsAlgorithm);

    // Проверяем, что оба способа дали одинаковый результат.
    cout << "оба способа совпали для первого вектора: "
              << (firstCountsLoop == firstCountsAlgorithm ? "да" : "нет") << '\n';
    cout << "оба способа совпали для второго вектора: "
              << (secondCountsLoop == secondCountsAlgorithm ? "да" : "нет") << '\n';

    // 4) Сумма всех значений — два варианта через <numeric>/<algorithm> 
    cout << "\n=== 4) Сумма всех значений ===\n";

    // Вариант 1: accumulate со значением по умолчанию (обычное сложение).
    const int firstSumVariant1 = accumulate(firstVector.begin(), firstVector.end(), 0);
    const int secondSumVariant1 = accumulate(secondVector.begin(), secondVector.end(), 0);

    // Вариант 2: accumulate со своей лямбдой (явно описываем сложение),
    // плюс для сравнения сумма через reduce-подобный подход не нужна —
    // покажем ещё и accumulate с plus.
    const int firstSumVariant2 = accumulate(firstVector.begin(), firstVector.end(), 0,
                                                [](int sum, int value) { return sum + value; });
    const int secondSumVariant2 = accumulate(secondVector.begin(), secondVector.end(), 0,
                                                 plus<int>());

    cout << "первый вектор: вариант 1 = " << firstSumVariant1
              << ", вариант 2 = " << firstSumVariant2 << '\n';
    cout << "второй вектор: вариант 1 = " << secondSumVariant1
              << ", вариант 2 = " << secondSumVariant2 << '\n';

    // 5) Сумма первых 10 элементов без циклов 
    cout << "\n=== 5) Сумма первых 10 элементов (без циклов) ===\n";
    cout << "первый вектор: " << SumFirstTen(firstVector) << '\n';
    cout << "второй вектор: " << SumFirstTen(secondVector)
              << " (во втором векторе меньше 10 чисел, поэтому просуммировались все)\n";

    return 0;
}
