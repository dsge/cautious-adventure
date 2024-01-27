#ifndef APP_SCENESWITCHER_H
#define APP_SCENESWITCHER_H

#include "vendor/Godot.h"

#include <spdlog/spdlog.h>

namespace app {

class SceneSwitcher {

protected:
    godot::Node* sceneContainer;
    godot::ResourceLoader* resourceLoader;

public:
    SceneSwitcher();
    ~SceneSwitcher();

    void setSceneContainer(godot::Node*);
    godot::Node* getSceneContainer();
    void setResourceLoader(godot::ResourceLoader*);
    godot::ResourceLoader* getResourceLoader();

    void switchLevel(godot::String);
};

}

#endif