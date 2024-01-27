#pragma once

#include "../vendor/Godot.h"
#include "../interfaces/DestructibleInterface.h"

#include <spdlog/spdlog.h>

namespace app {

class GlobalHealthBar : public godot::Control {
    GDCLASS(GlobalHealthBar, godot::Control);

public:
    static constexpr char SIGNAL_UPDATE_DESTRUCTIBLE_OBJECT[] = "update_destructible_object";
    static void _bind_methods();
    GlobalHealthBar();
    ~GlobalHealthBar();
    void _enter_tree() override;

    void _ready() override;
    void _process(double delta) override;

protected:
    void onUpdateDestructibleObject(godot::Variant targetObject);

};

}
