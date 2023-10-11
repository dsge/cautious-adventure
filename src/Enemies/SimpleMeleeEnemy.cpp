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

}

void SimpleMeleeEnemy::_ready() {

}

void SimpleMeleeEnemy::_process(double delta) {

}

void SimpleMeleeEnemy::_physics_process(double delta) {

}

SimpleMeleeEnemy::~SimpleMeleeEnemy() {

}
