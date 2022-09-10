#ifndef MESHLER_FILAPPSCENE_HPP
#define MESHLER_FILAPPSCENE_HPP

#include <Core/Types/TMap.hpp>
#include <Core/Types/TVector.hpp>
#include <Core/Utils/Warnings.h>
#include <FilApp/FilAppRenderableCreator.hpp>
#include <FilApp/FilAppScene.hpp>
#include <Graphics/Renderables/LineRenderable.hpp>
#include <Graphics/Renderables/PointRenderable.hpp>
#include <Graphics/Renderables/RendereableId.hpp>
#include <Graphics/Renderables/TriangleRenderable.hpp>
#include <optional>
DISABLE_ALL_WARNINGS
#include <utils/Entity.h>
ENABLE_ALL_WARNINGS

namespace filament
{
class Scene;
}

namespace FilApp
{

// List of objects to render.
class FilAppScene {
    filament::Engine* m_engine{nullptr};
    filament::Scene* m_scene{nullptr};
    utils::Entity m_globalTrafoComponent; // non-owning
    std::reference_wrapper<FilAppRenderableCreator> m_renderableCreator;

    Core::TMap<Graphics::RenderableId, std::unique_ptr<Graphics::PointRenderable>>
        m_pointRenderables{};
    Core::TMap<Graphics::RenderableId, std::unique_ptr<Graphics::LineRenderable>>
        m_lineRenderables{};
    Core::TMap<Graphics::RenderableId, std::unique_ptr<Graphics::TriangleRenderable>>
        m_triangleRenderables{};
    Core::TVector<FilAppRenderable> m_filAppRenderables;

  public:
    CORE_NODISCARD static FilAppScene create(filament::Engine* engine,
                                             FilAppRenderableCreator& filAppRenderableCreator);

    FilAppScene(const FilAppScene&) = delete;
    FilAppScene& operator=(const FilAppScene&) = delete;
    FilAppScene(FilAppScene&&) = default;
    FilAppScene& operator=(FilAppScene&&) = default;

    void destroy();

    CORE_NODISCARD Graphics::RenderableId add(Graphics::PointRenderable&& renderable);
    CORE_NODISCARD Graphics::RenderableId add(Graphics::LineRenderable&& renderable);
    CORE_NODISCARD Graphics::RenderableId add(Graphics::TriangleRenderable&& renderable);
    void remove(Graphics::RenderableId id);
    void clear();

    Core::TVector<Graphics::RenderableId> getRenderableIdentifiers() const;

    void setSkybox(filament::Skybox* skybox);
    CORE_NODISCARD filament::Scene* getFilamentScene() const { return m_scene; }

    CORE_NODISCARD FilAppRenderable* findFilAppRenderable(Graphics::RenderableId id);

  private:
    FilAppScene(filament::Engine* engine,
                filament::Scene* scene,
                utils::Entity globalTrafoComponent,
                FilAppRenderableCreator& filAppRenderableCreator);

    // clang-format off
    auto add(const FilAppRenderable& filAppRenderable) -> Graphics::RenderableId;
    auto add(const Core::TVector<FilAppRenderable>& filAppRenderables) -> Core::TVector<Graphics::RenderableId>;
    void remove(const FilAppRenderable& filAppRenderable);
    void remove(const Core::TVector<FilAppRenderable>& filAppRenderables);
    // clang-format on

    void eraseRenderable(Graphics::RenderableId id);

    template <typename TRenderable, typename TRenderableMap>
    CORE_NODISCARD Graphics::RenderableId
    addRenderable(TRenderable&& tRenderable,
                  TRenderableMap& tRenderableMap,
                  filament::RenderableManager::PrimitiveType primitiveType)
    {
        auto renderable = std::make_unique<TRenderable>(std::move(tRenderable));

        auto id =
            add(m_renderableCreator.get().createBakedColorRenderable(renderable->getVertices(),
                                                                     renderable->getIndices(),
                                                                     primitiveType));

        tRenderableMap.emplace(id, std::move(renderable));
        return id;
    }

    template <typename V>
    void eraseFromMap(Core::TMap<Graphics::RenderableId, V>& map, Graphics::RenderableId id)
    {
        auto idIter = map.find(id);
        if (idIter != map.end())
            map.erase(idIter);
    }
};

} // namespace FilApp

#endif // MESHLER_FILAPPSCENE_HPP
