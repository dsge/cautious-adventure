#include "../includes/Power/Grid.h"

using namespace app;
using namespace app::Power;

Grid::Grid() {


}


void Grid::tick(double delta) {

}

void Grid::queueAddConsumer(std::shared_ptr< Consumer > consumer) {
    this->consumers.push_back(consumer);
}
void Grid::queueAddProvider(std::shared_ptr< Provider > provider) {
    this->providers.push_back(provider);
}
void Grid::queueRemoveConsumer(std::shared_ptr< Consumer > consumer) {
    auto element = std::find(this->consumers.begin(), this->consumers.end(), consumer);
    if (element != this->consumers.end()) {
        auto it = this->consumers.begin();
        std::advance(it, std::distance(this->consumers.begin(), element));
        this->consumers.erase(it);
    }
}
void Grid::queueRemoveProvider(std::shared_ptr< Provider > provider) {
    auto element = std::find(this->providers.begin(), this->providers.end(), provider);
    if (element != this->providers.end()) {
        auto it = this->providers.begin();
        std::advance(it, std::distance(this->providers.begin(), element));
        this->providers.erase(it);
    }
}
std::vector<std::shared_ptr< Consumer >> Grid::getConsumers() {
    return this->consumers;
}
std::vector<std::shared_ptr< Provider >> Grid::getProviders() {
    return this->providers;
}


Grid::~Grid() {
}
