#include "includes/SceneSwitcher.h"
#include <gtest/gtest.h>
#include <node.hpp>
#include <godot.hpp>


TEST(SceneSwitcherTest, ThisShouldPass) {

    auto instance = std::make_shared<app::SceneSwitcher>();

    EXPECT_TRUE(instance != nullptr);
}