#include "ObjCarcassModelReaderImpl.h"

#include <sstream>

ObjCarcassModelReaderImpl::ObjCarcassModelReaderImpl(const std::string& path):
    BaseCarcassModelReaderImpl(path)
{ }

std::shared_ptr<std::vector<Vertex>> ObjCarcassModelReaderImpl::readVertixes()
{
    file.clear();
    file.seekg(0);
    std::string line;
    auto vertices = std::make_shared<std::vector<Vertex>>();
    while (std::getline(file, line))
    {
        if (!line.starts_with("v "))
            continue;
        std::istringstream is(line.substr(2));
        double x = 0.0, y = 0.0, z = 0.0;
        is >> x >> y >> z;
        vertices->emplace_back(x, y, z);
    }
    return vertices;
}

std::shared_ptr<std::vector<Edge>> ObjCarcassModelReaderImpl::readEdges()
{
    file.clear();
    file.seekg(0);
    std::string line;
    auto edges = std::make_shared<std::vector<Edge>>();
    while (std::getline(file, line))
    {
        if (!line.starts_with("l "))
            continue;
        std::istringstream is(line.substr(2));
        size_t a = 0, b = 0;
        is >> a >> b;
        if (a > 0 && b > 0)
            edges->emplace_back(a - 1, b - 1);
    }
    return edges;
}
