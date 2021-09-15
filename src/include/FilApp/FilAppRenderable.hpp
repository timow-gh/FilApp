#ifndef FILAPP_FILAPPRENDERABLE_HPP
#define FILAPP_FILAPPRENDERABLE_HPP

#include "Vertex.hpp"
#include <FilApp/Renderable.hpp>
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
struct FilAppRenderable
{
    std::unique_ptr<Renderable> renderable;
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

FilAppRenderable createBakedColorRenderable(Renderable&& renderable,
                                            const filament::Box& aabb,
                                            filament::Engine* engine);

} // namespace FilApp

#endif // FILAPP_FILAPPRENDERABLE_HPP
