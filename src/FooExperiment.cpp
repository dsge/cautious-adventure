#include "includes/FooExperiment.h"

using namespace app;

void FooExperiment::_bind_methods() {
    godot::ClassDB::bind_method(godot::D_METHOD("ready"), &FooExperiment::_ready);
    godot::ClassDB::bind_method(godot::D_METHOD("process"), &FooExperiment::_process);
    godot::ClassDB::bind_method(godot::D_METHOD("enter_tree"), &FooExperiment::_enter_tree);
}

FooExperiment::FooExperiment() {

}

void FooExperiment::_enter_tree() {
    // spdlog::info("FooExperiment enter tree");


}

void FooExperiment::_ready() {
    /*godot::Array arr;
    arr.resize(godot::Mesh::ArrayType::ARRAY_MAX);

    godot::PackedVector3Array verts;
    godot::PackedVector2Array uvs;
    godot::PackedVector3Array normals;
    godot::PackedInt32Array indices;

    normals.append(godot::Vector3(0.0f, 0.0f, -1.0f));
    uvs.append(godot::Vector2(0, 0));
    verts.append(godot::Vector3(-1, -1, 0));

    normals.append(godot::Vector3(0, 0, -1));
    uvs.append(godot::Vector2(0, 1));
    verts.append(godot::Vector3(-2, 1, 0));

    normals.append(godot::Vector3(0, 0, -1));
    uvs.append(godot::Vector2(1, 1));
    verts.append(godot::Vector3(1, 1, 0));

    // arr[godot::Mesh::ArrayType::ARRAY_NORMAL] = normals;
    arr[godot::Mesh::ArrayType::ARRAY_TEX_UV] = uvs;
    arr[godot::Mesh::ArrayType::ARRAY_VERTEX] = verts;


    godot::Ref<godot::ArrayMesh> mesh;
    mesh.instantiate();
    mesh->add_surface_from_arrays(godot::Mesh::PrimitiveType::PRIMITIVE_TRIANGLES, arr);

    auto meshInstance = memnew(godot::MeshInstance3D);
    meshInstance->set_mesh(mesh);
    this->add_child(meshInstance);*/

    auto container = this->get_node<Startup>("/root/Startup")->getContainer();

    auto sceneSwitcher = container->resolve< SceneSwitcher >();
    // auto initialControlledEntityCandidates = sceneSwitcher->getSceneContainer()->find_nodes("", "Simpleship", true, false);
    auto initialControlledEntityCandidates = this->get_node<godot::Node>("/root/Startup/sceneContainer/Experiments")->find_nodes("*", "Simpleship", true, false);
    if (initialControlledEntityCandidates.is_empty()) {
        spdlog::info("initialControlledEntityCandidates empty ???");


        auto foo = this->get_node<Simpleship>("/root/Startup/sceneContainer/Experiments/SimpleShip/simpleship_2");
        if (foo) {
            spdlog::info("--12345--");
        }
        spdlog::info("--67890--");

    } else {
        container->resolve< PlayerControlledEntityHandlerWrapper >()->node->setModel(static_cast<Simpleship *>(initialControlledEntityCandidates[0].operator Object *()));
    }

}

void FooExperiment::_process(float delta) {

}

FooExperiment::~FooExperiment() {

}
