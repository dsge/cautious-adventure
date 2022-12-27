#include "../includes/PlayerControlledEntities/PlayerCharacterBodyControls.h"

using namespace app;

PlayerCharacterBodyControls::PlayerCharacterBodyControls() {
    this->input = godot::Input::get_singleton();
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
    auto model = this->model;
}

void PlayerCharacterBodyControls::model_process(float delta) {

}



void PlayerCharacterBodyControls::model_physics_process(float delta) {
    this->model->move_and_slide();
}
void PlayerCharacterBodyControls::model_input(const godot::Ref<godot::InputEvent> &event) {

}
void PlayerCharacterBodyControls::model_unhandled_input(const godot::Ref<godot::InputEvent> &event) {
    /*godot::Ref<godot::InputEventMouseMotion> k = event;
    if (k.is_valid() && this->input && this->input->get_mouse_mode() == godot::Input::MOUSE_MODE_CAPTURED) {

    }*/

    // this->model->get_node<godot::Camera3D>("Head");

    godot::Ref<godot::InputEventMouseMotion> mouseMotionEvent = event;

    /**
     * radians/pixel
     */
    float mouseSensitivity = 0.002f;

	if (mouseMotionEvent.is_valid() && /*this->input->get_mouse_mode() == godot::Input::MOUSE_MODE_CAPTURED*/ this->mouseCaptured) {
        // -event.relative.x * mouse_sensitivity
        this->model->rotate_y( -mouseMotionEvent->get_relative().x * mouseSensitivity );

        auto head = this->model->get_node<godot::Node3D>("Head");

        if (head) {
            head->rotate_x( -mouseMotionEvent->get_relative().y * mouseSensitivity );
            auto headRotation = head->get_rotation();
            headRotation.x = CLAMP(headRotation.x, -1.2f, 1.2f);
            head->set_rotation(headRotation);
        }
    }



    const int mass = 1;

    const int speed = 6 * mass;

    auto direction = godot::Vector3();

    // event->is_action_pressed(Actions::UI_FORWARD)
    // event->is_action_released(Actions::UI_FORWARD)

    if (this->input->is_action_pressed(Actions::UI_FORWARD)) {
        if (!this->input->is_action_just_released(Actions::UI_FORWARD)) {
            direction += -this->model->get_global_transform().basis.get_column(2).normalized();
        }
    }

    if (this->input->is_action_pressed(Actions::UI_BACKWARDS)) {
        if (!this->input->is_action_just_released(Actions::UI_BACKWARDS)) {
            direction += this->model->get_global_transform().basis.get_column(2).normalized();
        }
    }

    if (this->input->is_action_pressed(Actions::UI_LEFT)) {
        if (!this->input->is_action_just_released(Actions::UI_LEFT)) {
            direction += -this->model->get_global_transform().basis.get_column(0).normalized();
        }
    }

    if (this->input->is_action_pressed(Actions::UI_RIGHT)) {
        if (!this->input->is_action_just_released(Actions::UI_RIGHT)) {
            direction += this->model->get_global_transform().basis.get_column(0).normalized();
        }
    }

    auto velocity = direction * speed;


    this->model->set_velocity(velocity);
}
void PlayerCharacterBodyControls::model_unhandled_key_input(const godot::Ref<godot::InputEvent> &event) {

    // spdlog::info("PlayerCharacterBodyControls::model_unhandled_key_input");

    /*godot::Ref<godot::InputEventKey> k = event;

	if (k.is_valid() && k->get_unicode() && k->is_pressed()) {
        spdlog::info(k->get_unicode());
    }*/

    if (event->is_action_pressed(Actions::UI_TOGGLE_MOUSE_CAPTURE) && this->input) {
        if (/*this->input->get_mouse_mode() != godot::Input::MOUSE_MODE_CAPTURED*/ !this->mouseCaptured) {
            this->input->set_mouse_mode(godot::Input::MOUSE_MODE_CAPTURED);
            this->mouseCaptured = true;
        } else {
            this->input->set_mouse_mode(godot::Input::MOUSE_MODE_VISIBLE);
            this->mouseCaptured = false;
        }

    }


}

PlayerCharacterBodyControls::~PlayerCharacterBodyControls() {

}
