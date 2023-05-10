#include "../includes/Power/Grid.h"
#include "../includes/Power/Consumer.h"
#include "../includes/Power/Provider.h"
#include <gtest/gtest.h>

TEST(GridTest, ThisShouldPass2) {

    auto instance = std::make_shared<app::Power::Grid>();

    EXPECT_EQ(instance, instance);
    // EXPECT_NE(instance, node);
}

TEST(GridTest, SimpleAddConsumer) {

    auto instance = std::make_shared<app::Power::Grid>();
    instance->queueAddConsumer(std::make_shared<app::Power::Consumer>(15));


    EXPECT_EQ(instance->getConsumers().size(), 1);
    EXPECT_EQ(instance->getProviders().size(), 0);
}
