#ifndef GRAPHICS_LINERENDERABLE_HPP
#define GRAPHICS_LINERENDERABLE_HPP

#include <Graphics/Vertex.hpp>
#include <cassert>
#include <utility>
#include <vector>

namespace Graphics
{
class LineRenderable {
  public:
    LineRenderable(std::vector<Vertex> vertices, std::vector<uint16_t> indices)
        : m_vertices(std::move(vertices)), m_indices(std::move(indices))
    {
    }

    static LineRenderable create(const Vertex& start, const Vertex& end);
    static LineRenderable create(std::vector<Vertex> vertices);

    CORE_NODISCARD const std::vector<Vertex>& getVertices() const { return m_vertices; }
    CORE_NODISCARD const std::vector<uint16_t>& getIndices() const { return m_indices; }

  private:
    std::vector<Vertex> m_vertices;
    std::vector<uint16_t> m_indices;
};

inline LineRenderable LineRenderable::create(const Vertex& start, const Vertex& end)
{
    return create({start, end});
}

inline LineRenderable LineRenderable::create(std::vector<Vertex> vertices)
{
    assert(vertices.size() % 2 == 0);
    std::vector<uint16_t> indices;
    indices.reserve((vertices.size()));
    const std::size_t SIZE = vertices.size();
    for (std::size_t i{1}; i <= SIZE; ++i)
        indices.push_back(i - 1);
    return {std::move(vertices), std::move(indices)};
}

} // namespace Graphics

#endif // GRAPHICS_LINERENDERABLE_HPP
