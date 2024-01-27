#include "../includes/PlayerControlledEntities/PlayerControlledEntityHandler.h"

using namespace app;

void PlayerControlledEntityHandler::_bind_methods() {
    godot::ClassDB::bind_method(godot::D_METHOD("ready"), &PlayerControlledEntityHandler::_ready);
    godot::ClassDB::bind_method(godot::D_METHOD("process"), &PlayerControlledEntityHandler::_process);
}

PlayerControlledEntityHandler::PlayerControlledEntityHandler() {
}


void PlayerControlledEntityHandler::_ready() {
}

void PlayerControlledEntityHandler::_process(float delta) {
    // spdlog::info("PlayerControlledEntityHandler::_process");
}

void PlayerControlledEntityHandler::setModel(PlayerControlledEntityInterface* value) {

    this->model = value;

    if (value) {
        godot::Camera3D* camera;
        if (model->useFirstPersonCameraByDefault()) {
            camera = model->getFirstPersonCamera();
        } else {
            camera = model->getThirdPersonCamera();
        }
        camera->make_current();

        value->enableControls();
    }


}

PlayerControlledEntityInterface* PlayerControlledEntityHandler::getModel() {
    return this->model;
}

PlayerControlledEntityHandler::~PlayerControlledEntityHandler() {
}
