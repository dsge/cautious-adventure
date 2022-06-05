#include "includes/PlayerControlledEntityHandler.h"

using namespace app;

void PlayerControlledEntityHandler::_bind_methods() {
    godot::ClassDB::bind_method(godot::D_METHOD("ready"), &PlayerControlledEntityHandler::_ready);
    godot::ClassDB::bind_method(godot::D_METHOD("process"), &PlayerControlledEntityHandler::_process);
}

PlayerControlledEntityHandler::PlayerControlledEntityHandler() {
    spdlog::info("PlayerControlledEntityHandler::contructor");
}


void PlayerControlledEntityHandler::_ready() {
    spdlog::info("PlayerControlledEntityHandler::_ready");
}

void PlayerControlledEntityHandler::_process(float delta) {
    // spdlog::info("PlayerControlledEntityHandler::_process");
}

void PlayerControlledEntityHandler::setModel(godot::Node3D* value) {

    this->model = value;

    Simpleship *model = godot::Object::cast_to<Simpleship>(value);
    if (model) {
        godot::Camera3D* camera;
        if (model->useFirstPersonCameraByDefault()) {
            camera = model->getFirstPersonCamera();
        } else {
            camera = model->getThirdPersonCamera();
        }
        camera->make_current();
    }


}

godot::Node3D* PlayerControlledEntityHandler::getModel() {
    return this->model;
}

PlayerControlledEntityHandler::~PlayerControlledEntityHandler() {
    spdlog::info("PlayerControlledEntityHandler::destructor");
}
