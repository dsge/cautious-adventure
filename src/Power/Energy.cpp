#include "../includes/Power/Energy.h"

using namespace app;
using namespace app::Power;

Energy::Energy() {
    this->setValue(0, EnergyUnit::Jules);
}

Energy::Energy(int64_t value) {
    this->setValue(value, EnergyUnit::Jules);
}

Energy::Energy(int64_t value, EnergyUnit unit) {
    this->setValue(value, unit);
}

void Energy::setValue(int64_t value, EnergyUnit unit) {
    switch (unit) {
        case EnergyUnit::KiloJules:
            value *= 1000;
        break;
        case EnergyUnit::MegaJules:
            value *= 1000 * 1000;
        break;
        case EnergyUnit::GigajJules:
            value *= 1000 * 1000 * 1000;
        break;
        case EnergyUnit::TeraJules:
            value *= 1000ULL * 1000 * 1000 * 1000;
        break;
    }
    this->jules = value;
}

int64_t Energy::getValue(EnergyUnit unit) {
    switch (unit) {
        case EnergyUnit::KiloJules:
            return this->jules * 1000;
        break;
        case EnergyUnit::MegaJules:
            return this->jules * 1000 * 1000;
        break;
        case EnergyUnit::GigajJules:
            return this->jules * 1000ULL * 1000 * 1000;
        break;
        case EnergyUnit::TeraJules:
            return this->jules * 1000ULL * 1000ULL * 1000ULL * 1000ULL;
        break;
        default:
        case EnergyUnit::Jules:
            return this->jules;
        break;
    }
}
Energy::operator int() {
    return this->getValue(EnergyUnit::Jules);
}
Energy::operator int64_t() {
    return this->getValue(EnergyUnit::Jules);
}


Energy::~Energy() {
}
