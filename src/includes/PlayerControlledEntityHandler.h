#ifndef APP_PLAYERCONTROLLEDENTITYHANDLER_H
#define APP_PLAYERCONTROLLEDENTITYHANDLER_H

#include "vendor/Godot.h"
#include <spdlog/spdlog.h>

using namespace godot;

namespace app {

class PlayerControlledEntityHandler : public Node {
    GDCLASS(PlayerControlledEntityHandler, Node);

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