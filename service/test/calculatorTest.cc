#include "gtest/gtest.h"
#include "../main/include/calculator.h"

TEST(CalculatorTest, sumTest) {
	Calculator instance;
	EXPECT_EQ(3, instance.sum(1, 2));
}
