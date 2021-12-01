#ifndef APP_REGISTER_GODOT_EXTENSION
#define APP_REGISTER_GODOT_EXTENSION

#include <godot/gdnative_interface.h>

#include <class_db.hpp>
#include <defs.hpp>
#include <godot.hpp>

void register_godot_extension();
void unregister_godot_extension();

#endif