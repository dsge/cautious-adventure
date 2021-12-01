#ifndef APP_REGISTER_GODOT_EXTENSION
#define APP_REGISTER_GODOT_EXTENSION

#include <godot/gdnative_interface.h>

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

void register_godot_extension();
void unregister_godot_extension();

#endif