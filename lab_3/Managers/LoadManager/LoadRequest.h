#pragma once

#include <string>

enum class EntityKind { Model, Camera, Composite };
enum class EntityStructureKind { 
    DefaultCameraStructure,
    MatrixCarcassModelStructure, 
    ListCarcassModelStructure 
};

struct LoadRequest {
    std::string path;
    EntityKind kind;
    EntityStructureKind structure;
};
