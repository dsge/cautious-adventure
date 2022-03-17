#include "includes/PlayerControlledEntityHandler.h"

using namespace app;

void PlayerControlledEntityHandler::_bind_methods() {
    ClassDB::bind_method(D_METHOD("ready"), &PlayerControlledEntityHandler::_ready);
    ClassDB::bind_method(D_METHOD("process"), &PlayerControlledEntityHandler::_process);
}

PlayerControlledEntityHandler::PlayerControlledEntityHandler() {
    spdlog::info("PlayerControlledEntityHandler::contructor");
}


void PlayerControlledEntityHandler::_ready() {
    spdlog::info("PlayerControlledEntityHandler::_ready");
}

void PlayerControlledEntityHandler::_process(float delta) {
      spdlog::info("PlayerControlledEntityHandler::_process");
}

PlayerControlledEntityHandler::~PlayerControlledEntityHandler() {
    spdlog::info("PlayerControlledEntityHandler::destructor");
}