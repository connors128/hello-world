//
// Created by Connor on 9/23/2024.
//

#include <gtest/gtest.h>

#include "addition.hpp"

TEST(Addition, test_Addition)
{
    EXPECT_EQ(add(1, 1), 2);
}