#pragma once

#include <spdlog/spdlog.h>

namespace app::Power {

class Provider {

public:
    Provider();
    ~Provider();
    void tick(double delta);
};

}
