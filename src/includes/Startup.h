#ifndef APP_STARTUP_H
#define APP_STARTUP_H

#ifdef INCLUDE_TESTRUNNER
    #include <gtest/gtest.h>
#endif

#include <godot.hpp>
#include <node.hpp>
#include <utility_functions.hpp>
#include <Hypodermic/Hypodermic.h>

using namespace godot;

namespace app {

class Startup : public Node {
    GDCLASS(Startup, Node);

protected:
    static void _bind_methods();

public:
    

    Startup();
    ~Startup();

    void _init(); // our initializer called by Godot
    void _enter_tree();

    void _ready();

    void _process(float delta);

    void runTestsAndExit();
    void initGameNormally();
};

}


#endif