#ifndef APP_PLAYERCONTROLLEDENTITYINTERFACE_H
#define APP_PLAYERCONTROLLEDENTITYINTERFACE_H

namespace app {

class PlayerControlledEntityInterface
{
    public:
        virtual ~PlayerControlledEntityInterface() {}
        virtual godot::Camera3D* getThirdPersonCamera() = 0;
};

}
#endif