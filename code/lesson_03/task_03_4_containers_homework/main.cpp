// Задание 3.IV. Домашнее задание.
//
// По пунктам задания:
//   1) создаём контейнеры array, vector, list, deque одинаковой длины M
//      и заполняем их случайными значениями типа T1 из диапазона -N..N;
//   2) перебираем контейнеры тремя формами цикла for:
//      классическая форма, форма с итераторами и range-based;
//   3) к каждому элементу применяем "расширенную модифицированную" функцию из задания 3.I,
//      второй аргумент генерируется случайно ОДИН раз и потом постоянен для всех контейнеров;
//   4) результаты (тип T2) складываем в контейнеры другого типа
//      (для vector — в list, для array — в deque, для list — в vector, для deque — в array);
//   5) одним циклом собираем строки таблицы со значениями через разделитель |;
//   6) оформляем таблицу в формате Markdown, пишем её в файл и показываем на экране.
//
// Индивидуальные параметры: T1 = int, T2 = double, M = 10, N = 20.

// "Расширенная модифицированная" функция из задания 3.I.
#include "../task_03_1_extended_functions/extended_sum.h"

#include <array>
#include <deque>
#include <fstream>
#include <iostream>
#include <list>
#include <random>
#include <sstream>
#include <string>
#include <vector>

// Чтобы не писать std:: перед каждым именем из стандартной библиотеки.
using namespace std;

namespace {

// Индивидуальные параметры варианта.
const int kSize = 10;      // M — длина всех контейнеров
const int kRange = 20;     // N — значения лежат в диапазоне [-N, N]
const char* kFileName = "table.md";

// Тип T1 (что хранится в исходных контейнерах) и тип T2 (что получается после функции).
using T1 = int;
using T2 = double;

// Один генератор на всю программу.
mt19937& Generator() {
    static mt19937 generator{ random_device{}() };
    return generator;
}

// Случайное целое из диапазона [-kRange, kRange].
int RandomValue() {
    uniform_int_distribution<int> distribution{ -kRange, kRange };
    return distribution(Generator());
}

// Превращает значение в строку. Нужно, чтобы собрать строку таблицы
// из значений разных типов без лишних пробелов.
template <typename T>
string ToText(const T& value) {
    ostringstream out;
    out << value;
    return out.str();
}

// Склеивает значения одной строки таблицы в строку через разделитель |.
// Ровно один пробел с каждой стороны от | — так выглядит аккуратная md-таблица.
template <typename... TValues>
string MakeTableRow(const TValues&... values) {
    const string cells[] = { ToText(values)... };

    string row;
    const size_t count = sizeof...(values);
    for (size_t i = 0; i < count; ++i) {
        if (i > 0) {
            row += " | ";
        }
        row += cells[i];
    }
    return row;
}

// Печатает таблицу в формате Markdown.
// headers — заголовки столбцов, rows — уже готовые строки вида "1 | 2 | 3".
void PrintMarkdownTable(const vector<string>& headers,
                        const vector<string>& rows) {
    for (size_t i = 0; i < headers.size(); ++i) {
        cout << '|' << headers[i];
    }
    cout << "|\n";

    for (size_t i = 0; i < headers.size(); ++i) {
        cout << "|---";
    }
    cout << "|\n";

    for (const string& row : rows) {
        cout << '|' << row << "|\n";
    }
}

// Оформляет таблицу и записывает её в md-файл.
void SaveMarkdownTable(const vector<string>& headers,
                       const vector<string>& rows,
                       const string& fileName) {
    ofstream out(fileName);

    if (!out.is_open()) {
        cout << "\nНе удалось открыть файл " << fileName << " для записи\n";
        return;
    }

    // Шапка таблицы.
    for (size_t i = 0; i < headers.size(); ++i) {
        out << '|' << headers[i];
    }
    out << "|\n";

    // Разделительная строка.
    for (size_t i = 0; i < headers.size(); ++i) {
        out << "|---";
    }
    out << "|\n";

    // Сами данные.
    for (const string& row : rows) {
        out << '|' << row << "|\n";
    }

    // Файл закроется сам в деструкторе ofstream (это RAII из лекции 3).
    cout << "\nТаблица записана в файл " << fileName << '\n';
}

}  // namespace

int main() {
    cout << "Параметры: M = " << kSize << ", N = " << kRange
              << ", T1 = int, T2 = double\n";

    // Общий "шаблонный близнец" функции из задания 3.I: вход типа T1, результат типа T2.
    cout << "\nПроверка расширенной заданной функции: ExtendedSum<double, int, int>(3, 4) = "
              << ExtendedSum<double, T1, T1>(3, 4) << '\n';

    // ---- 1. Создаём контейнеры одинаковой длины и заполняем случайными значениями ----
    // array — размер известен на этапе компиляции.
    array<T1, kSize> arrayContainer{};
    vector<T1> vectorContainer;
    list<T1> listContainer;
    deque<T1> dequeContainer;

    vectorContainer.reserve(kSize);

    // Классическая форма цикла for: счётчик по индексу.
    for (int i = 0; i < kSize; ++i) {
        arrayContainer[i] = static_cast<T1>(RandomValue());
    }
    for (int i = 0; i < kSize; ++i) {
        vectorContainer.push_back(static_cast<T1>(RandomValue()));
    }
    // В list и deque обращаться по индексу нельзя, поэтому заполняем через push_back.
    for (int i = 0; i < kSize; ++i) {
        listContainer.push_back(static_cast<T1>(RandomValue()));
    }
    for (int i = 0; i < kSize; ++i) {
        dequeContainer.push_back(static_cast<T1>(RandomValue()));
    }

    // ---- 2. Три формы цикла for -------------------------------------------------

    cout << "\nПеребор array классической формой for: ";
    for (int i = 0; i < kSize; ++i) {
        cout << arrayContainer[i] << ' ';
    }
    cout << '\n';

    cout << "Перебор vector через итераторы:        ";
    for (vector<T1>::iterator it = vectorContainer.begin(); it != vectorContainer.end(); ++it) {
        cout << *it << ' ';
    }
    cout << '\n';

    cout << "Перебор list через range-based for:    ";
    for (const T1& value : listContainer) {
        cout << value << ' ';
    }
    cout << '\n';

    cout << "Перебор deque через итераторы:         ";
    for (deque<T1>::iterator it = dequeContainer.begin(); it != dequeContainer.end(); ++it) {
        cout << *it << ' ';
    }
    cout << '\n';

    // ---- 3. Второй аргумент функции: генерируем ОДИН раз ------------------------
    // Он остаётся постоянным для всех контейнеров.
    const int secondArgument = RandomValue();
    cout << "\nВторой аргумент расширенной модифицированной функции: "
              << secondArgument << " (постоянный для всех контейнеров)\n";

    // ---- 4. Применяем функцию и складываем результаты в контейнеры другого типа ---

    // array -> deque
    deque<T2> fromArray;
    for (int i = 0; i < kSize; ++i) {
        fromArray.push_back(ExtendedModifiedSum<T2, T1, T1>(arrayContainer[i], secondArgument,
                                                            -kRange, kRange, false));
    }

    // vector -> list
    list<T2> fromVector;
    for (vector<T1>::iterator it = vectorContainer.begin(); it != vectorContainer.end(); ++it) {
        fromVector.push_back(ExtendedModifiedSum<T2, T1, T1>(*it, secondArgument,
                                                             -kRange, kRange, false));
    }

    // list -> vector
    vector<T2> fromList;
    for (const T1& value : listContainer) {
        fromList.push_back(ExtendedModifiedSum<T2, T1, T1>(value, secondArgument,
                                                           -kRange, kRange, false));
    }

    // deque -> array
    array<T2, kSize> fromDeque{};
    for (int i = 0; i < kSize; ++i) {
        fromDeque[i] = ExtendedModifiedSum<T2, T1, T1>(dequeContainer[i], secondArgument,
                                                       -kRange, kRange, false);
    }

    // ---- 5. Одним циклом собираем строки таблицы --------------------------------
    // Внутри одного цикла for обходим все контейнеры и формируем строку таблицы.
    vector<string> rows;
    for (int i = 0; i < kSize; ++i) {
        // К элементу list по индексу не обратиться — двигаем итератор вручную.
        list<T1>::iterator listIt = listContainer.begin();
        advance(listIt, i);

        list<T2>::iterator fromVectorIt = fromVector.begin();
        advance(fromVectorIt, i);

        rows.push_back(MakeTableRow(i,
                                    arrayContainer[i],
                                    vectorContainer[i],
                                    *listIt,
                                    dequeContainer[i],
                                    fromArray[i],
                                    *fromVectorIt,
                                    fromList[i],
                                    fromDeque[i]));
    }

    // ---- 6. Таблица в md-формате -------------------------------------------------
    const vector<string> headers = {
        "i", "array<T1>", "vector<T1>", "list<T1>", "deque<T1>",
        "array->deque<T2>", "vector->list<T2>", "list->vector<T2>", "deque->array<T2>"
    };

    cout << "\nТаблица (Markdown):\n\n";
    PrintMarkdownTable(headers, rows);
    SaveMarkdownTable(headers, rows, kFileName);

    return 0;
}
