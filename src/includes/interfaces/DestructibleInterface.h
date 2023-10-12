#pragma once

#include "../HitData.h"
#include <memory>

namespace app {

class DestructibleInterface
{
    public:
        DestructibleInterface() {}
        virtual ~DestructibleInterface() {}
        // virtual godot::Camera3D* getThirdPersonCamera() = 0;
        virtual void onHit(std::shared_ptr<HitData> hitData) = 0;
};

}
