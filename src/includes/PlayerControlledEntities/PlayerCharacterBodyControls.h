#ifndef APP_PLAYERCHARACTERBODYCONTROLS_H
#define APP_PLAYERCHARACTERBODYCONTROLS_H

#include "../vendor/Godot.h"

#include "../Actions.h"
#include "./PlayerCharacterBody.h"

#include <spdlog/spdlog.h>

namespace app {

class PlayerCharacterBodyControls {

public:
    godot::Input* input = NULL;
    PlayerCharacterBody* model = NULL;
    /**
     * until `this->input->get_mouse_mode() != godot::Input::MOUSE_MODE_CAPTURED` actually works
     */
    bool mouseCaptured = false;

    PlayerCharacterBodyControls();
    ~PlayerCharacterBodyControls();


    void model_enter_tree();
    void model_ready();
    void model_process(float delta);
    void model_physics_process(float delta);
	void model_input(const godot::Ref<godot::InputEvent> &event);
	void model_unhandled_input(const godot::Ref<godot::InputEvent> &event);
	void model_unhandled_key_input(const godot::Ref<godot::InputEvent> &event);

};

}


#endif
