#include "./includes/DaynightCycleManager.h"

using namespace app;


DaynightCycleManager::DaynightCycleManager() {
}

void DaynightCycleManager::initDaylengthMultiplier() {
    if (!this->animationPlayer) {
        return;
    }
    double value = 24 / this->animationPlayer->get_current_animation_length();
    this->dayLengthMultiplier = value;
}


double DaynightCycleManager::getHour() const {
    if (!this->animationPlayer) {
        return 0.0;
    }
    const int daybreakHour = 6;
    return std::fmod((this->animationPlayer->get_current_animation_position() + (this->animationDaybreakHour - daybreakHour / this->dayLengthMultiplier)) * this->dayLengthMultiplier, 24);
}

double DaynightCycleManager::getMinute() const {
    if (!this->animationPlayer) {
        return 0.0;
    }
    auto hourMinute = this->getHour();
    auto minuteRatio = hourMinute - floor(hourMinute);
    return minuteRatio * 60;
}

bool DaynightCycleManager::isDaytime() const {
    auto hour = this->getHour();
    return hour < 18 && hour >= 6;
}

bool DaynightCycleManager::isNighttime() const {
    return !this->isDaytime();
}

void DaynightCycleManager::playPauseDaynightCycle() {
    if (!this->animationPlayer) {
        return;
    }
    if (this->animationPlayer->is_playing()) {
        this->animationPlayer->stop(false);
    } else {
        this->animationPlayer->play();
    }
}


DaynightCycleManager::~DaynightCycleManager() {
}
