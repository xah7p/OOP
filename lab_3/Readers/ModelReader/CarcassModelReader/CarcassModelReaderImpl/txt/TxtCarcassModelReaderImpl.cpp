#include "TxtCarcassModelReaderImpl.h"
#include "ModelException.h"

TxtCarcassModelReaderImpl::TxtCarcassModelReaderImpl(const std::string& path):
    BaseCarcassModelReaderImpl(path)
{ }

std::shared_ptr<std::vector<Vertex>> TxtCarcassModelReaderImpl::readVertixes()
{
    file.clear();
    file.seekg(0);
    size_t n = 0;
    if (!(file >> n))
        throw ModelInvalidStructureException("File should contain vertices count on first line.");
    if (n == 0)
        throw ModelInvalidVerticesCountException("Invalid vertices count. Should be > 0.");
    auto vertices = std::make_shared<std::vector<Vertex>>();
    vertices->reserve(n);
    for (size_t i = 0; i < n; ++i)
    {
        double x = 0.0, y = 0.0, z = 0.0;
        if (!(file >> x >> y >> z))
            throw ModelInvalidVertexException("File contains invalid vertex.");
        vertices->emplace_back(x, y, z);
    }
    return vertices;
}

std::shared_ptr<std::vector<Edge>> TxtCarcassModelReaderImpl::readEdges()
{
    file.clear();
    file.seekg(0);
    size_t n = 0;
    if (!(file >> n))
        throw ModelInvalidStructureException("File should contain vertices count on first line.");
    if (n == 0)
        throw ModelInvalidVerticesCountException("Invalid vertices count. Should be > 0.");
    for (size_t i = 0; i < n; ++i)
    {
        double x = 0.0, y = 0.0, z = 0.0;
        if (!(file >> x >> y >> z))
            throw ModelInvalidVertexException("File contains invalid vertex.");
    }
    size_t m = 0;
    if (!(file >> m))
        throw ModelInvalidStructureException("File should contain edges count after vertices.");
    auto edges = std::make_shared<std::vector<Edge>>();
    edges->reserve(m);
    for (size_t i = 0; i < m; ++i)
    {
        size_t a = 0, b = 0;
        if (!(file >> a >> b))
            throw ModelInvalidEdgeException("File contains invalid edge.");
        edges->emplace_back(a, b);
    }
    return edges;
}
