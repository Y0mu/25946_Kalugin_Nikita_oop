// Задание 5.III. Тесты для библиотеки (GoogleTest).
//
// Что здесь показано:
//   1) обычные проверки: TEST(набор, имя_теста);
//   2) разница между ASSERT_ и EXPECT_;
//   3) примеры "провальных" тестов — они специально отключены приставкой DISABLED_,
//      чтобы проект собирался и все тесты проходили. Чтобы показать падение,
//      уберите приставку DISABLED_ (подробности в build.txt).

#include "my_lib.h"

#include <gtest/gtest.h>

#include <random>
#include <string>

// Чтобы не писать std:: перед каждым именем из стандартной библиотеки.
using namespace std;

// ---------------------------------------------------------------------------
// Тесты "требуемой" функции my_lib::Sum
// ---------------------------------------------------------------------------

TEST(SumTestSuite, SumPositiveNumbers) {
    // Ожидаем 10, получаем my_lib::Sum(4, 6).
    EXPECT_EQ(my_lib::Sum(4, 6), 10);
}

TEST(SumTestSuite, SumWithNegativeNumbers) {
    // Проверяем разные сравнения: =, !=, <, >, <=, >=.
    EXPECT_EQ(my_lib::Sum(-5, 3), -2);
    EXPECT_NE(my_lib::Sum(-5, 3), 0);
    EXPECT_LT(my_lib::Sum(-5, 3), 0);
    EXPECT_LE(my_lib::Sum(2, 2), 4);
    EXPECT_GT(my_lib::Sum(2, 2), 3);
    EXPECT_GE(my_lib::Sum(2, 2), 4);
}

TEST(SumTestSuite, SumWithZero) {
    EXPECT_EQ(my_lib::Sum(0, 0), 0);
    EXPECT_EQ(my_lib::Sum(7, 0), 7);
}

TEST(SumTestSuite, SumOfLargeNumbers) {
    // Проверяем границы типа int.
    EXPECT_EQ(my_lib::Sum(1000000, 2000000), 3000000);
}

// ---------------------------------------------------------------------------
// Демонстрация ASSERT_ и EXPECT_
// ---------------------------------------------------------------------------

// ASSERT_* — критический отказ: если проверка не прошла, тест сразу завершается.
// Поэтому после неудачного ASSERT_EQ следующие строки НЕ выполняются.
TEST(AssertVsExpectTestSuite, AssertStopsTest) {
    ASSERT_EQ(my_lib::Sum(2, 2), 4);        // проходит
    ASSERT_TRUE(my_lib::Sum(2, 2) == 4);    // проходит
    cout << "[ASSERT] все проверки прошли, идём дальше\n";
    ASSERT_GT(my_lib::Sum(10, 1), 10);      // проходит
}

// EXPECT_* — некритический отказ: даже если проверка не прошла,
// тест продолжает выполняться и покажет все остальные ошибки.
TEST(AssertVsExpectTestSuite, ExpectContinuesTest) {
    EXPECT_EQ(my_lib::Sum(2, 2), 4);        // проходит
    EXPECT_EQ(my_lib::Sum(2, 3), 5);        // проходит
    cout << "[EXPECT] проверки не останавливают тест\n";
    EXPECT_TRUE(my_lib::Sum(1, 1) == 2);    // проходит
}

// ---------------------------------------------------------------------------
// Тесты "модифицированной" функции my_random::RandomSum
// Проверяем не точное значение (там есть рандом), а диапазон.
// ---------------------------------------------------------------------------

TEST(RandomSumTestSuite, ResultStaysInRange) {
    const int x = 10;
    const int y = 20;
    const int rangeMin = -20;
    const int rangeMax = 20;

    // Прогоняем много раз: результат обязан попадать в [x + y + rangeMin, x + y + rangeMax].
    for (int i = 0; i < 1000; ++i) {
        const int result = my_random::RandomSumInRange(x, y, rangeMin, rangeMax);
        EXPECT_GE(result, x + y + rangeMin);
        EXPECT_LE(result, x + y + rangeMax);
    }
}

TEST(RandomSumTestSuite, BaseValueAppearsAtLeastOnce) {
    const int x = 5;
    const int y = 7;

    // Иногда добавки нет вообще, значит результат равен x + y.
    // За 1000 попыток такое обязано случиться хотя бы раз.
    bool foundBaseValue = false;
    for (int i = 0; i < 1000; ++i) {
        if (my_random::RandomSumInRange(x, y, -20, 20) == x + y) {
            foundBaseValue = true;
            break;
        }
    }
    EXPECT_TRUE(foundBaseValue);
}

TEST(RandomSumTestSuite, AdditionAppearsAtLeastOnce) {
    const int x = 5;
    const int y = 7;

    // А иногда добавка есть — значит результат отличается от x + y.
    bool foundAddition = false;
    for (int i = 0; i < 1000; ++i) {
        if (my_random::RandomSumInRange(x, y, -20, 20) != x + y) {
            foundAddition = true;
            break;
        }
    }
    EXPECT_TRUE(foundAddition);
}

// ---------------------------------------------------------------------------
// Тесты версии библиотеки и строк
// ---------------------------------------------------------------------------

TEST(LibraryTestSuite, VersionIsThree) {
    EXPECT_EQ(my_lib::Version(), 3);
}

TEST(LibraryTestSuite, StringComparisonExamples) {
    // Строковые проверки GoogleTest: ASSERT_STREQ, ASSERT_STRNE и т. д.
    string name = "my_lib";
    EXPECT_STREQ(name.c_str(), "my_lib");
    EXPECT_STRNE(name.c_str(), "other_lib");
    EXPECT_STRCASEEQ("MY_LIB", "my_lib");   // регистр не важен
}

// ---------------------------------------------------------------------------
// Провальные тесты для демонстрации (отключены приставкой DISABLED_).
//
// Чтобы показать падение, уберите DISABLED_ и пересоберите проект:
//   TEST(FailingTestSuite, ExpectFails) { ... }
//   TEST(FailingTestSuite, AssertFails) { ... }
// ---------------------------------------------------------------------------

// EXPECT_ продолжит тест и покажет ещё и вторую ошибку.
TEST(FailingTestSuite, DISABLED_ExpectFailsButTestContinues) {
    EXPECT_EQ(my_lib::Sum(2, 2), 5);   // ошибка: реально 4
    EXPECT_EQ(my_lib::Sum(2, 2), 6);   // ошибка: реально 4 — но тест дошёл и сюда
}

// ASSERT_ оборвёт тест на первой же ошибке, до второй проверки дело не дойдёт.
TEST(FailingTestSuite, DISABLED_AssertFailsAndStops) {
    ASSERT_EQ(my_lib::Sum(2, 2), 5);   // ошибка: реально 4 — тест останавливается
    EXPECT_EQ(my_lib::Sum(2, 2), 4);   // эта строка уже не выполнится
}
