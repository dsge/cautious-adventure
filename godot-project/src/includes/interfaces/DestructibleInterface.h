#pragma once

#include "../HitData.h"
#include <memory>

namespace app {

class DestructibleInterface
{
    public:
        DestructibleInterface() {}
        virtual ~DestructibleInterface() {}
        virtual void onGettingHit(std::shared_ptr<HitData> hitData) = 0;
};

}
