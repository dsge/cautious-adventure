#ifndef APP_PLAYERCONTROLLEDENTITYHANDLER_H
#define APP_PLAYERCONTROLLEDENTITYHANDLER_H

#include "../vendor/Godot.h"
#include <spdlog/spdlog.h>

#include "./Simpleship.h"
#include "../interfaces/PlayerControlledEntityInterface.h"


namespace app {

class PlayerControlledEntityHandler : public godot::Node {
    GDCLASS(PlayerControlledEntityHandler, godot::Node);

protected:
    static void _bind_methods();
    /**
     * The currently controlled model
     */
    godot::Node3D* model;

public:



    PlayerControlledEntityHandler();
    ~PlayerControlledEntityHandler();

    void _ready() override;

    void _process(float delta);

    void setModel(godot::Node3D* value);
    godot::Node3D* getModel();
};

}


#endif
