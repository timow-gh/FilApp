#ifndef FILAPP_RENDERABLE_HPP
#define FILAPP_RENDERABLE_HPP

#include "Vertex.hpp"
#include <filament/Engine.h>
#include <filament/IndexBuffer.h>
#include <filament/Material.h>
#include <filament/RenderableManager.h>
#include <filament/VertexBuffer.h>
#include <filapp_export.h>
#include <utils/EntityManager.h>
#include <vector>

namespace FilApp
{
struct FILAPP_EXPORT Renderable
{
    filament::Engine* engine = nullptr;
    filament::VertexBuffer* vb = nullptr;
    filament::IndexBuffer* ib = nullptr;
    filament::Material* mat = nullptr;
    utils::Entity renderableEntity;

    void destroy() const
    {
        engine->destroy(renderableEntity);
        engine->destroy(mat);
        engine->destroy(vb);
        engine->destroy(ib);
    }
};

FILAPP_EXPORT Renderable
createBakedColorRenderable(const std::vector<Vertex>& vertices,
                           const std::vector<uint16_t>& indices,
                           const filament::Box& aabb,
                           filament::Engine* engine);

} // namespace FilApp

#endif // FILAPP_RENDERABLE_HPP
