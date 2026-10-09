// Задание 5.V. Тесты шаблонной библиотеки.
// Один и тот же шаблон проверяется на разных типах — это и есть смысл шаблонов.

#include "my_lib/my_lib.h"
#include "my_lib/my_random.h"

#include <gtest/gtest.h>

#include <string>

// Чтобы не писать std:: перед каждым именем из стандартной библиотеки.
using namespace std;

// ---- my_lib::Sum с одним типом -------------------------------------------------

TEST(SumTemplateTestSuite, WorksWithInt) {
    EXPECT_EQ(my_lib::Sum<int>(4, 6), 10);
    EXPECT_EQ(my_lib::Sum(4, 6), 10);            // тип выведен автоматически
}

TEST(SumTemplateTestSuite, WorksWithDouble) {
    // Для double используем сравнение с плавающей точкой.
    EXPECT_DOUBLE_EQ(my_lib::Sum<double>(1.5, 2.25), 3.75);
    EXPECT_NEAR(my_lib::Sum(0.1, 0.2), 0.3, 1e-9);
}

TEST(SumTemplateTestSuite, WorksWithString) {
    // Важно: оба аргумента должны быть string, иначе шаблон выведет
    // тип как char[N] и оператор + не найдётся.
    EXPECT_EQ(my_lib::Sum(string("a"), string("bcd")), "abcd");
    EXPECT_EQ(my_lib::Sum<string>(string("a"), string("bcd")), "abcd");
}

TEST(SumTemplateTestSuite, WorksWithThreeArguments) {
    EXPECT_EQ(my_lib::Sum<int>(1, 2, 3), 6);
    EXPECT_DOUBLE_EQ(my_lib::Sum<double>(0.5, 0.25, 0.25), 1.0);
}

// ---- my_lib::Sum с разными типами аргументов и результата ----------------------

TEST(SumTemplateTestSuite, DifferentArgumentTypes) {
    // Тип результата указываем первым параметром шаблона.
    EXPECT_EQ((my_lib::Sum<int, int, double>(3, 2.7)), 5);
    EXPECT_DOUBLE_EQ((my_lib::Sum<double, int, double>(3, 2.5)), 5.5);
}

// ---- my_random::RandomSum ------------------------------------------------------

TEST(RandomSumTemplateTestSuite, IntResultStaysInRange) {
    for (int i = 0; i < 1000; ++i) {
        const int result = my_random::RandomSum<int>(5, 7);
        EXPECT_GE(result, 12);
        EXPECT_LE(result, 12 + 99);
    }
}

TEST(RandomSumTemplateTestSuite, DoubleResultStaysInRange) {
    for (int i = 0; i < 1000; ++i) {
        const double result = my_random::RandomSum<double>(1.5, 2.5);
        EXPECT_GE(result, 4.0);
        EXPECT_LE(result, 4.0 + 99.0);
    }
}

TEST(RandomSumTemplateTestSuite, AdditionAppearsAtLeastOnce) {
    bool foundAddition = false;
    for (int i = 0; i < 1000; ++i) {
        if (my_random::RandomSum<int>(5, 7) != 12) {
            foundAddition = true;
            break;
        }
    }
    EXPECT_TRUE(foundAddition);
}

TEST(RandomSumTemplateTestSuite, TwoTemplateParameters) {
    // Третий аргумент другого типа: RandomSum<double, int>(double, double, int).
    EXPECT_DOUBLE_EQ((my_random::RandomSum<double, int>(1.5, 2.0, 2)), 5.5);
}

// ---- Версия библиотеки ---------------------------------------------------------

TEST(LibraryTestSuite, VersionIsFive) {
    EXPECT_EQ(my_lib::Version(), 5);
}

// Провальные тесты для демонстрации (отключены приставкой DISABLED_).
TEST(FailingTestSuite, DISABLED_ExpectFailsButTestContinues) {
    EXPECT_EQ(my_lib::Sum<int>(2, 2), 5);
    EXPECT_EQ(my_lib::Sum<int>(2, 2), 6);   // тоже выполнится
}

TEST(FailingTestSuite, DISABLED_AssertFailsAndStops) {
    ASSERT_EQ(my_lib::Sum<int>(2, 2), 5);   // тест оборвётся
    EXPECT_EQ(my_lib::Sum<int>(2, 2), 4);   // не выполнится
}
