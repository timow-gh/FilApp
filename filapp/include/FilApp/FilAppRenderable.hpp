#ifndef FILAPP_FILAPPRENDERABLE_HPP
#define FILAPP_FILAPPRENDERABLE_HPP

#include <Core/Utils/Warnings.h>
DISABLE_ALL_WARNINGS
#include <filament/Engine.h>
#include <filament/IndexBuffer.h>
#include <filament/Material.h>
#include <filament/MaterialInstance.h>
#include <filament/RenderableManager.h>
#include <filament/TransformManager.h>
#include <filament/VertexBuffer.h>
#include <utils/EntityManager.h>
ENABLE_ALL_WARNINGS
#include <filapp_export.h>
#include <memory>

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

  bool operator<(const FilAppRenderable& rhs) const { return renderableEntity < rhs.renderableEntity; }
  bool operator>(const FilAppRenderable& rhs) const { return rhs < *this; }
  bool operator<=(const FilAppRenderable& rhs) const { return !(rhs < *this); }
  bool operator>=(const FilAppRenderable& rhs) const { return !(*this < rhs); }

  bool operator==(const FilAppRenderable& rhs) const { return renderableEntity == rhs.renderableEntity; }
  bool operator!=(const FilAppRenderable& rhs) const { return !(rhs == *this); }

  void updatePosition(filament::math::float3 position) const
  {
    auto& tcm = engine->getTransformManager();
    auto instance = tcm.getInstance(renderableEntity);
    auto trafo = tcm.getTransform(instance);
    filament::math::float4& matTranslation = trafo[3];
    matTranslation = filament::math::float4{position, 1};
    tcm.setTransform(instance, trafo);
  }

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

} // namespace FilApp

#endif // FILAPP_FILAPPRENDERABLE_HPP
