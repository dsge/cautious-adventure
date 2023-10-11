#include "../includes/Enemies/SimpleMeleeEnemy.h"

using namespace app;

void SimpleMeleeEnemy::_bind_methods() {
    godot::ClassDB::bind_method(godot::D_METHOD("ready"), &SimpleMeleeEnemy::_ready);
    godot::ClassDB::bind_method(godot::D_METHOD("process"), &SimpleMeleeEnemy::_process);
    godot::ClassDB::bind_method(godot::D_METHOD("enter_tree"), &SimpleMeleeEnemy::_enter_tree);
    godot::ClassDB::bind_method(godot::D_METHOD("physics_process"), &SimpleMeleeEnemy::_physics_process);
}

SimpleMeleeEnemy::SimpleMeleeEnemy() {
}

void SimpleMeleeEnemy::_enter_tree() {
    this->animationPlayer = this->get_node<godot::AnimationPlayer>("AnimationPlayer");
}

void SimpleMeleeEnemy::animate(godot::String animationName, bool forcePlay) {
    if (this->currentAnimation != animationName || forcePlay) {
        this->currentAnimation = animationName;
        this->animationPlayer->play(this->currentAnimation);
    }
}

void SimpleMeleeEnemy::onHit(std::shared_ptr<HitData> hitData) {

}

void SimpleMeleeEnemy::_ready() {
    this->animate(this->currentAnimation, true);
}

void SimpleMeleeEnemy::_process(double delta) {

}

void SimpleMeleeEnemy::_physics_process(double delta) {

}

SimpleMeleeEnemy::~SimpleMeleeEnemy() {

}
