#include "../includes/PlayerControlledEntities/Simpleship.h"

using namespace app;

void Simpleship::_bind_methods() {
    godot::ClassDB::bind_method(godot::D_METHOD("ready"), &Simpleship::_ready);
    godot::ClassDB::bind_method(godot::D_METHOD("process"), &Simpleship::_process);
    godot::ClassDB::bind_method(godot::D_METHOD("enter_tree"), &Simpleship::_enter_tree);
    godot::ClassDB::bind_method(godot::D_METHOD("physics_process"), &Simpleship::_physics_process);
    /*godot::ClassDB::bind_method(godot::D_METHOD("input"), &Simpleship::_input);
    godot::ClassDB::bind_method(godot::D_METHOD("unhandled_input"), &Simpleship::_unhandled_input);*/
    godot::ClassDB::bind_method(godot::D_METHOD("unhandled_key_input"), &Simpleship::_unhandled_key_input);
}

Simpleship::Simpleship() {
    this->controls = new SimpleshipControls();
    this->controls->model = this;

}

void Simpleship::_enter_tree() {
    if (this->controls) {
        this->controls->model_enter_tree();
    }
}

void Simpleship::_ready() {
    if (this->controls) {
        this->controls->model_ready();
    }
}

void Simpleship::_process(double delta) {
    if (this->controls) {
        this->controls->model_process(delta);
    }
}

void Simpleship::_physics_process(double delta) {
    if (this->controls) {
        // this->controls->model_physics_process(delta);
    }
}
/*void Simpleship::_input(const godot::Ref<godot::InputEvent> &event) {
    if (this->controls) {
        // this->controls->model_input(event);
    }
}
void Simpleship::_unhandled_input(const godot::Ref<godot::InputEvent> &event) {
    if (this->controls) {
        // this->controls->model_unhandled_input(event);
    }
}*/
void Simpleship::_unhandled_key_input(const godot::Ref<godot::InputEvent> &event) {
    if (this->controls) {
        this->controls->model_unhandled_key_input(event);
    }
}

godot::Camera3D* Simpleship::getThirdPersonCamera() {
    return this->get_node<godot::Camera3D>("Camera3D");
}

godot::Camera3D* Simpleship::getFirstPersonCamera() {
    return this->get_node<godot::Camera3D>("Camera3D");
}

bool Simpleship::useFirstPersonCameraByDefault() {
    return false;
}

Simpleship::~Simpleship() {
    if (this->controls) {
        delete this->controls;
    }
}
