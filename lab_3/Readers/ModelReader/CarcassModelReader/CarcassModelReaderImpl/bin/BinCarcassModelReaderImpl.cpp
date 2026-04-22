#include "BinCarcassModelReaderImpl.h"

BinCarcassModelReaderImpl::BinCarcassModelReaderImpl(const std::string& path):
    BaseCarcassModelReaderImpl(path)
{ }

std::shared_ptr<std::vector<Vertex>> BinCarcassModelReaderImpl::readVertixes()
{
    file.clear();
    file.seekg(0);
    size_t n = 0;
    file.read(reinterpret_cast<char*>(&n), sizeof(n));
    auto vertices = std::make_shared<std::vector<Vertex>>();
    vertices->reserve(n);
    for (size_t i = 0; i < n; ++i)
    {
        double x = 0.0, y = 0.0, z = 0.0;
        file.read(reinterpret_cast<char*>(&x), sizeof(double));
        file.read(reinterpret_cast<char*>(&y), sizeof(double));
        file.read(reinterpret_cast<char*>(&z), sizeof(double));
        vertices->emplace_back(x, y, z);
    }
    return vertices;
}

std::shared_ptr<std::vector<Edge>> BinCarcassModelReaderImpl::readEdges()
{
    file.clear();
    file.seekg(0);
    size_t n = 0;
    file.read(reinterpret_cast<char*>(&n), sizeof(n));
    file.seekg(static_cast<std::streamoff>(n * 3 * sizeof(double)), std::ios::cur);
    size_t m = 0;
    file.read(reinterpret_cast<char*>(&m), sizeof(m));
    auto edges = std::make_shared<std::vector<Edge>>();
    edges->reserve(m);
    for (size_t i = 0; i < m; ++i)
    {
        size_t a = 0, b = 0;
        file.read(reinterpret_cast<char*>(&a), sizeof(size_t));
        file.read(reinterpret_cast<char*>(&b), sizeof(size_t));
        edges->emplace_back(a, b);
    }
    return edges;
}
