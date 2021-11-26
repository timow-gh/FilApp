#ifndef FILAPP_POINTRENDERABLE_HPP
#define FILAPP_POINTRENDERABLE_HPP

#include "Vertex.hpp"
#include "filapp_export.h"
#include <utility>
#include <vector>

namespace FilApp
{
class FILAPP_EXPORT PointRenderable
{
  public:
    PointRenderable(std::vector<Vertex> vertices,
                    std::vector<uint16_t> indices,
                    std::vector<float_t> pointSizes)
        : m_vertices(std::move(vertices))
        , m_indices(std::move(indices))
        , m_pointSizes(std::move(pointSizes))
    {
    }

    static PointRenderable create(const Vertex& vertex, float_t pointSize);
    static PointRenderable create(std::vector<Vertex> vertices,
                                  float_t pointSize);
    static PointRenderable create(std::vector<Vertex> vertices,
                                  std::vector<float_t> pointSizes);

    [[nodiscard]] const std::vector<Vertex>& getVertices() const
    {
        return m_vertices;
    }
    [[nodiscard]] const std::vector<uint16_t>& getIndices() const
    {
        return m_indices;
    }
    [[nodiscard]] const std::vector<float_t>& getPointSizes() const
    {
        return m_pointSizes;
    }

  private:
    std::vector<Vertex> m_vertices;
    std::vector<uint16_t> m_indices;
    std::vector<float_t> m_pointSizes;
};
} // namespace FilApp

#endif // FILAPP_POINTRENDERABLE_HPP
