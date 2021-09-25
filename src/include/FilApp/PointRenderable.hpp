#ifndef FILAPP_POINTRENDERABLE_HPP
#define FILAPP_POINTRENDERABLE_HPP

#include "FilApp/Interfaces/Vertex.hpp"
#include "filapp_export.h"
#include <utility>
#include <vector>

namespace FilApp
{
class FILAPP_EXPORT PointRenderable
{
  public:
    PointRenderable(std::vector<Vertex> vertices, const float_t& pointSize)
        : m_vertices(std::move(vertices)), m_pointSize(pointSize)
    {
    }

    [[nodiscard]] const std::vector<Vertex>& getVertices() const
    {
        return m_vertices;
    }
    [[nodiscard]] float_t getPointSize() const { return m_pointSize; }

  private:
    std::vector<Vertex> m_vertices;
    float_t m_pointSize;
};
} // namespace FilApp

#endif // FILAPP_POINTRENDERABLE_HPP
