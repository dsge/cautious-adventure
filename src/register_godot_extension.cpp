#include "includes/register_godot_extension.h"

#include "includes/Startup.h"

using namespace godot;
using namespace app;

void register_godot_extension() {
	ClassDB::register_class<Startup>();
}

void unregister_godot_extension() {}

extern "C" {

// Initialization.

    GDNativeBool GDN_EXPORT on_app_godot_library_init(
            const GDNativeInterface *p_interface, 
            const GDNativeExtensionClassLibraryPtr p_library, 
            GDNativeInitialization *r_initialization
        ) {
        godot::GDExtensionBinding::InitObject init_obj(p_interface, p_library, r_initialization);

        init_obj.register_scene_initializer(register_godot_extension);
        init_obj.register_scene_terminator(unregister_godot_extension);

        return init_obj.init();
    }
}