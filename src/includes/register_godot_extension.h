#ifndef APP_REGISTER_GODOT_EXTENSION
#define APP_REGISTER_GODOT_EXTENSION

#include "vendor/Godot.h"

void register_godot_extension(godot::ModuleInitializationLevel p_level);
void unregister_godot_extension(godot::ModuleInitializationLevel p_level);

#endif
