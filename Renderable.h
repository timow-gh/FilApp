#ifndef FILAPP_RENDERABLE_H
#define FILAPP_RENDERABLE_H

#include <filament/RenderableManager.h>
#include <utils/EntityManager.h>
#include <filament/Engine.h>

namespace FilApp
{
struct Vertex
{
    filament::math::float2 position;
    uint32_t color;
};

struct Renderable
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
} // namespace FilApp

#endif // FILAPP_RENDERABLE_H
