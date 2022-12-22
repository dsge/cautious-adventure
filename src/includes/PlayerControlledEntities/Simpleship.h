#ifndef APP_SIMPLESHIP_H
#define APP_SIMPLESHIP_H

#include "../vendor/Godot.h"

#include "../interfaces/PlayerControlledEntityInterface.h"

#include <spdlog/spdlog.h>

namespace app {

class SimpleshipControls;

class Simpleship : public godot::RigidBody3D, public PlayerControlledEntityInterface {
    GDCLASS(Simpleship, godot::RigidBody3D);

protected:
    static void _bind_methods();

public:

    SimpleshipControls* controls = nullptr;


    Simpleship();
    ~Simpleship();
    void _enter_tree() override;
    // virtual void _notification(int64_t what) override;

    void _ready() override;
    void _process(double delta) override;
    void _physics_process(double delta) override;
	/*void _input(const godot::Ref<godot::InputEvent> &event) override;
	void _unhandled_input(const godot::Ref<godot::InputEvent> &event) override;*/
	void _unhandled_key_input(const godot::Ref<godot::InputEvent> &event) override;

    godot::Camera3D* getThirdPersonCamera() override;
    godot::Camera3D* getFirstPersonCamera() override;
    bool useFirstPersonCameraByDefault() override;
    void enableControls() override;
    void disableControls() override;
    bool getControlsEnabled() override;
};

}

#include "./SimpleshipControls.h"

#endif
