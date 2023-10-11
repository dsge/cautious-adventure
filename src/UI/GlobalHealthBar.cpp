#include "../includes/UI/GlobalHealthBar.h"

using namespace app;

void GlobalHealthBar::_bind_methods() {
    godot::ClassDB::bind_method(godot::D_METHOD("ready"), &GlobalHealthBar::_ready);
    godot::ClassDB::bind_method(godot::D_METHOD("process"), &GlobalHealthBar::_process);
    godot::ClassDB::bind_method(godot::D_METHOD("enter_tree"), &GlobalHealthBar::_enter_tree);
    // godot::ClassDB::bind_method(godot::D_METHOD("physics_process"), &GlobalHealthBar::_physics_process);

    ADD_SIGNAL(godot::MethodInfo("update_destructible_object", godot::PropertyInfo(godot::Variant::OBJECT, "name")));
}

GlobalHealthBar::GlobalHealthBar() {
}

void GlobalHealthBar::_enter_tree() {

}

void GlobalHealthBar::_ready() {
}

void GlobalHealthBar::_process(double delta) {

}

GlobalHealthBar::~GlobalHealthBar() {

}
