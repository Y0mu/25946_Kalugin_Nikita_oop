// Задание 3.III (9). Умные указатели вместо обычных.
//
// В задании 3.II у нас получился "висячий" указатель: память освободили,
// а указатель остался смотреть на старое место. Здесь показываем, как от этого
// избавиться при помощи умных указателей из <memory>:
//
//   unique_ptr — владелец единственный, копировать нельзя, только перемещать;
//   shared_ptr — владельцев может быть много, внутри счётчик ссылок;
//   weak_ptr   — "наблюдатель", который не мешает освободить память.
//
// Главная мысль: память освобождает деструктор умного указателя.
// Забыть delete стало невозможно, а сам указатель после освобождения обнуляется.

// Подключаем наши "расширенные" функции из задания 3.I.
#include "../task_03_1_extended_functions/extended_sum.h"

#include <iostream>
#include <memory>

// Чтобы не писать std:: перед каждым именем из стандартной библиотеки.
using namespace std;

namespace {

// Умный указатель можно передавать в функцию как обычный указатель —
// но только если функция НЕ пытается его удалять. Здесь мы только читаем.
void PrintSmartValue(const unique_ptr<int>& smart, const char* title) {
    cout << title << " = " << *smart << '\n';
}

// Так выглядит "правильная" работа с чужим указателем:
// функция не владеет памятью и ничего не освобождает.
void PrintRawView(const int* raw, const char* title) {
    if (raw == nullptr) {
        cout << title << ": указатель пустой\n";
        return;
    }
    cout << title << " = " << *raw << '\n';
}

}  // namespace

int main() {
    cout << "=== 1) unique_ptr вместо new/delete ===\n";

    // Обычный указатель: память надо освободить вручную.
    int* raw = new int{ 17 };
    cout << "[1] raw = " << *raw << '\n';
    delete raw;      // если забыть — утечка памяти
    raw = nullptr;   // если забыть — висячий указатель

    // Умный указатель: то же самое значение, но delete писать не нужно.
    unique_ptr<int> smart = make_unique<int>(17);
    PrintSmartValue(smart, "[1] smart");

    // Функция, которая просто читает значение, ничего не ломает.
    PrintRawView(smart.get(), "[1] через get()");

    // Освобождаем вручную — но это безопасно: указатель сам станет пустым.
    smart.reset();
    PrintRawView(smart.get(), "[1] после reset()");

    cout << "\n=== 2) unique_ptr на массив ===\n";

    // Вместо new int[n] используем make_unique<int[]>(n).
    // Скобки [] в типе нужны, чтобы вызывался delete[].
    const int size = 5;
    unique_ptr<int[]> numbers = make_unique<int[]>(size);

    // По умолчанию элементы зануляются: {0, 0, 0, 0, 0}.
    cout << "[2] начальные значения: ";
    for (int i = 0; i < size; ++i) {
        cout << numbers[i] << (i + 1 < size ? ' ' : '\n');
    }

    for (int i = 0; i < size; ++i) {
        numbers[i] = (i + 1) * 10;
    }
    cout << "[2] после заполнения:   ";
    for (int i = 0; i < size; ++i) {
        cout << numbers[i] << (i + 1 < size ? ' ' : '\n');
    }

    // Здесь важно: vector делает то же самое и умеет менять размер.
    // Но задание как раз про замену "сырого" массива на умный указатель.

    cout << "\n=== 3) shared_ptr: несколько владельцев ===\n";

    shared_ptr<int> first = make_shared<int>(50);
    cout << "[3] *first = " << *first << ", владельцев: " << first.use_count() << '\n';

    // Копировать shared_ptr разрешено: это тот же самый объект.
    shared_ptr<int> second = first;
    cout << "[3] *second = " << *second
              << ", владельцев: " << first.use_count() << '\n';

    {
        shared_ptr<int> third = first;
        cout << "[3] внутри блока владельцев: " << first.use_count() << '\n';
    }  // third вышел из области видимости — счётчик уменьшился

    cout << "[3] после выхода из блока владельцев: " << first.use_count() << '\n';

    // Память освободится только тогда, когда уйдёт последний владелец.
    second.reset();
    cout << "[3] после second.reset() владельцев: " << first.use_count() << '\n';
    first.reset();
    cout << "[3] после first.reset() владельцев: " << first.use_count() << '\n';

    cout << "\n=== 4) weak_ptr: наблюдаем, но не владеем ===\n";

    shared_ptr<int> owner = make_shared<int>(99);
    weak_ptr<int> watcher = owner;   // weak_ptr не увеличивает счётчик

    cout << "[4] владельцев: " << owner.use_count()
              << ", объект жив: " << (watcher.expired() ? "нет" : "да") << '\n';

    // Через weak_ptr нельзя обратиться напрямую — сначала "запираем" его в shared_ptr.
    if (shared_ptr<int> locked = watcher.lock()) {
        cout << "[4] *locked = " << *locked << '\n';
    }

    owner.reset();   // последний владелец ушёл, память освобождена

    cout << "[4] после owner.reset() владельцев: " << owner.use_count()
              << ", объект жив: " << (watcher.expired() ? "нет" : "да") << '\n';
    if (watcher.expired()) {
        cout << "[4] lock() вернул пустой указатель — вот так и выглядит "
                     "безопасная проверка\n";
    }

    cout << "\n=== 5) Тот же опыт с рандомом, что и в задании 3.I ===\n";
    cout << "ExtendedModifiedSum<double, int, int>(3, 4) = "
              << ExtendedModifiedSum<double, int, int>(3, 4, -20, 20) << '\n';

    cout << "\n=== 6) Итог ===\n";
    cout << "[6] delete не написан ни разу, а утечек и висячих указателей нет:\n";
    cout << "[6] память освобождает деструктор умного указателя (это и есть RAII)\n";

    return 0;
}
