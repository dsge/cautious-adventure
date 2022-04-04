#include "includes/SimpleshipControls.h"

using namespace app;

SimpleshipControls::SimpleshipControls() {

}

void SimpleshipControls::model_enter_tree() {

}

void SimpleshipControls::model_ready() {
    spdlog::info("SimpleshipControls::model_ready");

    auto model = this->model;

    godot::Camera3D* camera = model->getThirdPersonCamera();

    camera->make_current();
}

void SimpleshipControls::model_process(float delta) {
    
}



void SimpleshipControls::model_physics_process(float delta) {

}
void SimpleshipControls::model_input(const godot::Ref<godot::InputEvent> &event) {

}
void SimpleshipControls::model_unhandled_input(const godot::Ref<godot::InputEvent> &event) {

}
void SimpleshipControls::model_unhandled_key_input(const godot::Ref<godot::InputEvent> &event) {

    spdlog::info("SimpleshipControls::model_unhandled_key_input");

    godot::Ref<godot::InputEventKey> k = event;

	if (k.is_valid() && k->get_unicode() && k->is_pressed()) {
        // spdlog::info(k->get_unicode());
    }

    if (event->is_action_pressed(Actions::UI_FORWARD)) {
        spdlog::info("FORWARDDDD");
    }
    if (event->is_action_pressed(Actions::UI_BACKWARDS)) {
        spdlog::info("BACKWARDS");
    }
    if (event->is_action_pressed(Actions::UI_LEFT)) {
        spdlog::info("LEFT");
    }
    if (event->is_action_pressed(Actions::UI_RIGHT)) {
        spdlog::info("RIGHT");
    }
}

SimpleshipControls::~SimpleshipControls() {
    
}