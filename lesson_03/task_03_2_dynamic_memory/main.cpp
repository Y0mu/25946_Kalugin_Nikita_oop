// Задание 3.II (4). Динамическая память.
//
// Что делаем по пунктам задания:
//   1) создаём указатель на одно значение и на массив;
//   2) заполняем массив значениями и выводим их;
//   3) демонстрируем "висячий" указатель и объясняем, в чём опасность;
//   4) добавляем элемент в середину массива, выводим новое содержимое;
//   5) правильно очищаем память (delete / delete[] и nullptr).
//
// ВАЖНО про пункт 3. Обращение к удалённой памяти — это неопределённое поведение:
// программа может напечатать "мусор", может упасть, а может сработать как ни в чём
// не бывало. Поэтому опасный опыт мы запускаем в отдельном дочернем процессе:
// так его падение не мешает показать остальные пункты.

#include <cstdlib>
#include <iostream>

// Чтобы не писать std:: перед каждым именем из стандартной библиотеки.
using namespace std;

namespace {

// Печатает массив заданного размера.
void PrintArray(const int* data, int size) {
    for (int i = 0; i < size; ++i) {
        cout << data[i];
        if (i + 1 < size) {
            cout << ' ';
        }
    }
    cout << '\n';
}

// Пункт 3. Показывает, что "сырой" указатель ничего не знает об освобождении памяти,
// и что спасение — сразу записывать в него nullptr.
// Само опасное чтение памяти вынесено в отдельную программу dangling_demo.cpp
// (см. пункт 3 в main), потому что это неопределённое поведение.
void ShowDanglingPointerProblem() {
    int* dangling = new int{ 777 };
    cout << "[3] до удаления: *dangling = " << *dangling << '\n';

    delete dangling;
    // Память освобождена, но указатель по-прежнему смотрит на старое место.
    // Именно в этот момент он и становится "висячим".
    cout << "[3] после удаления указатель всё ещё хранит адрес "
              << static_cast<const void*>(dangling) << '\n';

    // Спасает только привычка обнулять указатель сразу после delete.
    dangling = nullptr;
    cout << "[3] после dangling = nullptr указатель безопасен: "
              << (dangling == nullptr ? "да" : "нет") << '\n';
}

// Возвращает указатель на локальную переменную.
// Так делать нельзя: функция завершилась, её локальные данные больше не существуют,
// и вызывающий код получает "висячий" указатель.
// Компилятор предупреждает об этом (-Wreturn-local-addr), но здесь это нужно
// показать специально, поэтому предупреждение отключаем только для этой функции.
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreturn-local-addr"
#elif defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4172)  // returning address of local variable
#endif

int* MakeDanglingPointer() {
    int local = 555;
    return &local;  // ошибка: адрес локальной переменной после выхода недействителен
}

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#elif defined(_MSC_VER)
#pragma warning(pop)
#endif

}  // namespace

int main() {
    cout << "=== 1) Указатель на одно значение и указатель на массив ===\n";

    // Указатель на одно значение.
    int* single = new int{ 42 };
    cout << "[1] single = " << *single << '\n';

    // Указатель на массив из 5 элементов.
    const int size = 5;
    int* array = new int[size]{ 10, 20, 30, 40, 50 };

    cout << "[1] массив: ";
    PrintArray(array, size);

    cout << "\n=== 2) Работа с массивом через указатель ===\n";

    // Обращаться к элементам можно и по индексу, и через арифметику указателей.
    cout << "[2] array[2] = " << array[2] << '\n';
    cout << "[2] *(array + 3) = " << *(array + 3) << '\n';

    // Меняем значения через указатель.
    for (int i = 0; i < size; ++i) {
        array[i] = array[i] + 1;
    }
    cout << "[2] после увеличения каждого элемента: ";
    PrintArray(array, size);

    cout << "\n=== 3) \"Висячий\" указатель и его опасность ===\n";

    // Обычный (не умный) указатель никак не сообщает о том, что память освобождена.
    ShowDanglingPointerProblem();

    // Второй источник "висячих" указателей — возврат адреса локальной переменной.
    int* fromFunction = MakeDanglingPointer();
    cout << "[3] MakeDanglingPointer() вернула адрес локальной переменной: "
              << static_cast<const void*>(fromFunction)
              << " — пользоваться им нельзя\n";
    cout << "[3] проверка: fromFunction == nullptr? "
              << (fromFunction == nullptr ? "да" : "нет")
              << " (компилятор не подсказывает об ошибке!)\n";
    fromFunction = nullptr;

    // Теперь покажем, что реально происходит при обращении к освобождённой памяти.
    cout << "[3] запускаем опасный опыт в отдельном процессе...\n";
    cout.flush();

#if defined(_WIN32)
    const char* demoCommand = "dangling_demo.exe";
#else
    const char* demoCommand = "./dangling_demo";
#endif

    const int code = system(demoCommand);
    if (code == 0) {
        cout << "[3] процесс завершился нормально, но напечатанное значение "
                     "всё равно мусор\n";
    } else {
        cout << "[3] процесс упал с кодом " << code
                  << " — это и есть опасность висячего указателя\n";
    }

    cout << "\n=== 4) Добавляем элемент в середину массива ===\n";

    // В обычном массиве места "в середине" нет, поэтому:
    //   - выделяем новый массив на один элемент больше;
    //   - копируем первую половину;
    //   - вставляем новый элемент;
    //   - копируем вторую половину;
    //   - освобождаем старый массив и переходим на новый.
    const int newSize = size + 1;
    int* bigger = new int[newSize];

    const int insertIndex = size / 2;  // позиция, куда вставляем
    const int insertedValue = 999;

    for (int i = 0; i < insertIndex; ++i) {
        bigger[i] = array[i];
    }
    bigger[insertIndex] = insertedValue;
    for (int i = insertIndex; i < size; ++i) {
        bigger[i + 1] = array[i];
    }

    // Старую память освобождаем обязательно, иначе получим утечку.
    delete[] array;
    array = nullptr;   // теперь array никуда не указывает

    array = bigger;    // работаем с новым массивом
    bigger = nullptr;

    cout << "[4] массив после вставки " << insertedValue
              << " в позицию " << insertIndex << ": ";
    PrintArray(array, newSize);

    cout << "\n=== 5) Правильное освобождение памяти ===\n";

    // delete[] — для массивов, просто delete — для одиночных значений.
    // После освобождения сразу ставим nullptr, чтобы случайно не удалить дважды.
    delete[] array;
    array = nullptr;

    delete single;
    single = nullptr;

    cout << "[5] память освобождена, указатели переведены в nullptr\n";
    cout << "[5] array == nullptr: " << (array == nullptr) << '\n';
    cout << "[5] single == nullptr: " << (single == nullptr) << '\n';

    // Приятный бонус: delete nullptr и delete[] nullptr разрешены и ничего не делают.
    delete[] array;
    delete single;

    return 0;
}
