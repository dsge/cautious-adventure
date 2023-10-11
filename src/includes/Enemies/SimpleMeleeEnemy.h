#pragma once

#include "../vendor/Godot.h"
#include "../enums/EnemyAnimations.h"
#include "../interfaces/DestructibleInterface.h"
#include "../HitData.h"

#include <spdlog/spdlog.h>

namespace app {

class PlayerCharacterBodyControls;

class SimpleMeleeEnemy : public godot::RigidBody3D, public DestructibleInterface {
    GDCLASS(SimpleMeleeEnemy, godot::RigidBody3D);

public:
    godot::String currentAnimation = EnemyAnimations::IDLE;

    static void _bind_methods();
    SimpleMeleeEnemy();
    ~SimpleMeleeEnemy();
    void _enter_tree() override;

    void _ready() override;
    void _process(double delta) override;
    void _physics_process(double delta) override;
    void onHit(std::shared_ptr<HitData> hitData) override;

protected:
    godot::AnimationPlayer* animationPlayer = NULL;
    void animate(godot::String animationName, bool forcePlay = false);
};

}
