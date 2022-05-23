#include "includes/register_godot_extension.h"

#include "includes/Startup.h"
#include "includes/FooExperiment.h"
#include "includes/PlayerControlledEntityHandler.h"
#include "includes/Simpleship.h"

using namespace app;

void register_godot_extension(godot::ModuleInitializationLevel p_level) {
    if (p_level != godot::MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
	godot::ClassDB::register_class<Startup>();
    godot::ClassDB::register_class<PlayerControlledEntityHandler>();
    godot::ClassDB::register_class<FooExperiment>();
    godot::ClassDB::register_class<Simpleship>();

}

void unregister_godot_extension(godot::ModuleInitializationLevel p_level) {
    if (p_level != godot::MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}

extern "C" {

// Initialization.

    GDNativeBool GDN_EXPORT on_app_godot_library_init(
            const GDNativeInterface *p_interface,
            const GDNativeExtensionClassLibraryPtr p_library,
            GDNativeInitialization *r_initialization
        ) {
        godot::GDExtensionBinding::InitObject init_obj(p_interface, p_library, r_initialization);

        init_obj.register_initializer(register_godot_extension);
        init_obj.register_terminator(unregister_godot_extension);
        init_obj.set_minimum_library_initialization_level(godot::MODULE_INITIALIZATION_LEVEL_SCENE);

        return init_obj.init();
    }
}
