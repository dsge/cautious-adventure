#include "includes/Startup.h"
#include <gtest/gtest.h>
#include <node.hpp>
#include <godot.hpp>


TEST(StartupTest, ThisShouldPass) {

    app::Startup* instance = memnew(app::Startup);

    godot::Node* node = memnew(godot::Node);

    EXPECT_NE(instance, node);

    memdelete(instance);
    memdelete(node);
}

TEST(StartupTest, ThisShouldPass2) {

    app::Startup* instance = memnew(app::Startup);

    godot::Node* node = memnew(godot::Node);

    EXPECT_EQ(instance, instance);

    memdelete(instance);
    memdelete(node);
}