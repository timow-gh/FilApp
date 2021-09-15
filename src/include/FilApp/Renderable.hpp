#ifndef FILAPP_RENDERABLE_HPP
#define FILAPP_RENDERABLE_HPP

#include "FilApp/Vertex.hpp"
#include <utility>
#include <vector>

namespace FilApp
{
class FILAPP_EXPORT Renderable
{
  public:
    Renderable() = default;
    Renderable(std::vector<Vertex>&& vertices, std::vector<uint16_t>&& indices)
        : m_vertices(std::move(vertices)), m_indices(std::move(indices))
    {
    }

    const std::vector<Vertex>& getVertices() const { return m_vertices; }
    const std::vector<uint16_t>& getIndices() const { return m_indices; }

  private:
    std::vector<Vertex> m_vertices;
    std::vector<uint16_t> m_indices;
};
} // namespace FilApp

#endif // FILAPP_RENDERABLE_HPP
