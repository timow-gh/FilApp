#ifndef GRAPHICS_POINTRENDERABLE_HPP
#define GRAPHICS_POINTRENDERABLE_HPP

#include <Graphics/Vertex.hpp>
#include <numeric>
#include <utility>
#include <vector>

namespace Graphics
{
class PointRenderable {
public:
  PointRenderable(std::vector<Vertex> vertices, std::vector<uint16_t> indices, std::vector<float_t> pointSizes)
      : m_vertices(std::move(vertices))
      , m_indices(std::move(indices))
      , m_pointSizes(std::move(pointSizes))
  {
  }

  static PointRenderable create(const Vertex& vertex, float_t pointSize);
  static PointRenderable create(std::vector<Vertex> vertices, float_t pointSize);
  static PointRenderable create(std::vector<Vertex> vertices, std::vector<float_t> pointSizes);

  CORE_NODISCARD const std::vector<Vertex>& getVertices() const { return m_vertices; }
  CORE_NODISCARD const std::vector<uint16_t>& getIndices() const { return m_indices; }
  CORE_NODISCARD const std::vector<float_t>& getPointSizes() const { return m_pointSizes; }

private:
  std::vector<Vertex> m_vertices;
  std::vector<uint16_t> m_indices;
  std::vector<float_t> m_pointSizes;
};

inline PointRenderable PointRenderable::create(const Vertex& vertex, float_t pointSize)
{
  return create(std::vector<Vertex>{vertex}, pointSize);
}

inline PointRenderable PointRenderable::create(std::vector<Vertex> vertices, float_t pointSize)
{
  const std::size_t SIZE = vertices.size();
  std::vector<uint16_t> indices(SIZE);
  std::iota(indices.begin(), indices.end(), 0);
  std::vector<float_t> pointSizes(SIZE);
  std::fill(pointSizes.begin(), pointSizes.end(), pointSize);
  return {std::move(vertices), std::move(indices), std::move(pointSizes)};
}

inline PointRenderable PointRenderable::create(std::vector<Vertex> vertices, std::vector<float_t> pointSizes)
{
  std::vector<uint16_t> indices(vertices.size());
  std::iota(indices.begin(), indices.end(), 0);
  return {std::move(vertices), std::move(indices), std::move(pointSizes)};
}

} // namespace Graphics

#endif // GRAPHICS_POINTRENDERABLE_HPP
