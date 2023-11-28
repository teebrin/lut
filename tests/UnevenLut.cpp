#include "y/lut.h"

#include <gtest/gtest.h>

using namespace y;

TEST(UnevenLut, BelowMin) {
    constexpr std::array<UnevenLut<float>::XYType, 3> table{{{0.0, 1.0}, {2.0, 2.0}, {10.0, 4.0}}};
    const UnevenLut<float> lut{table};
    ASSERT_EQ(lut[-0.5], 1.0);
}

TEST(UnevenLut, AtMin) {
    constexpr std::array<UnevenLut<float>::XYType, 3> table{{{0.0, 1.0}, {2.0, 2.0}, {10.0, 4.0}}};
    const UnevenLut<float> lut{table};
    ASSERT_EQ(lut[0.0], 1.0);
}

TEST(UnevenLut, NearMin) {
    constexpr std::array<UnevenLut<float>::XYType, 3> table{{{0.0, 1.0}, {2.0, 2.0}, {10.0, 4.0}}};
    const UnevenLut<float> lut{table};
    ASSERT_EQ(lut[0.25], 1.125);
}

TEST(UnevenLut, BelowMiddle) {
    constexpr std::array<UnevenLut<float>::XYType, 3> table{{{0.0, 1.0}, {2.0, 2.0}, {10.0, 4.0}}};
    const UnevenLut<float> lut{table};
    ASSERT_EQ(lut[1.75], 1.875);
}

TEST(UnevenLut, AtMiddle) {
    constexpr std::array<UnevenLut<float>::XYType, 3> table{{{0.0, 1.0}, {2.0, 2.0}, {10.0, 4.0}}};
    const UnevenLut<float> lut{table};
    ASSERT_EQ(lut[2.0], 2.0);
}

TEST(UnevenLut, OverMiddle) {
    constexpr std::array<UnevenLut<float>::XYType, 3> table{{{0.0, 1.0}, {2.0, 2.0}, {10.0, 4.0}}};
    const UnevenLut<float> lut{table};
    ASSERT_EQ(lut[2.25], 2.0625);
}

TEST(UnevenLut, NearMax) {
    constexpr std::array<UnevenLut<float>::XYType, 3> table{{{0.0, 1.0}, {2.0, 2.0}, {10.0, 4.0}}};
    const UnevenLut<float> lut{table};
    ASSERT_EQ(lut[9.75], 3.9375);
}

TEST(UnevenLut, AtMax) {
    constexpr std::array<UnevenLut<float>::XYType, 3> table{{{0.0, 1.0}, {2.0, 2.0}, {10.0, 4.0}}};
    const UnevenLut<float> lut{table};
    ASSERT_EQ(lut[10.0], 4.0);
}

TEST(UnevenLut, OverMax) {
    constexpr std::array<UnevenLut<float>::XYType, 3> table{{{0.0, 1.0}, {2.0, 2.0}, {10.0, 4.0}}};
    const UnevenLut<float> lut{table};
    ASSERT_EQ(lut[10.25], 4.0);
}

TEST(UnevenLut, Step) {
    constexpr std::array<UnevenLut<float>::XYType, 4> table{{{0.0, 1.0}, {2.0, 2.0}, {2.0, 4.0}, {10.0, 6.0}}};
    const UnevenLut<float> lut{table};
    ASSERT_EQ(lut[1.75], 1.875);
    ASSERT_EQ(lut[2.0], 4.0);
    ASSERT_EQ(lut[2.25], 4.0625);
}