#ifndef FILAPP_RENDERABLE_H
#define FILAPP_RENDERABLE_H

#include <filament/Engine.h>
#include <filament/RenderableManager.h>
#include <filapp_export.h>
#include <utils/EntityManager.h>

namespace FilApp
{

struct FILAPP_EXPORT Vertex
{
    filament::math::float2 position;
    uint32_t color;
};

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
} // namespace FilApp

#endif // FILAPP_RENDERABLE_H
