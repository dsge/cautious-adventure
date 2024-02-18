#include "../includes/PlayerControlledEntities/PlayerCharacterBodyControls.h"

using namespace app;

PlayerCharacterBodyControls::PlayerCharacterBodyControls() {
    this->input = godot::Input::get_singleton();

    auto resourceLoader = godot::ResourceLoader::get_singleton();

    this->goblinPrototype = resourceLoader->load("res://models/goblin/goblin.tscn", "PackedScene");
    this->demonPrototype = resourceLoader->load("res://models/demon/demon.tscn", "PackedScene");
}

void PlayerCharacterBodyControls::model_enter_tree() {
    this->cameraContainer = this->model->get_node<godot::Node3D>("CameraContainer");
    this->cameraSpringArm = this->model->get_node<godot::SpringArm3D>("CameraContainer/SpringArm3D");
    this->navigationAgent = this->model->get_node<godot::NavigationAgent3D>("NavigationAgent3D");
    // this->animationPlayer = this->model->get_node<godot::AnimationPlayer>("Body/Witch/AnimationPlayer");
    this->body = this->model->get_node<godot::Node3D>("Body");

    this->enemySpawnLocation = this->model->get_node<godot::Node3D>("../EnemySpawner");

    // this->container = Startup::containerInstance;

}

void PlayerCharacterBodyControls::model_ready() {
}



void PlayerCharacterBodyControls::model_on_agent_navigation_finished() {
    this->animate(PlayerCharacterAnimation::IDLE);
}

void PlayerCharacterBodyControls::animate(godot::String animationName) {
    if (this->currentAnimation != animationName) {
        this->currentAnimation = animationName;
        if (this->animationPlayer) {
            this->animationPlayer->play(this->currentAnimation);
        }
    }
}

void PlayerCharacterBodyControls::model_process(float delta) {
    if (this->input->is_action_pressed(InputActions::UI_MOUSE_PRIMARY)) {
        this->mouseTarget.lastMouseClickPosition = this->model->get_viewport()->get_mouse_position();;
        this->mouseTarget.isLastMouseClickPositionValid = true;
    }
}



void PlayerCharacterBodyControls::model_physics_process(float delta) {
    auto navigationAgent = this->navigationAgent;
    auto animationPlayer = this->animationPlayer;

    if (this->mouseTarget.isLastMouseClickPositionValid) {
        this->mouseTarget.isLastMouseClickPositionValid = false;
        auto spaceState = this->model->get_world_3d()->get_direct_space_state();
        if (spaceState != nullptr) {

            auto camera = this->model->get_viewport()->get_camera_3d();
            auto rayStart = camera->project_ray_origin(this->mouseTarget.lastMouseClickPosition);
            auto rayEnd = rayStart + camera->project_ray_normal(this->mouseTarget.lastMouseClickPosition) * 1000.0f;

            std::bitset<sizeof(uint32_t)> collisionMask;
            collisionMask.set();
            collisionMask.set(1, false);

            auto query = godot::PhysicsRayQueryParameters3D::create(rayStart, rayEnd, collisionMask.to_ulong());
            // query->set_collide_with_areas(true);

            /**
             * The `result` dictionary when a collision occurs contains the following data:
             * ```js
             * {
             *   position: Vector3 # point in world space for collision
             *   normal: Vector3 # normal in world space for collision
             *   collider: Object # Object collided or null (if unassociated)
             *   collider_id: ObjectID # Object it collided against
             *   rid: RID # RID it collided against
             *   shape: int # shape index of collider
             *   metadata: Variant() # metadata of collider
             * }
             * ```
             */
            godot::Dictionary result = spaceState->intersect_ray(query);

            if (!result.is_empty()) {
                auto foo = result["collider"];
                auto simpleMeleeEnemy = godot::Object::cast_to<SimpleMeleeEnemy>(foo);
                godot::Vector3 position;
                if (simpleMeleeEnemy) {
                    spdlog::info("collided with simplemeleeenemy");
                    position = simpleMeleeEnemy->get_position();
                } else {
                    /**
                     * ground
                     */
                    position = (godot::Vector3)result["position"];
                }
                navigationAgent->set_target_position(position);
                this->animate(PlayerCharacterAnimation::RUN);
            }
        }
    }

    if (!navigationAgent->is_navigation_finished()) {
        auto nextPosition = navigationAgent->get_next_path_position();
        auto currentAgentPosition = this->model->get_global_position();
        auto velocity = (nextPosition - currentAgentPosition).normalized() * 4.0f;
        this->model->set_velocity(velocity);
        this->model->move_and_slide();

        this->body->look_at(nextPosition);
    }
}
void PlayerCharacterBodyControls::model_input(const godot::Ref<godot::InputEvent> &event) {

}

void PlayerCharacterBodyControls::model_unhandled_input(const godot::Ref<godot::InputEvent> &event) {
    /**
     * radians/pixel
     */
    float mouseSensitivity = 0.002f;

    godot::Ref<godot::InputEventMouseMotion> mouseMotionEvent = event;
	if (mouseMotionEvent.is_valid() && /*this->input->get_mouse_mode() == godot::Input::MOUSE_MODE_CAPTURED*/ this->mouseCaptured) {
        if (this->cameraContainer) {
            this->cameraContainer->rotate_y( -mouseMotionEvent->get_relative().x * mouseSensitivity );
        }
    }

    auto cameraSpringArm = this->cameraSpringArm;

    if (cameraSpringArm != nullptr) {

        double length = cameraSpringArm->get_length();

        if (this->input->is_action_pressed(InputActions::UI_SCROLL_ZOOM_IN)) {
            length -= 0.1;
        }

        if (this->input->is_action_pressed(InputActions::UI_SCROLL_ZOOM_OUT)) {
            length += 0.1;
        }

        cameraSpringArm->set_length(godot::CLAMP(length, -2.0f, 5.0f));

    }

}
void PlayerCharacterBodyControls::model_unhandled_key_input(const godot::Ref<godot::InputEvent> &event) {

    // spdlog::info("PlayerCharacterBodyControls::model_unhandled_key_input");

    /*godot::Ref<godot::InputEventKey> k = event;

	if (k.is_valid() && k->get_unicode() && k->is_pressed()) {
        spdlog::info(k->get_unicode());
    }*/

    if (event->is_action_pressed(InputActions::UI_TOGGLE_MOUSE_CAPTURE) && this->input) {
        if (/*this->input->get_mouse_mode() != godot::Input::MOUSE_MODE_CAPTURED*/ !this->mouseCaptured) {
            this->input->set_mouse_mode(godot::Input::MOUSE_MODE_CAPTURED);
            this->mouseCaptured = true;
        } else {
            this->input->set_mouse_mode(godot::Input::MOUSE_MODE_VISIBLE);
            this->mouseCaptured = false;
        }

    }

    /* if (event->is_action_pressed(InputActions::UI_ASCEND) && this->container) {
        auto sceneContainer = this->container->resolve<SceneSwitcher>()->getSceneContainer();
        godot::Node3D* enemyInstance = app::call_cast_to<godot::Node3D>(this->goblinPrototype->instantiate());
        enemyInstance->set_position(this->enemySpawnLocation->get_position());
        sceneContainer->add_child(enemyInstance);
    } */


}

PlayerCharacterBodyControls::~PlayerCharacterBodyControls() {

}
