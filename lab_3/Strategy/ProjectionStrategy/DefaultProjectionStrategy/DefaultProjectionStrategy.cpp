#include "DefaultProjectionStrategy.h"
#include <cmath>

void DefaultProjectionStrategy::prepare(std::vector<Vertex>& projectedVertexes,
                                        std::shared_ptr<CarcassModelStructure> model,
                                        std::shared_ptr<CameraEntityStructure> camera,
                                        double aspectRatio)
{
    if (!model)
        return;

    auto vertices = model->getVertices();
    projectedVertexes.clear();
    projectedVertexes.reserve(vertices.size());
    if (!camera)
    {
        for (const auto& v : vertices)
            projectedVertexes.emplace_back(v.getX(), -v.getY(), v.getZ());
        return;
    }

    const auto lookMatrix = camera->getLookMatrix();
    const auto safeAspect = (aspectRatio > 1e-9) ? aspectRatio : 1.0;
    const auto projectionMatrix = camera->getProjectionMatrix(safeAspect);

    for (const auto& vertex : vertices)
    {
        Matrix<double> point(4, 1, 0.0);
        point[0][0] = vertex.getX();
        point[1][0] = vertex.getY();
        point[2][0] = vertex.getZ();
        point[3][0] = 1.0;

        const auto cameraPoint = lookMatrix * point;
        point = projectionMatrix * cameraPoint;

        double x = 0.0;
        double y = 0.0;
        double z = 0.0;
        const double w = point[3][0];
        bool valid = true;
        if (std::abs(w) > 1e-9 && w > 0.0)
        {
            x = point[0][0] / w;
            y = point[1][0] / w;
            z = point[2][0] / w;
            if (!std::isfinite(x) || !std::isfinite(y) || !std::isfinite(z))
                valid = false;
        }
        else
            valid = false;

        Vertex projected(x, -y, z);
        projected.setW(valid ? 1.0 : 0.0);
        projectedVertexes.push_back(projected);
    }
}
