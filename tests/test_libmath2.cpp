/* SPDX-License-Identifier: MIT
 * Copyright (c) 2026 libmath2 contributors
 */

#include <gtest/gtest.h>

extern "C" {
#include "libmath2.h"
}

TEST(Libmath2Add, PositiveNumbers) {
    EXPECT_EQ(libmath2_add(2, 3), 5);
}

TEST(Libmath2Add, NegativeNumbers) {
    EXPECT_EQ(libmath2_add(-2, -3), -5);
}

TEST(Libmath2Add, MixedSign) {
    EXPECT_EQ(libmath2_add(-2, 5), 3);
}

TEST(Libmath2Add, Zero) {
    EXPECT_EQ(libmath2_add(0, 0), 0);
}
