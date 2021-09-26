#ifndef FILAPP_FILAPPRENDERABLE_HPP
#define FILAPP_FILAPPRENDERABLE_HPP

#include "FilApp/Interfaces/Vertex.hpp"
#include <FilApp/PointRenderable.hpp>
#include <FilApp/TriangleRenderable.hpp>
#include <filament/Engine.h>
#include <filament/IndexBuffer.h>
#include <filament/Material.h>
#include <filament/MaterialInstance.h>
#include <filament/RenderableManager.h>
#include <filament/VertexBuffer.h>
#include <filapp_export.h>
#include <memory>
#include <utils/EntityManager.h>
#include <vector>

namespace FilApp
{
struct FilAppRenderable
{
    filament::Engine* engine = nullptr;
    filament::VertexBuffer* vb = nullptr;
    filament::IndexBuffer* ib = nullptr;
    filament::Material* mat = nullptr;
    filament::MaterialInstance* matInstance = nullptr;
    utils::Entity renderableEntity;

    void destroy() const
    {
        engine->destroy(renderableEntity);
        engine->destroy(mat);
        engine->destroy(vb);
        engine->destroy(ib);
    }
};

FilAppRenderable
createBakedColorRenderable(TriangleRenderable* triangleRenderable,
                           const filament::Box& aabb,
                           filament::Engine* engine);

FilAppRenderable createBakedColorRenderable(PointRenderable* renderable,
                                            const filament::Box& aabb,
                                            filament::Engine* engine);
} // namespace FilApp

#endif // FILAPP_FILAPPRENDERABLE_HPP
