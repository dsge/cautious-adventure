#include "includes/Startup.h"

using namespace godot;
using namespace app;

void Startup::_bind_methods() {
    UtilityFunctions::print("Startup bind methods");
    ClassDB::bind_method(D_METHOD("init"), &Startup::_init);
    ClassDB::bind_method(D_METHOD("ready"), &Startup::_ready);
    ClassDB::bind_method(D_METHOD("process"), &Startup::_process);
    ClassDB::bind_method(D_METHOD("enter_tree"), &Startup::_enter_tree);
}

Startup::Startup() {
    UtilityFunctions::print("Startup constrt");
}

void Startup::_init() {
    UtilityFunctions::print("Startup init");
}

void Startup::_enter_tree() {
    UtilityFunctions::print("Startup enter tree");
}

void Startup::_ready() {
    UtilityFunctions::print("Startup ready");
    #ifdef INCLUDE_TESTRUNNER
        this->runTestsAndExit();
    #else
        this->initGameNormally();
    #endif
}

void Startup::runTestsAndExit() {
    #ifdef INCLUDE_TESTRUNNER
    ::testing::InitGoogleTest();
    ::exit(RUN_ALL_TESTS());
    #endif
}

void Startup::initGameNormally() {
    
}

void Startup::_process(float delta) {
    
}

Startup::~Startup() {
    
}