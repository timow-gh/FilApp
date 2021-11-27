#ifndef FILAPP_LINERENDERABLE_HPP
#define FILAPP_LINERENDERABLE_HPP

#include <FilAppInterfaces/Vertex.hpp>
#include <filapp_export.h>
#include <utility>
#include <vector>

namespace FilApp
{
class FILAPP_EXPORT LineRenderable
{
  public:
    LineRenderable(std::vector<Vertex> vertices, std::vector<uint16_t> indices)
        : m_vertices(std::move(vertices)), m_indices(std::move(indices))
    {
    }

    static LineRenderable create(const Vertex& start, const Vertex& end);
    static LineRenderable create(std::vector<Vertex> vertices);

    [[nodiscard]] const std::vector<Vertex>& getVertices() const
    {
        return m_vertices;
    }
    [[nodiscard]] const std::vector<uint16_t>& getIndices() const
    {
        return m_indices;
    }

  private:
    std::vector<Vertex> m_vertices;
    std::vector<uint16_t> m_indices;
};
} // namespace FilApp

#endif // FILAPP_LINERENDERABLE_HPP
