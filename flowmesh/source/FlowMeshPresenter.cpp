#include <Core/Utils/Assert.hpp>
#include <FlowMesh/FlowMeshPresenter.hpp>
#include <FlowMesh/GeometryElements/FlowMeshCylinder.hpp>
#include <FlowMesh/PresenterUtils.hpp>
#include <Geometry/HalfedgeMeshBuilder/ConeMeshBuilder.hpp>
#include <Geometry/HalfedgeMeshBuilder/CuboidMeshBuilder.hpp>
#include <Geometry/HalfedgeMeshBuilder/CylinderMeshBuilder.hpp>
#include <Geometry/HalfedgeMeshBuilder/SphereMeshBuilder.hpp>
#include <Graphics/Vec.hpp>
#include <Graphics/Vertex.hpp>

namespace FlowMesh
{
FlowMeshPresenter::FlowMeshPresenter(Graphics::View* mainView) : m_view(mainView)
{
}

void FlowMeshPresenter::registerListener(Graphics::GraphicsController* flowMeshController)
{
    registerInputEventListener(dynamic_cast<Graphics::InputEventListener*>(flowMeshController));
    registerRayPickEventListener(dynamic_cast<Graphics::RayPickEventListener*>(flowMeshController));
}

void FlowMeshPresenter::removeListener(Graphics::GraphicsController* flowMeshController)
{
    removeInputEventListener(dynamic_cast<Graphics::InputEventListener*>(flowMeshController));
    removeRayPickEventListener(dynamic_cast<Graphics::RayPickEventListener*>(flowMeshController));
}

void FlowMeshPresenter::registerInputEventListener(Graphics::InputEventListener* inputEventListener)
{
    m_view->getInputEventDispatcher().registerInputEventListener(inputEventListener);
}

void FlowMeshPresenter::removeInputEventListener(Graphics::InputEventListener* inputEventListener)
{
    m_view->getInputEventDispatcher().removeInputEventListener(inputEventListener);
}

void FlowMeshPresenter::registerRayPickEventListener(
    Graphics::RayPickEventListener* rayPickEventListener)
{
    m_view->getRayPickEventDispatcher().registerRayPickEventListener(rayPickEventListener);
}

void FlowMeshPresenter::removeRayPickEventListener(
    Graphics::RayPickEventListener* rayPickEventListener)
{
    m_view->getRayPickEventDispatcher().removeRayPickEventListener(rayPickEventListener);
}

Graphics::TriangleRenderable
FlowMeshPresenter::createTriangleRenderable(const Geometry::HalfedgeMesh<double_t>& halfedgeMesh,
                                            std::uint32_t faceColor)
{
    Core::TVector<Graphics::Vertex> vertices;
    for (const auto& vec: halfedgeMesh.getVertexPoints())
        vertices.push_back(vecToVertex(vec, faceColor));

    return {std::move(vertices),
            Geometry::calcTriangleIndices<double_t, uint16_t>(halfedgeMesh.getFacets())};
}

Graphics::LineRenderable
FlowMeshPresenter::createLineRenderables(const Core::TVector<Geometry::Segment3d>& segments,
                                         std::uint32_t lineColor)
{
    Core::TVector<Graphics::Vertex> vertices;
    for (const auto& segment: segments)
    {
        vertices.push_back(vecToVertex(segment.getSource(), lineColor));
        vertices.push_back(vecToVertex(segment.getTarget(), lineColor));
    }

    return Graphics::LineRenderable::create(vertices);
}

void FlowMeshPresenter::onAdd(const FlowMeshSphere& flowMeshSphere)
{
    std::unique_ptr<Geometry::HalfedgeMesh<double_t>> sphereMesh =
        Geometry::SphereMeshBuilder<double_t>()
            .setPolarCount(m_presenterConfig.spherePolarCount)
            .setAzimuthCount(m_presenterConfig.sphereAzimuthCount)
            .setSphere(flowMeshSphere.getGeometryElement())
            .build();

    const auto& segIndices = Geometry::calcMeshSegmentIndices(*sphereMesh);
    Core::TVector<Graphics::Vertex> graphicsVertices;
    graphicsVertices.reserve(segIndices.size());
    segmentGraphicsVertices(*sphereMesh, segIndices, graphicsVertices);

    auto verticesId = m_view->addRenderable(Graphics::LineRenderable::create(graphicsVertices));
    auto sphereId =
        m_view->addRenderable(createTriangleRenderable(*sphereMesh, m_presenterConfig.faceColor));

    m_fGuidRenderableMapping.emplace(flowMeshSphere.getFGuid(),
                                     Core::TVector<Graphics::RenderableId>{verticesId, sphereId});
}

void FlowMeshPresenter::onAdd(const FlowMeshCone& flowMeshCone)
{
    auto coneMesh = Geometry::ConeMeshBuilder<double_t>()
                        .setCone((flowMeshCone.getGeometryElement()))
                        .setAzimuthCount(m_presenterConfig.coneAzimuthCount)
                        .build();

    const auto& segIndices = Geometry::calcMeshSegmentIndices(*coneMesh);
    Core::TVector<Graphics::Vertex> graphicsVertices;
    graphicsVertices.reserve(segIndices.size());
    segmentGraphicsVertices(*coneMesh, segIndices, graphicsVertices);

    auto verticesId = m_view->addRenderable(Graphics::LineRenderable::create(graphicsVertices));
    auto coneId =
        m_view->addRenderable(createTriangleRenderable(*coneMesh, m_presenterConfig.faceColor));

    m_fGuidRenderableMapping.emplace(flowMeshCone.getFGuid(),
                                     Core::TVector<Graphics::RenderableId>{verticesId, coneId});
}

void FlowMeshPresenter::onAdd(const FlowMeshCylinder& flowMeshCylinder)
{
    auto cylinderMesh = Geometry::CylinderMeshBuilder<double_t>()
                            .setCylinder(flowMeshCylinder.getGeometryElement())
                            .setAzimuthCount(m_presenterConfig.cylinderAzimuthCount)
                            .build();

    const auto& segIndices = Geometry::calcMeshSegmentIndices(*cylinderMesh);
    Core::TVector<Graphics::Vertex> graphicsVertices;
    graphicsVertices.reserve(segIndices.size());
    segmentGraphicsVertices(*cylinderMesh, segIndices, graphicsVertices);

    auto verticesId = m_view->addRenderable(Graphics::LineRenderable::create(graphicsVertices));
    auto coneId =
        m_view->addRenderable(createTriangleRenderable(*cylinderMesh, m_presenterConfig.faceColor));

    m_fGuidRenderableMapping.emplace(flowMeshCylinder.getFGuid(),
                                     Core::TVector<Graphics::RenderableId>{verticesId, coneId});
}

void FlowMeshPresenter::onAdd(const FlowMeshSegments& flowMeshSegments)
{
    auto segmentsId = m_view->addRenderable(
        createLineRenderables(flowMeshSegments.getSegments(), m_presenterConfig.lineColor));
    m_fGuidRenderableMapping.emplace(flowMeshSegments.getFGuid(),
                                     Core::TVector<Graphics::RenderableId>{segmentsId});
}

void FlowMeshPresenter::onAdd(const FlowMeshCuboid& flowMeshCuboid)
{
    auto cuboidMesh = Geometry::CuboidMeshBuilder<double_t>()
                          .setCuboid(flowMeshCuboid.getGeometryElement())
                          .build();

    const auto& segIndices = Geometry::calcMeshSegmentIndices(*cuboidMesh);

    Core::TVector<Graphics::Vertex> graphicsVertices;
    graphicsVertices.reserve(segIndices.size());
    segmentGraphicsVertices(*cuboidMesh, segIndices, graphicsVertices);

    auto verticesId = m_view->addRenderable(Graphics::LineRenderable::create(graphicsVertices));
    auto cuboidId =
        m_view->addRenderable(createTriangleRenderable(*cuboidMesh, m_presenterConfig.faceColor));

    m_fGuidRenderableMapping.emplace(flowMeshCuboid.getFGuid(),
                                     Core::TVector<Graphics::RenderableId>{verticesId, cuboidId});
}

void FlowMeshPresenter::onAdd(const FlowMeshGrid& flowMeshGrid)
{
    auto segmentsId = m_view->addRenderable(
        createLineRenderables(flowMeshGrid.getSegments(), m_presenterConfig.lineColor));

    auto result =
        m_fGuidRenderableMapping.emplace(flowMeshGrid.getFGuid(),
                                         Core::TVector<Graphics::RenderableId>{segmentsId});
    CORE_POSTCONDITION_DEBUG_ASSERT(result.second, "GeometryElement already exists.");
}

void FlowMeshPresenter::onRemove(const FGuid& fGuid)
{
    auto iter = m_fGuidRenderableMapping.find(fGuid);
    if (iter != m_fGuidRenderableMapping.end())
    {
        for (const Graphics::RenderableId id: iter->second)
            m_view->removeRenderable(id);
        m_fGuidRenderableMapping.erase(iter);
    }
}

void FlowMeshPresenter::onUpdate(const FlowMeshCylinder& flowMeshCylinder)
{
    onUpdateImpl(flowMeshCylinder);
}

void FlowMeshPresenter::onUpdate(const FlowMeshCone& flowMeshCone)
{
    onUpdateImpl(flowMeshCone);
}

void FlowMeshPresenter::onUpdate(const FlowMeshSegments& flowMeshSegments)
{
    onUpdateImpl(flowMeshSegments);
}

void FlowMeshPresenter::onUpdate(const FlowMeshSphere& flowMeshSphere)
{
    onUpdateImpl(flowMeshSphere);
}

void FlowMeshPresenter::onUpdate(const FlowMeshCuboid& flowMeshCuboid)
{
    onUpdateImpl(flowMeshCuboid);
}

void FlowMeshPresenter::onUpdate(const FlowMeshGrid& flowMeshGrid)
{
    onUpdateImpl(flowMeshGrid);
}

void FlowMeshPresenter::onPositionChanged(const PositionEvent& positionEvent)
{
    auto iter = m_fGuidRenderableMapping.find(positionEvent.fGuid);
    CORE_POSTCONDITION_DEBUG_ASSERT((iter != m_fGuidRenderableMapping.end()),
                                    "Renderable not found.");
    CORE_POSTCONDITION_DEBUG_ASSERT(!iter->second.empty(), "Renderable mapping is empty.");

    if (iter != m_fGuidRenderableMapping.cend())
        for (const Graphics::RenderableId& id: iter->second)
            m_view->updatePosition(id,
                                   Graphics::Vec3(static_cast<float_t>(positionEvent.position[0]),
                                                  static_cast<float_t>(positionEvent.position[1]),
                                                  static_cast<float_t>(positionEvent.position[2])));
}

void FlowMeshPresenter::setIdleAnimation(const Graphics::Vec3& rotationAxis)
{
    for (const auto id: m_view->getRenderableIdentifiers())
        m_view->addRotationAnimation(id, rotationAxis);
}

void FlowMeshPresenter::segmentGraphicsVertices(
    const Geometry::HalfedgeMesh<double_t>& heMesh,
    const Core::TVector<Geometry::SegmentIndices>& segIndices,
    Core::TVector<Graphics::Vertex>& vertices) const

{
    for (const auto& segmentIndices: segIndices)
    {
        vertices.push_back(vecToVertex(heMesh.getVertex(segmentIndices.source).getPoint(),
                                       m_presenterConfig.lineColor));
        vertices.push_back(vecToVertex(heMesh.getVertex(segmentIndices.target).getPoint(),
                                       m_presenterConfig.lineColor));
    }
}

} // namespace FlowMesh