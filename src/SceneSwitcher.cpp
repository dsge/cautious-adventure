#include "includes/SceneSwitcher.h"


using namespace godot;
using namespace app;


SceneSwitcher::SceneSwitcher() {
    this->resourceLoader = ResourceLoader::get_singleton();
    // this->playerControls = PlayerControls::_new();
}

SceneSwitcher::~SceneSwitcher() {
    // bool isValid = core_1_1_api->godot_is_instance_valid(this->playerControls);
    /*bool isInsideTree = this->playerControls->is_inside_tree();
    if (this->playerControls && !isInsideTree) {
        this->playerControls->queue_free();
        delete this->playerControls;
    }*/

    spdlog::info("SceneSwitcher destructor yeeaaaahhh");
}

void SceneSwitcher::switchLevel(godot::String levelName) {
    if (!this->sceneContainer) {
        spdlog::info("SceneSwitcher switchLevel no sceneContainer");
        return;
    }
    spdlog::info("SceneSwitcher switchLevel HAS sceneContainer");
    // initialize any variables here

    // https://godotengine.org/qa/12873/calling-nodes-from-c
    // https://godotengine.org/qa/45083/solved-how-to-load-resource-scene-using-gdnative-c

    

    Ref<PackedScene> levelPrototype = this->resourceLoader->load(levelName, "PackedScene");
	if (!levelPrototype.is_valid()) {
        spdlog::info("SceneSwitcher switchLevel unable to load requested level");
        return;
    }
    Node *level = levelPrototype->instantiate();
	if (!level) {
        spdlog::info("SceneSwitcher switchLevel unable to instantiate level");
		return;
	}

    /*KinematicBody* playerCharacter = firstLevel->getPlayerCharacter();*/

    // this->playerControls->setControlledEntity(playerCharacter);

    this->sceneContainer->add_child(level);

    // this->sceneContainer->get_tree().
}

void SceneSwitcher::setSceneContainer(Node* value) {
    this->sceneContainer = value;
    // this->sceneContainer->add_child(this->playerControls);
}

Node* SceneSwitcher::getSceneContainer() {
    return this->sceneContainer;
}

void SceneSwitcher::setResourceLoader(ResourceLoader* value) {
    this->resourceLoader = value;
}

ResourceLoader* SceneSwitcher::getResourceLoader() {
    return this->resourceLoader;
}
