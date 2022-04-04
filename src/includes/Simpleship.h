#ifndef APP_SIMPLESHIP_H
#define APP_SIMPLESHIP_H

#include "vendor/Godot.h"

#include <spdlog/spdlog.h>

namespace app {

class SimpleshipControls;

class Simpleship : public godot::RigidDynamicBody3D {
    GDCLASS(Simpleship, godot::RigidDynamicBody3D);

protected:
    static void _bind_methods();

public:

    SimpleshipControls* controls;
    

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

    godot::Camera3D* getThirdPersonCamera();
};

}

#include "./SimpleshipControls.h"

#endif