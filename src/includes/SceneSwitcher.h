#ifndef APP_SCENESWITCHER_H
#define APP_SCENESWITCHER_H

#include <godot.hpp>
#include <node.hpp>
#include <ref.hpp>
#include <resource_loader.hpp>
#include <packed_scene.hpp>
#include <spdlog/spdlog.h>

using namespace godot;

namespace app {

class SceneSwitcher {

protected:
    Node* sceneContainer;
    ResourceLoader* resourceLoader;

public:
    SceneSwitcher();
    ~SceneSwitcher();

    void setSceneContainer(Node*);
    Node* getSceneContainer();
    void setResourceLoader(ResourceLoader*);
    ResourceLoader* getResourceLoader();

    void switchLevel(godot::String);
};

}

#endif