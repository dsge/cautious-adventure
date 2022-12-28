#pragma once

#include "vendor/Godot.h"

namespace app {

class DaynightCycleManager {

protected:
    /**
     * @brief the multiplier for animationPlayer->get_current_animation_length() to turn it into a 24 hour time
     */
    double dayLengthMultiplier = 1;
    /**
     * @brief at what second of animationPlayer->get_current_animation_position() is is daybreak - it will be treated as 06:00
     */
    double animationDaybreakHour = 9;
    double daybreakHour = 6;

    double animationTimeToHour(double animationTime) const;
    double hourToAnimationTime(double hour) const;

public:
    godot::AnimationPlayer* animationPlayer;

    DaynightCycleManager();
    ~DaynightCycleManager();

    void initDaylengthMultiplier();

    /**
     * @brief 24 hour format, goes from 0.0 to 23.9999999
     *
     * @return double
     */
    double getHour() const;
    /**
     * @brief goes from 0.0 to 59.9999999
     *
     * @return double
     */
    double getMinute() const;

    bool isDaytime() const;
    bool isNighttime() const;
    void playPauseDaynightCycle();
    void pauseDaynightCycle();
    void playDaynightCycle();
    void setTime(double hour);
};

}
