#include "../includes/Power/Consumer.h"

using namespace app;
using namespace app::Power;

Consumer::Consumer() {
    this->energyDemandPerSecond = 0;
}

Consumer::Consumer(Energy energyDemandPerSecond) {
    this->energyDemandPerSecond = energyDemandPerSecond;
}


void Consumer::tick(double delta) {

}


Consumer::~Consumer() {
}
