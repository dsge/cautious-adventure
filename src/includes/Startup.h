#ifndef APP_STARTUP_H
#define APP_STARTUP_H

#include "vendor/Godot.h"
#include <Hypodermic/Hypodermic.h>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_sinks.h>

#include "./SceneSwitcher.h"
#include "./PlayerControlledEntityHandler.h"
#include "./PlayerControlledEntityHandlerWrapper.h"
#include "./Simpleship.h"

#ifdef INCLUDE_TESTRUNNER
    #include <gtest/gtest.h>
#endif

namespace app {

class Startup : public godot::Node {
    GDCLASS(Startup, godot::Node);

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

    std::shared_ptr< Hypodermic::Container > getContainer();
};

}


#endif
