#include <Core/Utils/Assert.hpp>
#include <Core/Utils/Warnings.h>
#include <FilApp/FilAppConversion.hpp>
#include <FilApp/FilAppScene.hpp>
DISABLE_ALL_WARNINGS
#include <filament/Scene.h>
#include <filament/TransformManager.h>
ENABLE_ALL_WARNINGS

namespace FilApp
{

FilAppScene FilAppScene::create(filament::Engine* engine,
                                FilAppRenderableCreator& filAppRenderableCreator)
{
    CORE_PRECONDITION_DEBUG_ASSERT(engine, "Engine is null");
    utils::Entity globalTrafoComponent = createGlobalTrafoComponent(*engine);
    auto scene = engine->createScene();
    CORE_POSTCONDITION_ASSERT(scene, "Failed to create scene");
    return std::move(FilAppScene{engine, scene, globalTrafoComponent, filAppRenderableCreator});
}
void FilAppScene::destroy()
{
    auto& tcm = utils::EntityManager::get();
    tcm.destroy(m_globalTrafoComponent);

    clear();

    bool success = m_engine->destroy(m_scene);
    CORE_POSTCONDITION_DEBUG_ASSERT(success, "Filament scene destruction failed");
    m_scene = nullptr;
}
auto FilAppScene::add(Graphics::PointRenderable&& renderable) -> Graphics::RenderableId
{
    return addRenderable(std::move(renderable),
                         m_pointRenderables,
                         filament::RenderableManager::PrimitiveType::POINTS);
}
auto FilAppScene::add(Graphics::LineRenderable&& renderable) -> Graphics::RenderableId
{
    return addRenderable(std::move(renderable),
                         m_lineRenderables,
                         filament::RenderableManager::PrimitiveType::LINES);
}
auto FilAppScene::add(Graphics::TriangleRenderable&& renderable) -> Graphics::RenderableId
{
    return addRenderable(std::move(renderable),
                         m_triangleRenderables,
                         filament::RenderableManager::PrimitiveType::TRIANGLES);
}
void FilAppScene::remove(Graphics::RenderableId id)
{
    eraseRenderable(id);
    auto iter = std::remove_if(m_filAppRenderables.begin(),
                               m_filAppRenderables.end(),
                               [id = id, scene = m_scene](const FilAppRenderable& item)
                               {
                                   if (item.renderableEntity.getId() == id.getId())
                                   {
                                       scene->remove(item.renderableEntity);
                                       return true;
                                   }
                                   return false;
                               });
    m_filAppRenderables.erase(iter, m_filAppRenderables.end());
}
void FilAppScene::clear()
{
    for (auto& renderable: m_filAppRenderables)
    {
        remove(renderable);
        renderable.destroy();
    }
    m_filAppRenderables.clear();
}
Core::TVector<Graphics::RenderableId> FilAppScene::getRenderableIdentifiers() const
{
    Core::TVector<Graphics::RenderableId> result;
    result.reserve(m_filAppRenderables.size());
    for (const auto& filAppRenderable: m_filAppRenderables)
        result.emplace_back(filAppRenderable.renderableEntity.getId());
    return result;
}
void FilAppScene::setSkybox(filament::Skybox* skybox)
{
    m_scene->setSkybox(skybox);
}
FilAppRenderable* FilAppScene::findFilAppRenderable(Graphics::RenderableId id)

{
    if (!std::is_sorted(m_filAppRenderables.begin(), m_filAppRenderables.end()))
        std::sort(m_filAppRenderables.begin(), m_filAppRenderables.end());

    utils::Entity entity = utils::Entity::import(static_cast<int32_t>(id.getId()));
    auto iter = std::lower_bound(m_filAppRenderables.begin(),
                                 m_filAppRenderables.end(),
                                 entity,
                                 [](const FilAppRenderable& filAppRenderable, utils::Entity ent)
                                 {
                                     return filAppRenderable.renderableEntity < ent;
                                 });
    if (iter != m_filAppRenderables.cend())
        return &(*iter);
    return nullptr;
}
FilAppScene::FilAppScene(filament::Engine* engine,
                         filament::Scene* scene,
                         utils::Entity globalTrafoComponent,
                         FilAppRenderableCreator& filAppRenderableCreator)
    : m_engine(engine)
    , m_scene(scene)
    , m_globalTrafoComponent(globalTrafoComponent)
    , m_renderableCreator(filAppRenderableCreator)
{
}
Graphics::RenderableId FilAppScene::add(const FilAppRenderable& filAppRenderable)
{
    m_filAppRenderables.push_back(filAppRenderable);
    auto& renderable = m_filAppRenderables.back();
    // Setting the global to filament coordinate system transformation for
    // all renderables.
    auto& tcm = m_engine->getTransformManager();
    auto globalInstance = tcm.getInstance(m_globalTrafoComponent);
    auto renderableInstance = tcm.getInstance(renderable.renderableEntity);
    tcm.setParent(renderableInstance, globalInstance);
    m_scene->addEntity(filAppRenderable.renderableEntity);
    return Graphics::RenderableId(m_filAppRenderables.back().renderableEntity.getId());
}
Core::TVector<Graphics::RenderableId>
FilAppScene::add(const Core::TVector<FilAppRenderable>& filAppRenderables)
{
    Core::TVector<Graphics::RenderableId> renderableIds;
    for (const auto& filAppRenderable: filAppRenderables)
        renderableIds.push_back(add(filAppRenderable));
    return renderableIds;
}
void FilAppScene::remove(const FilAppRenderable& filAppRenderable)
{
    m_scene->remove(filAppRenderable.renderableEntity);
}
void FilAppScene::remove(const Core::TVector<FilAppRenderable>& filAppRenderables)
{
    for (const auto& filAppRenderable: filAppRenderables)
        remove(filAppRenderable);
}
void FilAppScene::eraseRenderable(Graphics::RenderableId id)
{
    eraseFromMap(m_pointRenderables, id);
    eraseFromMap(m_lineRenderables, id);
    eraseFromMap(m_triangleRenderables, id);
}
} // namespace FilApp