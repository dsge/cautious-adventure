#pragma once

#include "../vendor/Godot.h"

#include <spdlog/spdlog.h>

namespace app {

class GlobalHealthBar : public godot::Control {
    GDCLASS(GlobalHealthBar, godot::Control);

public:
    static void _bind_methods();
    GlobalHealthBar();
    ~GlobalHealthBar();
    void _enter_tree() override;

    void _ready() override;
    void _process(double delta) override;
};

}
