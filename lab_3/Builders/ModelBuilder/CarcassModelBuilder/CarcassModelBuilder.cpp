#include "CarcassModelBuilder.h"

CarcassModelBuilder::CarcassModelBuilder(std::shared_ptr<CarcassModelReader> reader,
                                         std::shared_ptr<CarcassModelStructure> structure):
    BaseModelBuilder(std::move(reader)), structure(std::move(structure))
{ }

std::shared_ptr<BaseEntity> CarcassModelBuilder::createEntity()
{
    return std::make_shared<CarcassModelEntity>(structure);
}

bool CarcassModelBuilder::buildVertixes()
{
    if (!reader || !structure)
        return false;
    auto vertices = reader->readVertixes();
    if (!vertices)
        return false;
    for (const auto& v : *vertices)
        structure->addVertex(v);
    part = static_cast<size_t>(ModelBuildPart::Edges);
    return true;
}

bool CarcassModelBuilder::buildEdges()
{
    if (!reader || !structure)
        return false;
    auto edges = reader->readEdges();
    if (!edges)
        return false;
    for (const auto& e : *edges)
        structure->addEdge(e);
    part = static_cast<size_t>(ModelBuildPart::Center);
    return true;
}

bool CarcassModelBuilder::buildCenter()
{
    if (!structure)
        return false;
    auto vertices = structure->getVertices();
    if (vertices.empty())
    {
        structure->setCenter(Vertex(0.0, 0.0, 0.0));
        return true;
    }
    Vertex center(0.0, 0.0, 0.0);
    for (const auto& v : vertices)
        center += v;
    center.setX(center.getX() / static_cast<double>(vertices.size()));
    center.setY(center.getY() / static_cast<double>(vertices.size()));
    center.setZ(center.getZ() / static_cast<double>(vertices.size()));
    structure->setCenter(center);
    part = static_cast<size_t>(ModelBuildPart::Center) + 1;
    return true;
}
