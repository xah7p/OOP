#include "ZBufferStrategy.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <set>
#include <vector>

namespace
{
bool edgeExists(const std::vector<std::vector<size_t>>& adj, size_t a, size_t b)
{
    if (a >= adj.size())
        return false;
    return std::binary_search(adj[a].begin(), adj[a].end(), b);
}

std::vector<std::array<size_t, 4>> findQuadFaces(const std::vector<Edge>& edges, size_t vertexCount)
{
    std::vector<std::vector<size_t>> adj(vertexCount);
    for (const auto& edge : edges)
    {
        if (edge.getFirst() >= vertexCount || edge.getSecond() >= vertexCount)
            continue;
        adj[edge.getFirst()].push_back(edge.getSecond());
        adj[edge.getSecond()].push_back(edge.getFirst());
    }

    for (auto& neighbours : adj)
    {
        std::sort(neighbours.begin(), neighbours.end());
        neighbours.erase(std::unique(neighbours.begin(), neighbours.end()), neighbours.end());
    }

    std::set<std::array<size_t, 4>> uniqueIds;
    std::vector<std::array<size_t, 4>> faces;
    for (const auto& edge : edges)
    {
        const size_t a = edge.getFirst();
        const size_t b = edge.getSecond();
        if (a >= vertexCount || b >= vertexCount)
            continue;

        for (size_t c : adj[b])
        {
            if (c == a)
                continue;
            for (size_t d : adj[c])
            {
                if (d == a || d == b)
                    continue;
                if (!edgeExists(adj, d, a))
                    continue;

                std::array<size_t, 4> ordered = {a, b, c, d};
                auto key = ordered;
                std::sort(key.begin(), key.end());
                if (uniqueIds.insert(key).second)
                    faces.push_back(ordered);
            }
        }
    }


    return faces;
}

bool pointInTriangle(double px, double py, const Vertex& a, const Vertex& b, const Vertex& c,
                     double& wa, double& wb, double& wc)
{
    const double v0x = b.getX() - a.getX();
    const double v0y = b.getY() - a.getY();
    const double v1x = c.getX() - a.getX();
    const double v1y = c.getY() - a.getY();
    const double v2x = px - a.getX();
    const double v2y = py - a.getY();

    const double den = v0x * v1y - v1x * v0y;
    if (std::abs(den) < 1e-9)
        return false;

    wb = (v2x * v1y - v1x * v2y) / den;
    wc = (v0x * v2y - v2x * v0y) / den;
    wa = 1.0 - wb - wc;
    constexpr double eps = -1e-6;
    return wa >= eps && wb >= eps && wc >= eps;
}

void appendVisibleRun(std::vector<ZBufferStrategy::Edge2D>& visibleEdges, const std::vector<Vertex>& run)
{
    if (run.size() < 2)
        return;
    for (size_t i = 1; i < run.size(); ++i)
        visibleEdges.emplace_back(run[i - 1], run[i]);
}

}  

void ZBufferStrategy::prepare(std::vector<Edge2D>& visibleEdges,
                              const std::vector<Vertex>& vertices,
                              const std::vector<Edge>& edges,
                              std::shared_ptr<BaseCameraEntity> camera)
{
    (void)camera;
    visibleEdges.clear();

    struct Triangle
    {
        Vertex a;
        Vertex b;
        Vertex c;
    };

    std::vector<Triangle> triangles;
    triangles.reserve(edges.size());

    const auto faces = findQuadFaces(edges, vertices.size());
    if (faces.empty())
    {
        for (const auto& edge : edges)
        {
            if (edge.getFirst() >= vertices.size() || edge.getSecond() >= vertices.size())
                continue;
            const auto& a = vertices[edge.getFirst()];
            const auto& b = vertices[edge.getSecond()];
            if (a.getW() == 0.0 || b.getW() == 0.0)
                continue;
            if (!std::isfinite(a.getX()) || !std::isfinite(a.getY()) || !std::isfinite(a.getZ()) ||
                !std::isfinite(b.getX()) || !std::isfinite(b.getY()) || !std::isfinite(b.getZ()))
                continue;
            visibleEdges.emplace_back(a, b);
        }
        return;
    }

    for (const auto& face : faces)
    {
        const auto& a = vertices[face[0]];
        const auto& b = vertices[face[1]];
        const auto& c = vertices[face[2]];
        const auto& d = vertices[face[3]];
        if (a.getW() == 0.0 || b.getW() == 0.0 || c.getW() == 0.0 || d.getW() == 0.0)
            continue;
        triangles.push_back({a, b, c});
        triangles.push_back({a, c, d});
    }

    if (triangles.size() > 12000)
    {
        for (const auto& edge : edges)
        {
            if (edge.getFirst() >= vertices.size() || edge.getSecond() >= vertices.size())
                continue;
            const auto& a = vertices[edge.getFirst()];
            const auto& b = vertices[edge.getSecond()];
            if (a.getW() == 0.0 || b.getW() == 0.0)
                continue;
            visibleEdges.emplace_back(a, b);
        }
        return;
    }

    constexpr double eps = 1e-5;
    for (const auto& edge : edges)
    {
        if (edge.getFirst() >= vertices.size() || edge.getSecond() >= vertices.size())
            continue;

        const auto& v1 = vertices[edge.getFirst()];
        const auto& v2 = vertices[edge.getSecond()];
        if (v1.getW() == 0.0 || v2.getW() == 0.0)
            continue;

        const double dx = v2.getX() - v1.getX();
        const double dy = v2.getY() - v1.getY();
        const int rawSteps = std::max(8, static_cast<int>(std::ceil(std::max(std::abs(dx), std::abs(dy)))));
        const int steps = std::min(rawSteps, 140);
        std::vector<Vertex> run;
        run.reserve(static_cast<size_t>(steps) + 1);

        for (int i = 0; i <= steps; ++i)
        {
            const double t = static_cast<double>(i) / static_cast<double>(steps);
            const double x = v1.getX() + (v2.getX() - v1.getX()) * t;
            const double y = v1.getY() + (v2.getY() - v1.getY()) * t;
            const double z = v1.getZ() + (v2.getZ() - v1.getZ()) * t;
            if (!std::isfinite(x) || !std::isfinite(y) || !std::isfinite(z))
            {
                appendVisibleRun(visibleEdges, run);
                run.clear();
                continue;
            }

            bool hidden = false;
            for (const auto& tri : triangles)
            {
                double wa = 0.0, wb = 0.0, wc = 0.0;
                if (!pointInTriangle(x, y, tri.a, tri.b, tri.c, wa, wb, wc))
                    continue;
                const double zFace = wa * tri.a.getZ() + wb * tri.b.getZ() + wc * tri.c.getZ();
                if (zFace < z - eps)
                {
                    hidden = true;
                    break;
                }
            }
            const bool isVisible = !hidden;
            if (isVisible)
                run.emplace_back(x, y, z);
            else
            {
                appendVisibleRun(visibleEdges, run);
                run.clear();
            }
        }
        appendVisibleRun(visibleEdges, run);
    }
}
