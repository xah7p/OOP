#include "DefaultCenterStrategy.h"

void DefaultCenterStrategy::prepare(std::vector<Vertex>& vertices, size_t width, size_t height)
{
    const double cx = static_cast<double>(width) / 2.0;
    const double cy = static_cast<double>(height) / 2.0;
    for (auto& v : vertices)
    {
        if (v.getW() == 0.0)
            continue;
        v.setX(v.getX() * cx + cx);
        v.setY(v.getY() * cy + cy);
    }
}
