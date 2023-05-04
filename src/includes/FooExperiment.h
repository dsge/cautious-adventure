#ifndef APP_FOOEXPERIMENT_H
#define APP_FOOEXPERIMENT_H

#include "vendor/Godot.h"

#include <spdlog/spdlog.h>

#include "./Startup.h"
#include "./SceneSwitcher.h"
#include "./PlayerControlledEntities/Simpleship.h"
#include "./PlayerControlledEntities/Hovership.h"
#include "./PlayerControlledEntities/PlayerCharacterBody.h"
#include "./PlayerControlledEntities/PlayerControlledEntityHandlerWrapper.h"
#include "./helper-functions.h"

namespace app {

class FooExperiment : public godot::Node3D {
    GDCLASS(FooExperiment, godot::Node3D);

protected:
    static void _bind_methods();

public:


    FooExperiment();
    ~FooExperiment();
    void _enter_tree() override;
    // virtual void _notification(int64_t what) override;

    void _ready() override;

    void _process(float delta);
};

}


#endif
