#include "y/lut.h"

#include <gtest/gtest.h>

using namespace y;

TEST(EvenLut, BelowMin) {
    constexpr std::array<float, 2> table{1.0, 2.0};
    const EvenLut<float> lut{0.0, 1.0, table};
    ASSERT_EQ(lut[-0.5], 1.0);
}

TEST(EvenLut, AtMin) {
    constexpr std::array<float, 2> table{1.0, 2.0};
    const EvenLut<float> lut{0.0, 1.0, table};
    ASSERT_EQ(lut[0.0], 1.0);
}

TEST(EvenLut, NearMin) {
    constexpr std::array<float, 2> table{1.0, 2.0};
    const EvenLut<float> lut{0.0, 1.0, table};
    ASSERT_EQ(lut[0.25], 1.25);
}

TEST(EvenLut, Between) {
    constexpr std::array<float, 2> table{1.0, 2.0};
    const EvenLut<float> lut{0.0, 1.0, table};
    ASSERT_EQ(lut[0.5], 1.5);
}

TEST(EvenLut, NearMax) {
    constexpr std::array<float, 2> table{1.0, 2.0};
    const EvenLut<float> lut{0.0, 1.0, table};
    ASSERT_EQ(lut[0.75], 1.75);
}

TEST(EvenLut, AtMax) {
    constexpr std::array<float, 2> table{1.0, 2.0};
    const EvenLut<float> lut{0.0, 1.0, table};
    ASSERT_EQ(lut[1.0], 2.0);
}

TEST(EvenLut, OverMax) {
    constexpr std::array<float, 2> table{1.0, 2.0};
    const EvenLut<float> lut{0.0, 1.0, table};
    ASSERT_EQ(lut[1.5], 2.0);
}

TEST(EvenLut, ManySteps) {
    constexpr std::array<float, 3> table{1.0, 2.0, 10.0};
    const EvenLut<float> lut{0.0, 1.0, table};
    ASSERT_EQ(lut[0.25], 1.5);
    ASSERT_EQ(lut[0.75], 6.0);
}

TEST(EvenLut, DifferentInputAndOutputTypes) {
    constexpr std::array<float, 3> table{1.0, 2.0, 10.0};
    const EvenLut<float, double> lut{0.0, 1.0, table};
    ASSERT_EQ(lut[0.25], 1.5);
    ASSERT_EQ(lut[0.75], 6.0);
}

TEST(EvenLut, MinHigherThanMax) {
    // It is not recommended to use a reversed range (lowerX being higher than
    // higherX) because the result is hard to anticipate. But the results are
    // well-defined to a machine!
    constexpr std::array<float, 2> table{1.0, 2.0};
    const EvenLut<float> lut{1.0, 0.0, table};
    ASSERT_EQ(lut[0.25], 1.75);
    ASSERT_EQ(lut[0.75], 1.25);
    ASSERT_EQ(lut[2.0], 1.0);
    ASSERT_EQ(lut[-1.0], 2.0);
}

TEST(EvenLut, MinEqualToMax) {
    // It is not recommended to use a nil range.
    // Inputs below the range will output the first value of the table.
    // Inputs over the range will output the last value of the table.
    // Inputs within (equal) to the nil range may output anything within the table or even NaN.
    constexpr std::array<float, 3> table{1.0, 1.5, 2.0};
    const EvenLut<float> lut{0.0, 0.0, table};

    const auto lut0 = lut[0.0];
    ASSERT_TRUE(lut0 >= 1.0 && lut0 <= 2.0 || std::isnan(lut0));
    ASSERT_EQ(lut[-1.0], 1.0);
    ASSERT_EQ(lut[1.0], 2.0);
}