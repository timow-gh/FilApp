#ifndef FILAPP_RENDERABLE_HPP
#define FILAPP_RENDERABLE_HPP

#include "Vertex.hpp"
#include <filapp_export.h>
#include <utility>
#include <vector>

namespace FilApp
{
class FILAPP_EXPORT Renderable
{
  public:
    enum class RenderableType
    {
        POINTS,
        TRIANGLES
    };

    Renderable() = default;
    Renderable(std::vector<Vertex>&& vertices,
               std::vector<uint16_t>&& indices,
               RenderableType renderableType)
        : m_vertices(std::move(vertices))
        , m_indices(std::move(indices))
        , m_renderableType(renderableType)
    {
    }

    const std::vector<Vertex>& getVertices() const { return m_vertices; }
    const std::vector<uint16_t>& getIndices() const { return m_indices; }
    RenderableType getRenderableType() const { return m_renderableType; }

  private:
    std::vector<Vertex> m_vertices;
    std::vector<uint16_t> m_indices;
    RenderableType m_renderableType;
};
} // namespace FilApp

#endif // FILAPP_RENDERABLE_HPP
