#ifndef APP_PLAYERCONTROLLEDENTITYHANDLER_H
#define APP_PLAYERCONTROLLEDENTITYHANDLER_H

#include "vendor/Godot.h"
#include <spdlog/spdlog.h>


namespace app {

class PlayerControlledEntityHandler : public godot::Node {
    GDCLASS(PlayerControlledEntityHandler, godot::Node);

protected:
    static void _bind_methods();

public:
    

    PlayerControlledEntityHandler();
    ~PlayerControlledEntityHandler();

    void _ready() override;

    void _process(float delta);
};

}


#endif