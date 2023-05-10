#pragma once

#include <spdlog/spdlog.h>
#include "./EnergyUnit.h"
#include <stdint.h>

namespace app::Power {

/**
 * @brief Stores and handles the amount of energy a given Consumer or Provider consumes/provides
 */
class Energy {

protected:
    int64_t jules = 0;

public:
    Energy();
    ~Energy();
    Energy(int64_t value);
    Energy(int64_t value, EnergyUnit unit);
    void setValue(int64_t value = 0, EnergyUnit unit = EnergyUnit::Jules);
    int64_t getValue(EnergyUnit unit = EnergyUnit::Jules);
    operator int();
    operator long();
};

}
