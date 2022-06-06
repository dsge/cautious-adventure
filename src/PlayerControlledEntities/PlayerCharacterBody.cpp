#include "../includes/PlayerControlledEntities/PlayerCharacterBody.h"

using namespace app;

void PlayerCharacterBody::_bind_methods() {
    godot::ClassDB::bind_method(godot::D_METHOD("ready"), &PlayerCharacterBody::_ready);
    godot::ClassDB::bind_method(godot::D_METHOD("process"), &PlayerCharacterBody::_process);
    godot::ClassDB::bind_method(godot::D_METHOD("enter_tree"), &PlayerCharacterBody::_enter_tree);
    godot::ClassDB::bind_method(godot::D_METHOD("physics_process"), &PlayerCharacterBody::_physics_process);
    /*godot::ClassDB::bind_method(godot::D_METHOD("input"), &PlayerCharacterBody::_input);
    godot::ClassDB::bind_method(godot::D_METHOD("unhandled_input"), &PlayerCharacterBody::_unhandled_input);*/
    godot::ClassDB::bind_method(godot::D_METHOD("unhandled_key_input"), &PlayerCharacterBody::_unhandled_key_input);
}

PlayerCharacterBody::PlayerCharacterBody() {

}

void PlayerCharacterBody::_enter_tree() {

}

void PlayerCharacterBody::_ready() {

}

void PlayerCharacterBody::_process(double delta) {

}

void PlayerCharacterBody::_physics_process(double delta) {

}
/*void PlayerCharacterBody::_input(const godot::Ref<godot::InputEvent> &event) {
    if (this->controls) {
        // this->controls->model_input(event);
    }
}
void PlayerCharacterBody::_unhandled_input(const godot::Ref<godot::InputEvent> &event) {
    if (this->controls) {
        // this->controls->model_unhandled_input(event);
    }
}*/
void PlayerCharacterBody::_unhandled_key_input(const godot::Ref<godot::InputEvent> &event) {

}

godot::Camera3D* PlayerCharacterBody::getThirdPersonCamera() {
    return this->get_node<godot::Camera3D>("Head/Camera3D");
}

godot::Camera3D* PlayerCharacterBody::getFirstPersonCamera() {
    return this->get_node<godot::Camera3D>("Head/Camera3D");
}

bool PlayerCharacterBody::useFirstPersonCameraByDefault() {
    return false;
}

PlayerCharacterBody::~PlayerCharacterBody() {

}
