#pragma once

#include "vendor/Godot.h"
#include "./helper-functions.h"
#include "./Startup.h"
#include "./DaynightCycleManager.h"

#include <spdlog/spdlog.h>

namespace app {

class DaynightCycleInfo : public godot::MarginContainer {
    GDCLASS(DaynightCycleInfo, godot::MarginContainer);

protected:
    godot::Input* input = nullptr;
    godot::Label* infoLabel = nullptr;
    std::shared_ptr< app::DaynightCycleManager > daynightCycleManager;

    static void _bind_methods();

public:


    DaynightCycleInfo();
    ~DaynightCycleInfo();
    void _enter_tree() override;
    // virtual void _notification(int64_t what) override;

    void _ready() override;

    void _process(float delta);
	void _unhandled_key_input(const godot::Ref<godot::InputEvent> &event) override;
};

}
