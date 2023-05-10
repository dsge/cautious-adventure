#pragma once

#include <spdlog/spdlog.h>
#include <vector>

namespace app::Power {

class Consumer;
class Provider;

/**
 * @brief Handles the interconnection of multiple power consumers and providers
 */
class Grid {

protected:
    std::vector<std::shared_ptr< Consumer >> consumers;
    std::vector<std::shared_ptr< Provider >> providers;

public:
    Grid();
    ~Grid();
    /**
     * - Apply all the queued Consumer and Provider changes
     * - Recalculate the current power usage
     * - Update the connected Consumer and Provider objects according to the current power usage
     */
    void tick(double delta);

    /**
     * @brief Add a consumer to be present on the network from the next tick
     *
     * @param consumer
     */
    void queueAddConsumer(std::shared_ptr< Consumer > consumer);
    void queueAddProvider(std::shared_ptr< Provider > provider);
    void queueRemoveConsumer(std::shared_ptr< Consumer > consumer);
    void queueRemoveProvider(std::shared_ptr< Provider > provider);
    std::vector<std::shared_ptr< Consumer >> getConsumers();
    std::vector<std::shared_ptr< Provider >> getProviders();


};

}


#include "./Consumer.h"
#include "./Provider.h"
