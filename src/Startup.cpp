#include "includes/Startup.h"

using namespace app;

void Startup::_bind_methods() {
    // std::cout << "Startup bind methods cccccc" << std::endl;
    // godot::UtilityFunctions::print("Startup bind methods sss");
    auto console = spdlog::stdout_logger_mt("console");
    spdlog::set_default_logger(console);
    spdlog::set_level(spdlog::level::debug); // Set global log level to debug
    spdlog::info("Startup bind methods cccccc");
    // ClassDB::bind_method(D_METHOD("init"), &Startup::_init);
    // ClassDB::bind_method(D_METHOD("_init"), &Startup::_init);
    ClassDB::bind_method(D_METHOD("ready"), &Startup::_ready);
    ClassDB::bind_method(D_METHOD("process"), &Startup::_process);
    ClassDB::bind_method(D_METHOD("enter_tree"), &Startup::_enter_tree);
}

Startup::Startup() {
    // godot::UtilityFunctions::print("Startup constructor");
    // std::cout << "Startup constructor" << std::endl;
}

void Startup::_init() {
    // std::cout << "Startup init" << std::endl;
    // godot::UtilityFunctions::print("Startup init");
}

void Startup::_enter_tree() {
    // std::cout << "Startup enter tree" << std::endl;
    // godot::UtilityFunctions::print("Startup enter tree");
}

/* void Startup::_notification(int64_t what) {
    std::cout << "Startup notification with: " << what << std::endl;
} */

void Startup::_ready() {
    // std::cout << "Startup ready" << std::endl;
    // godot::UtilityFunctions::print("Startup ready");
    #ifdef INCLUDE_TESTRUNNER
        this->runTestsAndExit();
    #else
        this->initGameNormally();
    #endif
}

void Startup::runTestsAndExit() {
    #ifdef INCLUDE_TESTRUNNER
    // std::cout << "Startup::runTestsAndExit()" << std::endl;
    ::testing::InitGoogleTest();
    ::exit(RUN_ALL_TESTS());
    #endif
}

void Startup::initGameNormally() {
    // std::cout << "Startup::initGameNormally()" << std::endl;
}

void Startup::_process(float delta) {
    
}

Startup::~Startup() {
    // godot::UtilityFunctions::print("Startup destructor");
}