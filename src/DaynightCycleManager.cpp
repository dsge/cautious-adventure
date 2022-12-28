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
    return this->animationTimeToHour(this->animationPlayer->get_current_animation_position());
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
        this->pauseDaynightCycle();
    } else {
        this->playDaynightCycle();
    }
}

void DaynightCycleManager::pauseDaynightCycle() {
    if (!this->animationPlayer) {
        return;
    }
    if (this->animationPlayer->is_playing()) {
        this->animationPlayer->stop(false);
    }
}

void DaynightCycleManager::playDaynightCycle() {
    if (!this->animationPlayer) {
        return;
    }
    if (!this->animationPlayer->is_playing()) {
        this->animationPlayer->play();
    }
}

double DaynightCycleManager::animationTimeToHour(double animationTime) const {
    return std::fmod((animationTime + (this->animationDaybreakHour - this->daybreakHour / this->dayLengthMultiplier)) * this->dayLengthMultiplier, 24);
}

double DaynightCycleManager::hourToAnimationTime(double hour) const {
    return hour / this->dayLengthMultiplier - (this->animationDaybreakHour - this->daybreakHour / this->dayLengthMultiplier);
}

void DaynightCycleManager::setTime(double hour) {
    if (!this->animationPlayer) {
        return;
    }
    this->animationPlayer->seek(this->hourToAnimationTime(hour), true);
}


DaynightCycleManager::~DaynightCycleManager() {
}
