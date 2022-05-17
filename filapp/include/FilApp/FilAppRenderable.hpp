#ifndef FILAPP_FILAPPRENDERABLE_HPP
#define FILAPP_FILAPPRENDERABLE_HPP

#include <Core/Utils/Compiler.hpp>
#include <Graphics/Renderables/LineRenderable.hpp>
#include <Graphics/Renderables/PointRenderable.hpp>
#include <Graphics/Renderables/RendereableId.hpp>
#include <Graphics/Renderables/TriangleRenderable.hpp>
#include <Graphics/Vertex.hpp>
#include <filament/Engine.h>
#include <filament/IndexBuffer.h>
#include <filament/Material.h>
#include <filament/MaterialInstance.h>
#include <filament/RenderableManager.h>
#include <filament/VertexBuffer.h>
#include <filapp_export.h>
#include <memory>
#include <utils/EntityManager.h>

namespace Graphics
{
struct FilAppRenderable
{
    filament::Engine* engine = nullptr;
    filament::VertexBuffer* vb = nullptr;
    filament::IndexBuffer* ib = nullptr;
    filament::Material* mat = nullptr;
    filament::MaterialInstance* matInstance = nullptr;
    utils::Entity renderableEntity;

    bool operator<(const FilAppRenderable& rhs) const
    {
        return renderableEntity < rhs.renderableEntity;
    }
    bool operator>(const FilAppRenderable& rhs) const { return rhs < *this; }
    bool operator<=(const FilAppRenderable& rhs) const { return !(rhs < *this); }
    bool operator>=(const FilAppRenderable& rhs) const { return !(*this < rhs); }

    void destroy() const
    {
        auto& em = utils::EntityManager::get();
        em.destroy(renderableEntity);
        engine->destroy(renderableEntity);
        engine->destroy(vb);
        engine->destroy(ib);
        // FilAppRenderable does not own material and material instance
    }
};

} // namespace Graphics

#endif // FILAPP_FILAPPRENDERABLE_HPP
