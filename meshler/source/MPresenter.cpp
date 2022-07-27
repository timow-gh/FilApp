#include <Core/Utils/Assert.hpp>
#include <Graphics/GraphicsController.hpp>
#include <Graphics/InputEvents/InputEventDispatcher.hpp>
#include <Graphics/InputEvents/RayPickEventDispatcher.hpp>
#include <Graphics/Vec.hpp>
#include <Graphics/Vertex.hpp>
#include <Graphics/View.hpp>
#include <Meshler/GeometryElements/MCone.hpp>
#include <Meshler/GeometryElements/MCuboid.hpp>
#include <Meshler/GeometryElements/MCylinder.hpp>
#include <Meshler/GeometryElements/MGrid.hpp>
#include <Meshler/GeometryElements/MSegments.hpp>
#include <Meshler/GeometryElements/MSphere.hpp>
#include <Meshler/MPresenter.hpp>
#include <Meshler/RenderableBuilder.hpp>

namespace Meshler
{
MPresenter::MPresenter(Graphics::View& mainView) : m_view(mainView)
{
}

void MPresenter::registerListener(Graphics::GraphicsController* meshlerController)
{
    registerInputEventListener(dynamic_cast<Graphics::InputEventListener*>(meshlerController));
    registerRayPickEventListener(dynamic_cast<Graphics::RayPickEventListener*>(meshlerController));
}

void MPresenter::removeListener(Graphics::GraphicsController* meshlerController)
{
    removeInputEventListener(dynamic_cast<Graphics::InputEventListener*>(meshlerController));
    removeRayPickEventListener(dynamic_cast<Graphics::RayPickEventListener*>(meshlerController));
}

void MPresenter::registerInputEventListener(Graphics::InputEventListener* inputEventListener)
{
    m_view.get().getInputEventDispatcher().registerInputEventListener(inputEventListener);
}

void MPresenter::removeInputEventListener(Graphics::InputEventListener* inputEventListener)
{
    m_view.get().getInputEventDispatcher().removeInputEventListener(inputEventListener);
}

void MPresenter::registerRayPickEventListener(Graphics::RayPickEventListener* rayPickEventListener)
{
    m_view.get().getRayPickEventDispatcher().registerRayPickEventListener(rayPickEventListener);
}

void MPresenter::removeRayPickEventListener(Graphics::RayPickEventListener* rayPickEventListener)
{
    m_view.get().getRayPickEventDispatcher().removeRayPickEventListener(rayPickEventListener);
}

void MPresenter::onAdd(const MSphere& meshlerSphere)
{
    onAddImpl(meshlerSphere);
}

void MPresenter::onAdd(const MCone& meshlerCone)
{
    onAddImpl(meshlerCone);
}

void MPresenter::onAdd(const MCylinder& meshlerCylinder)
{
    onAddImpl(meshlerCylinder);
}

void MPresenter::onAdd(const MSegments& meshlerSegments)
{
    onAddImpl(meshlerSegments);
}

void MPresenter::onAdd(const MCuboid& meshlerCuboid)
{
    onAddImpl(meshlerCuboid);
}

void MPresenter::onAdd(const MGrid& meshlerGrid)
{
    onAddImpl(meshlerGrid);
}

void MPresenter::onRemove(const FGuid& fGuid)
{
    auto iter = m_fGuidRenderableMapping.find(fGuid);
    if (iter != m_fGuidRenderableMapping.end())
    {
        for (const Graphics::RenderableId id: iter->second)
            m_view.get().removeRenderable(id);
        m_fGuidRenderableMapping.erase(iter);
    }
}

void MPresenter::onUpdate(const MCylinder& meshlerCylinder)
{
    onUpdateImpl(meshlerCylinder);
}

void MPresenter::onUpdate(const MCone& meshlerCone)
{
    onUpdateImpl(meshlerCone);
}

void MPresenter::onUpdate(const MSegments& meshlerSegments)
{
    onUpdateImpl(meshlerSegments);
}

void MPresenter::onUpdate(const MSphere& meshlerSphere)
{
    onUpdateImpl(meshlerSphere);
}

void MPresenter::onUpdate(const MCuboid& meshlerCuboid)
{
    onUpdateImpl(meshlerCuboid);
}

void MPresenter::onUpdate(const MGrid& meshlerGrid)
{
    onUpdateImpl(meshlerGrid);
}

void MPresenter::onPositionChanged(const PositionEvent& positionEvent)
{
    auto iter = m_fGuidRenderableMapping.find(positionEvent.fGuid);
    CORE_POSTCONDITION_DEBUG_ASSERT((iter != m_fGuidRenderableMapping.end()),
                                    "Renderable not found.");
    CORE_POSTCONDITION_DEBUG_ASSERT(!iter->second.empty(), "Renderable mapping is empty.");

    if (iter != m_fGuidRenderableMapping.cend())
        for (const Graphics::RenderableId& id: iter->second)
            m_view.get().updatePosition(
                id,
                Graphics::Vec3(static_cast<float_t>(positionEvent.position[0]),
                               static_cast<float_t>(positionEvent.position[1]),
                               static_cast<float_t>(positionEvent.position[2])));
}

template <typename TGeomElement>
void MPresenter::onAddImpl(const TGeomElement& element)
{
    RenderableBuilder rBuilder{m_view.get(), m_presenterConfig};
    rBuilder.add(element);
    auto renderableIds = rBuilder.build();
    m_fGuidRenderableMapping.emplace(element.getFGuid(), renderableIds);
}

} // namespace Meshler