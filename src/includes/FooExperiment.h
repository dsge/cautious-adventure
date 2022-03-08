#ifndef APP_FOOEXPERIMENT_H
#define APP_FOOEXPERIMENT_H

#include <node.hpp>
#include <node3d.hpp>
#include <godot.hpp>
#include <surface_tool.hpp>
#include <mesh.hpp>
#include <vector3.hpp>
#include <vector2.hpp>
#include <array_mesh.hpp>
#include <packed_vector3_array.hpp>
#include <packed_vector2_array.hpp>
#include <packed_int32_array.hpp>
#include <array.hpp>
#include <mesh_instance3d.hpp>
#include <utility_functions.hpp>

#include <spdlog/spdlog.h>
using namespace godot;

namespace app {

class FooExperiment : public Node3D {
    GDCLASS(FooExperiment, Node3D);

protected:
    static void _bind_methods();

public:
    

    FooExperiment();
    ~FooExperiment();
    void _enter_tree() override;
    // virtual void _notification(int64_t what) override;

    void _ready() override;

    void _process(float delta);
};

}


#endif