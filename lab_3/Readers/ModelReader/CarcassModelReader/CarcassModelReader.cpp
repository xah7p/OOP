#include "CarcassModelReader.h"

CarcassModelReader::CarcassModelReader(std::shared_ptr<BaseCarcassModelReaderImpl> impl):
    impl(std::move(impl))
{ }

std::shared_ptr<std::vector<Vertex>> CarcassModelReader::readVertixes()
{
    if (!vertixes.empty())
        return std::make_shared<std::vector<Vertex>>(vertixes);
    if (!impl)
        return std::make_shared<std::vector<Vertex>>();
    auto values = impl->readVertixes();
    if (values)
        vertixes = *values;
    return std::make_shared<std::vector<Vertex>>(vertixes);
}

std::shared_ptr<std::vector<Edge>> CarcassModelReader::readEdges()
{
    if (!edges.empty())
        return std::make_shared<std::vector<Edge>>(edges);
    if (!impl)
        return std::make_shared<std::vector<Edge>>();
    auto values = impl->readEdges();
    if (values)
        edges = *values;
    return std::make_shared<std::vector<Edge>>(edges);
}
