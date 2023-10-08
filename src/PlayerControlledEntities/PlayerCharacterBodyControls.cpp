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

    auto navigationAgent = this->model->get_node<godot::NavigationAgent3D>("NavigationAgent3D");
    auto animationPlayer = this->model->get_node<godot::AnimationPlayer>("Witch/AnimationPlayer");

    if (this->isLastMouseClickPositionValid) {
        this->isLastMouseClickPositionValid = false;
        auto spaceState = this->model->get_world_3d()->get_direct_space_state();
        if (spaceState != nullptr) {

            auto camera = this->model->get_viewport()->get_camera_3d();
            auto rayStart = camera->project_ray_origin(this->lastMouseClickPosition);
            auto rayEnd = rayStart + camera->project_ray_normal(this->lastMouseClickPosition) * 1000.0f;

            auto query = godot::PhysicsRayQueryParameters3D::create(rayStart, rayEnd);
            query->set_collide_with_areas(true);

            godot::Dictionary result = spaceState->intersect_ray(query);

            if (!result.is_empty()) {
                spdlog::info("raycast");
                spdlog::info(((godot::Vector3)result["position"]).x);
                spdlog::info(((godot::Vector3)result["position"]).y);
                spdlog::info(((godot::Vector3)result["position"]).z);

                navigationAgent->set_target_position((godot::Vector3)result["position"]);

                animationPlayer->play("CharacterArmature|Run");
            }
        }
    }

    if (!navigationAgent->is_navigation_finished()) {
        auto nextPosition = navigationAgent->get_next_path_position();
        auto currentAgentPosition = this->model->get_global_position();
        auto velocity = (nextPosition - currentAgentPosition).normalized() * 10.0f;
        this->model->set_velocity(velocity);
        this->model->move_and_slide();
    }
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
        // this->model->rotate_y( -mouseMotionEvent->get_relative().x * mouseSensitivity );

        auto head = this->model->get_node<godot::Node3D>("CameraContainer");

        if (head) {
            // head->rotate_x( -mouseMotionEvent->get_relative().y * mouseSensitivity );
            head->rotate_y( -mouseMotionEvent->get_relative().x * mouseSensitivity );
            /*auto headRotation = head->get_rotation();
            headRotation.y = godot::CLAMP(headRotation.y, -1.2f, 1.2f);
            head->set_rotation(headRotation);*/
        }
    }

    godot::Ref<godot::InputEventMouseButton> mouseButtonEvent = event;

    if (mouseButtonEvent.is_valid() && mouseButtonEvent->get_button_index() == godot::MouseButton::MOUSE_BUTTON_LEFT) {
        this->lastMouseClickPosition = mouseButtonEvent->get_position();
        this->isLastMouseClickPositionValid = true;
    }



    auto cameraSpringArm = this->model->get_node<godot::SpringArm3D>("CameraContainer/SpringArm3D");

    if (cameraSpringArm != nullptr) {

        double length = cameraSpringArm->get_length();

        if (this->input->is_action_pressed(Actions::UI_SCROLL_ZOOM_IN)) {
            length -= 0.1;
        }

        if (this->input->is_action_pressed(Actions::UI_SCROLL_ZOOM_OUT)) {
            length += 0.1;
        }

        cameraSpringArm->set_length(godot::CLAMP(length, -2.0f, 5.0f));

    }



    /*const int mass = 1;

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


    this->model->set_velocity(velocity);*/
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
