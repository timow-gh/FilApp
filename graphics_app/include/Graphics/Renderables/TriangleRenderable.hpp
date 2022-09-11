#ifndef GRAPHICS_TRIANGLERENDERABLE_HPP
#define GRAPHICS_TRIANGLERENDERABLE_HPP

#include <Graphics/Vertex.hpp>
#include <utility>
#include <vector>

namespace Graphics
{
class TriangleRenderable {
public:
  TriangleRenderable() = default;
  TriangleRenderable(std::vector<Vertex>&& vertices, std::vector<uint16_t>&& indices)
      : m_vertices(std::move(vertices))
      , m_indices(std::move(indices))
  {
  }

  CORE_NODISCARD const std::vector<Vertex>& getVertices() const { return m_vertices; }
  CORE_NODISCARD const std::vector<uint16_t>& getIndices() const { return m_indices; }

private:
  std::vector<Vertex> m_vertices;
  std::vector<uint16_t> m_indices;
};
} // namespace Graphics

#endif // GRAPHICS_TRIANGLERENDERABLE_HPP
