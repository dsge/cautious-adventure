#pragma once

#include <spdlog/spdlog.h>
#include "./EnergyUnit.h"
#include "./Energy.h"


namespace app::Power {

class Consumer {

protected:
    Energy energyDemandPerSecond = Energy(0);

public:
    Consumer();
    Consumer(Energy energyDemandPerSecond);
    ~Consumer();
    void tick(double delta);
};

}
