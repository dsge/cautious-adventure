#include "../includes/PlayerControlledEntities/PlayerCharacterBodyControls.h"

using namespace app;

PlayerCharacterBodyControls::PlayerCharacterBodyControls() {

}

void PlayerCharacterBodyControls::model_enter_tree() {
    /*auto material = godot::Ref(memnew(godot::PhysicsMaterial));
    material->set_bounce(0.0);
    material->set_absorbent(true);
    this->model->set_physics_material_override(material);

    this->model->set_use_continuous_collision_detection(true);
    this->model->set_mass(20.0);*/
}

void PlayerCharacterBodyControls::model_ready() {
    spdlog::info("PlayerCharacterBodyControls::model_ready");

    auto model = this->model;
}

void PlayerCharacterBodyControls::model_process(float delta) {

}



void PlayerCharacterBodyControls::model_physics_process(float delta) {

}
void PlayerCharacterBodyControls::model_input(const godot::Ref<godot::InputEvent> &event) {

}
void PlayerCharacterBodyControls::model_unhandled_input(const godot::Ref<godot::InputEvent> &event) {

}
void PlayerCharacterBodyControls::model_unhandled_key_input(const godot::Ref<godot::InputEvent> &event) {

    // spdlog::info("PlayerCharacterBodyControls::model_unhandled_key_input");

    /*godot::Ref<godot::InputEventKey> k = event;

	if (k.is_valid() && k->get_unicode() && k->is_pressed()) {
        // spdlog::info(k->get_unicode());
    }*/

    const int mass = 20;

    const int speed = 15 * mass;

    if (event->is_action_pressed(Actions::UI_ASCEND)) {
        // this->model->add_constant_central_force(godot::Vector3(0, speed, 0));
    } else if (event->is_action_released(Actions::UI_ASCEND)) {
        // this->model->set_constant_force(godot::Vector3(0, 0, 0));
    }

    if (event->is_action_pressed(Actions::UI_DESCEND)) {
        // this->model->add_constant_central_force(godot::Vector3(0, -speed, 0));
    } else if (event->is_action_released(Actions::UI_DESCEND)) {
        // this->model->set_constant_force(godot::Vector3(0, 0, 0));
    }

    if (event->is_action_pressed(Actions::UI_FORWARD)) {
        // this->model->add_constant_central_force(this->model->get_global_transform().basis.get_axis(2).normalized() * -speed);
    } else if (event->is_action_released(Actions::UI_FORWARD)) {
        // this->model->set_constant_force(godot::Vector3(0, 0, 0));
    }

    if (event->is_action_pressed(Actions::UI_BACKWARDS)) {
        // this->model->add_constant_central_force(godot::Vector3(-speed, 0, 0));
    } else if (event->is_action_released(Actions::UI_BACKWARDS)) {
        // this->model->set_constant_force(godot::Vector3(0, 0, 0));
    }

    if (event->is_action_pressed(Actions::UI_LEFT)) {
        // this->model->add_constant_torque(godot::Vector3(0, 50 * mass, 0));
    } else if (event->is_action_released(Actions::UI_LEFT)) {
        // this->model->set_constant_torque(godot::Vector3(0, 0, 0));
    }

    if (event->is_action_pressed(Actions::UI_RIGHT)) {
        // this->model->add_constant_torque(godot::Vector3(0, -50 * mass, 0));
    } else if (event->is_action_released(Actions::UI_RIGHT)) {
        // this->model->set_constant_torque(godot::Vector3(0, 0, 0));
    }
}

PlayerCharacterBodyControls::~PlayerCharacterBodyControls() {

}
