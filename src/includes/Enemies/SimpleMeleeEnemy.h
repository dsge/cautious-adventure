#pragma once

#include "../vendor/Godot.h"

#include <spdlog/spdlog.h>

namespace app {

class PlayerCharacterBodyControls;

class SimpleMeleeEnemy : public godot::Node3D {
    GDCLASS(SimpleMeleeEnemy, godot::Node3D);

protected:
    static void _bind_methods();

public:
    SimpleMeleeEnemy();
    ~SimpleMeleeEnemy();
    void _enter_tree() override;

    void _ready() override;
    void _process(double delta) override;
    void _physics_process(double delta) override;
};

}
