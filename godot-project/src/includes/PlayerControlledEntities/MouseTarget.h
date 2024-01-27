#pragma once

#include "../vendor/Godot.h"

#include <spdlog/spdlog.h>

namespace app {

struct MouseTarget {
    bool isLastMouseClickPositionValid = false;
    godot::Vector2 lastMouseClickPosition = godot::Vector2();
    godot::Node3D* targetedEnemy = NULL;
};

}
