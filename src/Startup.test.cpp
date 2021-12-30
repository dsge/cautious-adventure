#include "includes/Startup.h"
#include <gtest/gtest.h>
#include <node.hpp>
#include <godot.hpp>


TEST(StartupTest, ThisShouldPass) {

    auto instance = app::Startup::_new();

    auto node = godot::Node::_new();

    EXPECT_NE(instance, node);
}