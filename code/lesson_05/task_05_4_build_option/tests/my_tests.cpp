// Задание 5.IV. Тесты библиотеки.
// Отличие от 5.III только в версии библиотеки (Version() == 4)
// и в том, что весь блок тестов собирается лишь при BUILD_TESTS = ON.

#include "my_lib.h"

#include <gtest/gtest.h>

#include <random>
#include <string>

// Чтобы не писать std:: перед каждым именем из стандартной библиотеки.
using namespace std;

TEST(SumTestSuite, SumPositiveNumbers) {
    EXPECT_EQ(my_lib::Sum(4, 6), 10);
}

TEST(SumTestSuite, SumWithNegativeNumbers) {
    EXPECT_EQ(my_lib::Sum(-5, 3), -2);
    EXPECT_NE(my_lib::Sum(-5, 3), 0);
    EXPECT_LT(my_lib::Sum(-5, 3), 0);
    EXPECT_GE(my_lib::Sum(2, 2), 4);
}

TEST(SumTestSuite, SumWithZero) {
    EXPECT_EQ(my_lib::Sum(0, 0), 0);
    EXPECT_EQ(my_lib::Sum(7, 0), 7);
}

TEST(AssertVsExpectTestSuite, AssertStopsTest) {
    ASSERT_EQ(my_lib::Sum(2, 2), 4);
    cout << "[ASSERT] проверка прошла, идём дальше\n";
    ASSERT_GT(my_lib::Sum(10, 1), 10);
}

TEST(AssertVsExpectTestSuite, ExpectContinuesTest) {
    EXPECT_EQ(my_lib::Sum(2, 2), 4);
    EXPECT_TRUE(my_lib::Sum(1, 1) == 2);
}

TEST(RandomSumTestSuite, ResultStaysInRange) {
    const int x = 10;
    const int y = 20;

    for (int i = 0; i < 1000; ++i) {
        const int result = my_random::RandomSumInRange(x, y, -20, 20);
        EXPECT_GE(result, x + y - 20);
        EXPECT_LE(result, x + y + 20);
    }
}

TEST(RandomSumTestSuite, AdditionAppearsAtLeastOnce) {
    bool foundAddition = false;
    for (int i = 0; i < 1000; ++i) {
        if (my_random::RandomSumInRange(5, 7, -20, 20) != 12) {
            foundAddition = true;
            break;
        }
    }
    EXPECT_TRUE(foundAddition);
}

TEST(LibraryTestSuite, VersionIsFour) {
    EXPECT_EQ(my_lib::Version(), 4);
}

TEST(LibraryTestSuite, StringComparisonExamples) {
    string name = "my_lib";
    EXPECT_STREQ(name.c_str(), "my_lib");
    EXPECT_STRCASEEQ("MY_LIB", "my_lib");
}

// Провальные тесты для демонстрации — включаются снятием приставки DISABLED_.
TEST(FailingTestSuite, DISABLED_ExpectFailsButTestContinues) {
    EXPECT_EQ(my_lib::Sum(2, 2), 5);
    EXPECT_EQ(my_lib::Sum(2, 2), 6);   // выполнится: EXPECT_ не останавливает тест
}

TEST(FailingTestSuite, DISABLED_AssertFailsAndStops) {
    ASSERT_EQ(my_lib::Sum(2, 2), 5);   // тест оборвётся здесь
    EXPECT_EQ(my_lib::Sum(2, 2), 4);   // уже не выполнится
}
