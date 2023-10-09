#ifndef APP_PLAYERCHARACTERBODYCONTROLS_H
#define APP_PLAYERCHARACTERBODYCONTROLS_H

#include "../vendor/Godot.h"

#include "../Actions.h"
#include "./PlayerCharacterBody.h"
#include "./PlayerCharacterAnimations.h"
#include <bitset>

#include <spdlog/spdlog.h>

namespace app {

class PlayerCharacterBodyControls {

public:
    PlayerCharacterBody* model = NULL;
    godot::String currentAnimation = PlayerCharacterAnimation::IDLE;

    PlayerCharacterBodyControls();
    ~PlayerCharacterBodyControls();

    void model_enter_tree();
    void model_ready();
    void model_process(float delta);
    void model_physics_process(float delta);
	void model_input(const godot::Ref<godot::InputEvent> &event);
	void model_unhandled_input(const godot::Ref<godot::InputEvent> &event);
	void model_unhandled_key_input(const godot::Ref<godot::InputEvent> &event);
    void model_on_agent_navigation_finished();

protected:
    /**
     * until `this->input->get_mouse_mode() != godot::Input::MOUSE_MODE_CAPTURED` actually works
     */
    bool mouseCaptured = false;
    /**
     * for communicating between `model_unhandled_key_input()` and `model_physics_process()`
     */
    bool isLastMouseClickPositionValid = false;
    godot::Vector2 lastMouseClickPosition = godot::Vector2();
    /**
     * godot nodes used internally
     */
    godot::Input* input = NULL;
    godot::Node3D* cameraContainer = NULL;
    godot::SpringArm3D* cameraSpringArm = NULL;
    godot::NavigationAgent3D* navigationAgent = NULL;
    godot::AnimationPlayer* animationPlayer = NULL;
    godot::Node3D* body = NULL;

    void animate(godot::String animationName);
};

}


#endif
