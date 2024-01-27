#include "../includes/UI/GlobalHealthBar.h"

using namespace app;

void GlobalHealthBar::_bind_methods() {
    godot::ClassDB::bind_method(godot::D_METHOD("ready"), &GlobalHealthBar::_ready);
    godot::ClassDB::bind_method(godot::D_METHOD("process"), &GlobalHealthBar::_process);
    godot::ClassDB::bind_method(godot::D_METHOD("enter_tree"), &GlobalHealthBar::_enter_tree);
    // godot::ClassDB::bind_method(godot::D_METHOD("physics_process"), &GlobalHealthBar::_physics_process);
    godot::ClassDB::bind_method(godot::D_METHOD("onUpdateDestructibleObject", "object"), &GlobalHealthBar::onUpdateDestructibleObject);

    ADD_SIGNAL(godot::MethodInfo(GlobalHealthBar::SIGNAL_UPDATE_DESTRUCTIBLE_OBJECT, godot::PropertyInfo(godot::Variant::OBJECT, "targetObject")));
}

GlobalHealthBar::GlobalHealthBar() {
}

void GlobalHealthBar::_enter_tree() {
    this->set_visible(false);
    this->connect(GlobalHealthBar::SIGNAL_UPDATE_DESTRUCTIBLE_OBJECT, godot::Callable(this, "onUpdateDestructibleObject"));
}

void GlobalHealthBar::_ready() {
}

void GlobalHealthBar::onUpdateDestructibleObject(godot::Variant targetObject) {
    auto obj = Object::cast_to<godot::Node>((godot::Object*)targetObject);
    if (obj != nullptr) {
        this->get_node<godot::Label>("Text")->set_text(obj->get_name());
        this->set_visible(true);
    } else {
        this->set_visible(false);
    }
}

void GlobalHealthBar::_process(double delta) {

}

GlobalHealthBar::~GlobalHealthBar() {

}
