#include "y/lut.h"

#include <gtest/gtest.h>

TEST(Lut, BelowMin) {
    std::array<float, 2> table{1.0, 2.0};
    Lut<float> lut{0.0, 1.0, table};
    ASSERT_EQ(lut[-0.5], 1.0);
}

TEST(Lut, AtMin) {
    std::array<float, 2> table{1.0, 2.0};
    Lut<float> lut{0.0, 1.0, table};
    ASSERT_EQ(lut[0.0], 1.0);
}

TEST(Lut, NearMin) {
    std::array<float, 2> table{1.0, 2.0};
    Lut<float> lut{0.0, 1.0, table};
    ASSERT_EQ(lut[0.25], 1.25);
}

TEST(Lut, Between) {
    std::array<float, 2> table{1.0, 2.0};
    Lut<float> lut{0.0, 1.0, table};
    ASSERT_EQ(lut[0.5], 1.5);
}

TEST(Lut, NearMax) {
    std::array<float, 2> table{1.0, 2.0};
    Lut<float> lut{0.0, 1.0, table};
    ASSERT_EQ(lut[0.75], 1.75);
}

TEST(Lut, AtMax) {
    std::array<float, 2> table{1.0, 2.0};
    Lut<float> lut{0.0, 1.0, table};
    ASSERT_EQ(lut[1.0], 2.0);
}

TEST(Lut, OverMax) {
    std::array<float, 2> table{1.0, 2.0};
    Lut<float> lut{0.0, 1.0, table};
    ASSERT_EQ(lut[1.5], 2.0);
}

TEST(Lut, ManySteps) {
    std::array<float, 3> table{1.0, 2.0, 10.0};
    Lut<float> lut{0.0, 1.0, table};
    ASSERT_EQ(lut[0.25], 1.5);
    ASSERT_EQ(lut[0.75], 6.0);
}

TEST(Lut, DifferentInputAndOutputTypes) {
    std::array<float, 3> table{1.0, 2.0, 10.0};
    Lut<float, double> lut{0.0, 1.0, table};
    ASSERT_EQ(lut[0.25], 1.5);
    ASSERT_EQ(lut[0.75], 6.0);
}

TEST(Lut, MinHigherThanMax) {
    // It is not recommended to use a reversed range (lowerX being higher than
    // higherX) because the result is hard to anticipate. But the results are
    // well-defined to a machine!
    std::array<float, 2> table{1.0, 2.0};
    Lut<float> lut{1.0, 0.0, table};
    ASSERT_EQ(lut[0.25], 1.75);
    ASSERT_EQ(lut[0.75], 1.25);
    ASSERT_EQ(lut[2.0], 1.0);
    ASSERT_EQ(lut[-1.0], 2.0);
}

TEST(Lut, MinEqualToMax) {
    // It is not recommended to use a nil range.
    // Inputs below the range will output the first value of the table.
    // Inputs over the range will output the last value of the table.
    // Inputs within (equal) to the nil range may output anything within the table or even NaN.
    std::array<float, 3> table{1.0, 1.5, 2.0};
    Lut<float> lut{0.0, 0.0, table};

    auto lut0 = lut[0.0];
    ASSERT_TRUE(lut0 >= 1.0 && lut0 <= 2.0 || std::isnan(lut0));
    ASSERT_EQ(lut[-1.0], 1.0);
    ASSERT_EQ(lut[1.0], 2.0);
}