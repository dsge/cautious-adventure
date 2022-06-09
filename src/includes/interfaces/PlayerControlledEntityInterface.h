#ifndef APP_PLAYERCONTROLLEDENTITYINTERFACE_H
#define APP_PLAYERCONTROLLEDENTITYINTERFACE_H

namespace app {

class PlayerControlledEntityInterface
{
    public:
        virtual ~PlayerControlledEntityInterface() {}
        virtual godot::Camera3D* getThirdPersonCamera() = 0;
        virtual godot::Camera3D* getFirstPersonCamera() = 0;
        virtual bool useFirstPersonCameraByDefault() = 0;
        /**
         * @brief The player input handlers in this entity should be enabled
         */
        virtual void enableControls() = 0;
        /**
         * @brief The player input handlers in this entity should be disabled
         */
        virtual void disableControls() = 0;
        /**
         * @brief Are the player input handlers in this entity enabled?
         */
        virtual bool getControlsEnabled() = 0;
};

}
#endif
