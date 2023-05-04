#include "../includes/PlayerControlledEntities/Hovership.h"

using namespace app;

void Hovership::_bind_methods() {
    godot::ClassDB::bind_method(godot::D_METHOD("ready"), &Hovership::_ready);
    godot::ClassDB::bind_method(godot::D_METHOD("process"), &Hovership::_process);
    godot::ClassDB::bind_method(godot::D_METHOD("enter_tree"), &Hovership::_enter_tree);
    godot::ClassDB::bind_method(godot::D_METHOD("physics_process"), &Hovership::_physics_process);
    /*godot::ClassDB::bind_method(godot::D_METHOD("input"), &Hovership::_input);
    godot::ClassDB::bind_method(godot::D_METHOD("unhandled_input"), &Hovership::_unhandled_input);*/
    godot::ClassDB::bind_method(godot::D_METHOD("unhandled_key_input"), &Hovership::_unhandled_key_input);
}

Hovership::Hovership() {


}

void Hovership::_enter_tree() {
    if (this->controls) {
        this->controls->model_enter_tree();
    }
}

void Hovership::_ready() {
    if (this->controls) {
        this->controls->model_ready();
    }
}

void Hovership::_process(double delta) {
    if (this->controls) {
        this->controls->model_process(delta);
    }
}

void Hovership::_physics_process(double delta) {
    if (this->controls) {
        // this->controls->model_physics_process(delta);
    }
}
/*void Hovership::_input(const godot::Ref<godot::InputEvent> &event) {
    if (this->controls) {
        // this->controls->model_input(event);
    }
}
void Hovership::_unhandled_input(const godot::Ref<godot::InputEvent> &event) {
    if (this->controls) {
        // this->controls->model_unhandled_input(event);
    }
}*/
void Hovership::_unhandled_key_input(const godot::Ref<godot::InputEvent> &event) {
    if (this->controls) {
        this->controls->model_unhandled_key_input(event);
    }
}

godot::Camera3D* Hovership::getThirdPersonCamera() {
    return this->get_node<godot::Camera3D>("Camera3D");
}

godot::Camera3D* Hovership::getFirstPersonCamera() {
    return this->get_node<godot::Camera3D>("Camera3D");
}

bool Hovership::useFirstPersonCameraByDefault() {
    return false;
}

void Hovership::enableControls() {
    if (!this->controls) {
        this->controls = new HovershipControls();
        this->controls->model = this;
    }
}

void Hovership::disableControls() {
    if (this->controls) {
        delete this->controls;
        this->controls = nullptr;
    }
}

bool Hovership::getControlsEnabled() {
    return !!this->controls;
}

Hovership::~Hovership() {
    this->disableControls();
}
