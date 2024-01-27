#ifndef APP_PLAYERCHARACTERBODYCONTROLS_H
#define APP_PLAYERCHARACTERBODYCONTROLS_H

#include "../vendor/Godot.h"

#include "../enums/InputActions.h"
#include "./PlayerCharacterBody.h"
#include "../enums/PlayerCharacterAnimations.h"
#include <Hypodermic/Hypodermic.h>
#include "../SceneSwitcher.h"
#include "../helper-functions.h"
#include "../Startup.h"
#include "../SceneSwitcher.h"
#include "../Enemies/SimpleMeleeEnemy.h"
#include "./MouseTarget.h"
#include <bitset>

#include <spdlog/spdlog.h>

namespace app {

struct PlayerCharacterBodyControls {
    PlayerCharacterBody* model = NULL;

    godot::Ref<godot::PackedScene> goblinPrototype = NULL;
    godot::Ref<godot::PackedScene> demonPrototype = NULL;
    godot::Node3D* enemySpawnLocation = NULL;
    std::shared_ptr<Hypodermic::Container> container = NULL;

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
    MouseTarget mouseTarget;
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
