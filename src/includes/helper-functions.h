#ifndef APP_HELPERFUNCTIONS_H
#define APP_HELPERFUNCTIONS_H

#include <node.hpp>
#include <node_path.hpp>
#include <spdlog/spdlog.h>

namespace app {
/**
 * @brief call `godot::Node`'s `get_node_or_null` function
 *
 * godot's own implementation segfaults in the cases where the function would return nullptr
 *
 * this function can be removed from our code once godot's implementation works as expected
 *
 * @param node
 * @param path
 * @return godot::Node*
 */
inline godot::Node* call_get_node_or_null(godot::Node* node, const godot::NodePath &path) {
    if (!node) {
        spdlog::info("app::call_get_node_or_null called with nullptr");
    }
    if (node && node->has_node(path)) {
        return node->get_node_or_null(path);
    } else {
        return nullptr;
    }
}


template<class T> inline T* call_cast_to(godot::Node* node) {
    if (node) {
        return godot::Object::cast_to<T>(node);
    } else {
        return nullptr;
    }
}

/**
 * @brief call `godot::Node`'s `get_node` function
 *
 * godot's own implementation segfaults in the cases where the function would return nullptr
 *
 * this function can be removed from our code once godot's implementation works as expected
 *
 * @param node
 * @param path
 * @return godot::Node*
 */
template<class T> T *call_get_node(godot::Node* node, const godot::NodePath &p_path) {
    return call_cast_to<T>(call_get_node_or_null(node, p_path));
}

}

#endif
