#include "includes/register_godot_extension.h"

#include "includes/Startup.h"
#include "includes/FooExperiment.h"
#include "includes/PlayerControlledEntities/PlayerControlledEntityHandler.h"
#include "includes/PlayerControlledEntities/PlayerCharacterBody.h"
#include "includes/Enemies/SimpleMeleeEnemy.h"

void register_godot_extension(godot::ModuleInitializationLevel p_level) {
    if (p_level != godot::MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

    using namespace app;

	godot::ClassDB::register_class<Startup>();
    godot::ClassDB::register_class<PlayerControlledEntityHandler>();
    godot::ClassDB::register_class<FooExperiment>();
    godot::ClassDB::register_class<PlayerCharacterBody>();
    godot::ClassDB::register_class<SimpleMeleeEnemy>();

}

void unregister_godot_extension(godot::ModuleInitializationLevel p_level) {
    if (p_level != godot::MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}

extern "C" {

// Initialization.

    GDExtensionBool GDE_EXPORT on_app_godot_library_init(
            GDExtensionInterfaceGetProcAddress p_get_proc_address,
            GDExtensionClassLibraryPtr p_library,
            GDExtensionInitialization *r_initialization
        ) {
        godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

        init_obj.register_initializer(register_godot_extension);
        init_obj.register_terminator(unregister_godot_extension);
        init_obj.set_minimum_library_initialization_level(godot::MODULE_INITIALIZATION_LEVEL_SCENE);

        return init_obj.init();
    }
}
