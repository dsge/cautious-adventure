#ifndef APP_SIMPLESHIPCONTROLS_H
#define APP_SIMPLESHIPCONTROLS_H

#include "../vendor/Godot.h"

#include "../Actions.h"
#include "./Simpleship.h"

#include <spdlog/spdlog.h>

namespace app {

class SimpleshipControls {

public:

    Simpleship* model = NULL;

    SimpleshipControls();
    ~SimpleshipControls();


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
