#include "../includes/PlayerControlledEntities/HovershipControls.h"

using namespace app;

HovershipControls::HovershipControls() {

}

void HovershipControls::model_enter_tree() {
    auto material = godot::Ref(memnew(godot::PhysicsMaterial));
    material->set_bounce(0.0);
    material->set_absorbent(true);
    this->model->set_physics_material_override(material);

    this->model->set_use_continuous_collision_detection(true);
    this->model->set_mass(1.0);

    godot::AABB boundingBox = this->model->getBoundingBox();
    this->model->set_mass(1.0);

}

void HovershipControls::model_ready() {
    auto model = this->model;

    /*godot::Camera3D* camera = model->getThirdPersonCamera();

    camera->make_current();*/
}

void HovershipControls::model_process(float delta) {

}



void HovershipControls::model_physics_process(float delta) {

}
void HovershipControls::model_input(const godot::Ref<godot::InputEvent> &event) {

}
void HovershipControls::model_unhandled_input(const godot::Ref<godot::InputEvent> &event) {

}
void HovershipControls::model_unhandled_key_input(const godot::Ref<godot::InputEvent> &event) {

    // spdlog::info("HovershipControls::model_unhandled_key_input");

    /*godot::Ref<godot::InputEventKey> k = event;

	if (k.is_valid() && k->get_unicode() && k->is_pressed()) {
        // spdlog::info(k->get_unicode());
    }*/

    const int mass = 1;

    const int speed = 15 * mass;

    if (event->is_action_pressed(Actions::UI_ASCEND)) {
        this->model->add_constant_central_force(godot::Vector3(0, speed, 0));
    } else if (event->is_action_released(Actions::UI_ASCEND)) {
        this->model->set_constant_force(godot::Vector3(0, 0, 0));
    }

    if (event->is_action_pressed(Actions::UI_DESCEND)) {
        this->model->add_constant_central_force(godot::Vector3(0, -speed, 0));
    } else if (event->is_action_released(Actions::UI_DESCEND)) {
        this->model->set_constant_force(godot::Vector3(0, 0, 0));
    }

    if (event->is_action_pressed(Actions::UI_FORWARD)) {
        this->model->add_constant_central_force(this->model->get_global_transform().basis.get_column(2).normalized() * -speed);
    } else if (event->is_action_released(Actions::UI_FORWARD)) {
        this->model->set_constant_force(godot::Vector3(0, 0, 0));
    }

    if (event->is_action_pressed(Actions::UI_BACKWARDS)) {
        this->model->add_constant_central_force(godot::Vector3(-speed, 0, 0));
    } else if (event->is_action_released(Actions::UI_BACKWARDS)) {
        this->model->set_constant_force(godot::Vector3(0, 0, 0));
    }

    if (event->is_action_pressed(Actions::UI_LEFT)) {
        this->model->add_constant_torque(godot::Vector3(0, 50 * mass, 0));
    } else if (event->is_action_released(Actions::UI_LEFT)) {
        this->model->set_constant_torque(godot::Vector3(0, 0, 0));
    }

    if (event->is_action_pressed(Actions::UI_RIGHT)) {
        this->model->add_constant_torque(godot::Vector3(0, -50 * mass, 0));
    } else if (event->is_action_released(Actions::UI_RIGHT)) {
        this->model->set_constant_torque(godot::Vector3(0, 0, 0));
    }
}

HovershipControls::~HovershipControls() {

}
