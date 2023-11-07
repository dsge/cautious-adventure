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
    godot::ClassDB::bind_method(godot::D_METHOD("on_agent_navigation_finished"), &PlayerCharacterBody::on_agent_navigation_finished);
}

PlayerCharacterBody::PlayerCharacterBody() {
}

void PlayerCharacterBody::_enter_tree() {
    if (this->controls) {
        this->controls->model_enter_tree();
    }
    this->get_node<godot::NavigationAgent3D>("NavigationAgent3D")->connect("navigation_finished", godot::Callable(this, "on_agent_navigation_finished"));
}

void PlayerCharacterBody::_ready() {
    if (this->controls) {
        this->controls->model_ready();
    }
}

void PlayerCharacterBody::on_agent_navigation_finished() {
    if (this->controls) {
        this->controls->model_on_agent_navigation_finished();
    }
}

void PlayerCharacterBody::_process(double delta) {
    if (this->controls) {
        this->controls->model_process(delta);
    }
}

void PlayerCharacterBody::_physics_process(double delta) {
    if (this->controls) {
        this->controls->model_physics_process(delta);
    }
}
/*void PlayerCharacterBody::_input(const godot::Ref<godot::InputEvent> &event) {
    if (this->controls) {
        // this->controls->model_input(event);
    }
}*/
void PlayerCharacterBody::_unhandled_input(const godot::Ref<godot::InputEvent> &event) {
    if (this->controls) {
        this->controls->model_unhandled_input(event);
    }
}
void PlayerCharacterBody::_unhandled_key_input(const godot::Ref<godot::InputEvent> &event) {
    if (this->controls) {
        this->controls->model_unhandled_key_input(event);
    }
}

godot::Camera3D* PlayerCharacterBody::getThirdPersonCamera() {
    return this->get_node<godot::Camera3D>("CameraContainer/SpringArm3D/Camera3D");
}

godot::Camera3D* PlayerCharacterBody::getFirstPersonCamera() {
    return this->get_node<godot::Camera3D>("CameraContainer/SpringArm3D/Camera3D");
}

bool PlayerCharacterBody::useFirstPersonCameraByDefault() {
    return false;
}

void PlayerCharacterBody::enableControls() {
    if (!this->controls) {
        this->controls = new PlayerCharacterBodyControls();
        this->controls->model = this;

        if (this->get_tree() != nullptr) {
            this->controls->model_enter_tree();
            this->controls->model_ready();
        }
    }
}

void PlayerCharacterBody::disableControls() {
    if (this->controls) {
        delete this->controls;
        this->controls = nullptr;
    }
}

bool PlayerCharacterBody::getControlsEnabled() {
    return !!this->controls;
}

double PlayerCharacterBody::getAttackRange() {
    return 3.0;
}

PlayerCharacterBody::~PlayerCharacterBody() {
    this->disableControls();
}
