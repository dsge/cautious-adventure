#ifndef APP_STARTUP_H
#define APP_STARTUP_H

#include <node.hpp>
#include <node3d.hpp>
#include <godot.hpp>
#include <utility_functions.hpp>
#include <Hypodermic/Hypodermic.h>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_sinks.h>

#include "./SceneSwitcher.h"
#include "./PlayerControlledEntityHandler.h"

#ifdef INCLUDE_TESTRUNNER
    #include <gtest/gtest.h>
#endif

using namespace godot;

namespace app {

class Startup : public Node {
    GDCLASS(Startup, Node);

protected:
    static void _bind_methods();
    std::shared_ptr< Hypodermic::Container > container;

public:
    

    Startup();
    ~Startup();

    void _init(); // our initializer called by Godot
    void _enter_tree() override;
    // virtual void _notification(int64_t what) override;

    void _ready() override;

    void _process(float delta);

    void runTestsAndExit();
    void initGameNormally();
};

}


#endif