#include "includes/Startup.h"

using namespace app;

void Startup::_bind_methods() {
    auto console = spdlog::stdout_logger_mt("console");
    spdlog::set_default_logger(console);
    spdlog::set_level(spdlog::level::debug); // Set global log level to debug
    // ClassDB::bind_method(D_METHOD("init"), &Startup::_init);
    // ClassDB::bind_method(D_METHOD("_init"), &Startup::_init);
    godot::ClassDB::bind_method(godot::D_METHOD("ready"), &Startup::_ready);
    godot::ClassDB::bind_method(godot::D_METHOD("process"), &Startup::_process);
    godot::ClassDB::bind_method(godot::D_METHOD("enter_tree"), &Startup::_enter_tree);
}

Startup::Startup() {

}

void Startup::_init() {
}

void Startup::_enter_tree() {
    // spdlog::info("Startup enter tree");

    godot::Node3D* sceneContainer = memnew(godot::Node3D);
    sceneContainer->set_name("sceneContainer");
    this->add_child(sceneContainer);

    auto resourceLoader = godot::ResourceLoader::get_singleton();
    godot::Ref<godot::PackedScene> globalHealthBarPrototype = resourceLoader->load("res://scenes/GlobalHealthBar.tscn", "PackedScene");

    Hypodermic::ContainerBuilder builder;
    builder
        .registerType< SceneSwitcher >()
        .onActivated([sceneContainer](Hypodermic::ComponentContext&, const std::shared_ptr< SceneSwitcher >& instance) {
            instance->setSceneContainer(sceneContainer);
        })
        .singleInstance();
    builder
        .registerType< GodotNodeWrapper<PlayerControlledEntityHandler>  >()
        .onActivated([](Hypodermic::ComponentContext&, const std::shared_ptr< GodotNodeWrapper<PlayerControlledEntityHandler> >& instance) {
            auto handler = memnew(PlayerControlledEntityHandler);
            handler->set_name("PlayerControlledEntityHandler");
            instance->node = handler;
        })
        .singleInstance();
    builder
        .registerType< GodotNodeWrapper<godot::ResourceLoader> >()
        .onActivated([](Hypodermic::ComponentContext&, const std::shared_ptr< GodotNodeWrapper<godot::ResourceLoader> >& instance) {
            instance->node = godot::ResourceLoader::get_singleton();
        })
        .singleInstance();
    this->container = builder.build();
    builder
        .registerType< GodotNodeWrapper<GlobalHealthBar> >()
        .onActivated([globalHealthBarPrototype](Hypodermic::ComponentContext&, const std::shared_ptr< GodotNodeWrapper<GlobalHealthBar> >& instance) {
            instance->node = app::call_cast_to<GlobalHealthBar>(globalHealthBarPrototype->instantiate());
        })
        .singleInstance();
    this->container = builder.build();

    // app::setGlobalContainer(this->container);


    // std::cout << "Startup enter tree" << std::endl;
    // godot::UtilityFunctions::print("Startup enter tree");
}

/* void Startup::_notification(int64_t what) {
    std::cout << "Startup notification with: " << what << std::endl;
} */

void Startup::_ready() {
    this->add_child((this->container->resolve< GodotNodeWrapper<PlayerControlledEntityHandler> >())->node);
    this->add_child((this->container->resolve< GodotNodeWrapper<GlobalHealthBar> >())->node);

    // this->add_child(memnew(PlayerControlledEntityHandler));
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
    ::testing::InitGoogleTest();
    this->get_tree()->get_root()->propagate_notification(godot::Node::NOTIFICATION_WM_CLOSE_REQUEST);
    this->get_tree()->quit(RUN_ALL_TESTS());
    #endif
}

void Startup::initGameNormally() {
    auto sceneSwitcher = container->resolve< SceneSwitcher >();
    sceneSwitcher->switchLevel("res://scenes/Experiments.tscn");
}

void Startup::_process(float delta) {

}

std::shared_ptr< Hypodermic::Container > Startup::getContainer() {
    return this->container;
}

Startup::~Startup() {
    // godot::UtilityFunctions::print("Startup destructor");
}
