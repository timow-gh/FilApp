#include <Core/Utils/Assert.hpp>
#include <FlowMesh/FlowMeshPresenter.hpp>
#include <FlowMesh/GeometryElements/FlowMeshCylinder.hpp>
#include <Geometry/HalfedgeMeshBuilder/ConeMeshBuilder.hpp>
#include <Geometry/HalfedgeMeshBuilder/CylinderMeshBuilder.hpp>
#include <Geometry/HalfedgeMeshBuilder/SphereMeshBuilder.hpp>
#include <GraphicsInterface/Vec.hpp>
#include <GraphicsInterface/Vertex.hpp>

namespace FlowMesh
{
FlowMeshPresenter::FlowMeshPresenter(Graphics::View* mainView) : m_view(mainView)
{
}

void FlowMeshPresenter::registerListener(Graphics::GraphicsController* flowMeshController)
{
    m_view->getInputEventDispatcher().registerListener(
        dynamic_cast<Graphics::InputEventListener*>(flowMeshController));
    m_view->getRayPickEventDispatcher().registerListener(
        dynamic_cast<Graphics::RayPickEventListener*>(flowMeshController));
}

void FlowMeshPresenter::removeListener(Graphics::GraphicsController* flowMeshController)
{
    m_view->getInputEventDispatcher().removeListener(
        dynamic_cast<Graphics::InputEventListener*>(flowMeshController));
    m_view->getRayPickEventDispatcher().removeListener(
        dynamic_cast<Graphics::RayPickEventListener*>(flowMeshController));
}

Graphics::TriangleRenderable
FlowMeshPresenter::createTriangleRenderable(const Geometry::HalfedgeMesh<double_t>& halfedgeMesh,
                                            std::uint32_t faceColor)
{
    std::vector<Graphics::Vertex> vertices;
    for (const auto& vec: halfedgeMesh.getVertexPoints())
        vertices.push_back(Graphics::Vertex{{static_cast<float_t>(vec[0]),
                                             static_cast<float_t>(vec[1]),
                                             static_cast<float_t>(vec[2])},
                                            faceColor});

    return {std::move(vertices),
            Geometry::calcTriangleIndices<double_t, uint16_t>(halfedgeMesh.getFacets())};
}

Graphics::LineRenderable
FlowMeshPresenter::createLineRenderables(const FlowMeshSegments& flowMeshSegments,
                                         std::uint32_t lineColor)
{
    Core::TVector<Graphics::Vertex> vertices;
    for (const auto& segment: flowMeshSegments.getSegments())
    {
        auto& source = segment.getSource();
        auto& target = segment.getTarget();
        vertices.push_back(Graphics::Vertex{{static_cast<float_t>(source[0]),
                                             static_cast<float_t>(source[1]),
                                             static_cast<float_t>(source[2])},
                                            lineColor});
        vertices.push_back(Graphics::Vertex{{static_cast<float_t>(target[0]),
                                             static_cast<float_t>(target[1]),
                                             static_cast<float_t>(target[2])},
                                            lineColor});
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
    std::vector<Graphics::Vertex> filAppVertices;
    filAppVertices.reserve(segIndices.size());
    segmentFilAppVertices(*sphereMesh, segIndices, filAppVertices);

    auto verticesId = m_view->addRenderable(Graphics::LineRenderable::create(filAppVertices));
    auto sphereId =
        m_view->addRenderable(createTriangleRenderable(*sphereMesh, m_presenterConfig.faceColor));

    m_fGuidRenderableMapping.emplace(flowMeshSphere.getFGuid(),
                                     std::vector<Graphics::RenderableId>{verticesId, sphereId});
}

void FlowMeshPresenter::onAdd(const FlowMeshCone& flowMeshCone)
{
    auto coneMesh = Geometry::ConeMeshBuilder<double_t>()
                        .setCone((flowMeshCone.getGeometryElement()))
                        .setAzimuthCount(m_presenterConfig.coneAzimuthCount)
                        .build();

    const auto& segIndices = Geometry::calcMeshSegmentIndices(*coneMesh);
    std::vector<Graphics::Vertex> filAppVertices;
    filAppVertices.reserve(segIndices.size());
    segmentFilAppVertices(*coneMesh, segIndices, filAppVertices);

    auto verticesId = m_view->addRenderable(Graphics::LineRenderable::create(filAppVertices));
    auto coneId =
        m_view->addRenderable(createTriangleRenderable(*coneMesh, m_presenterConfig.faceColor));

    m_fGuidRenderableMapping.emplace(flowMeshCone.getFGuid(),
                                     std::vector<Graphics::RenderableId>{verticesId, coneId});
}

void FlowMeshPresenter::onAdd(const FlowMeshCylinder& flowMeshCylinder)
{
    auto cylinderMesh = Geometry::CylinderMeshBuilder<double_t>()
                            .setCylinder(flowMeshCylinder.getGeometryElement())
                            .setAzimuthCount(m_presenterConfig.cylinderAzimuthCount)
                            .build();

    const auto& segIndices = Geometry::calcMeshSegmentIndices(*cylinderMesh);
    std::vector<Graphics::Vertex> filAppVertices;
    filAppVertices.reserve(segIndices.size());
    segmentFilAppVertices(*cylinderMesh, segIndices, filAppVertices);

    auto verticesId = m_view->addRenderable(Graphics::LineRenderable::create(filAppVertices));
    auto coneId =
        m_view->addRenderable(createTriangleRenderable(*cylinderMesh, m_presenterConfig.faceColor));

    m_fGuidRenderableMapping.emplace(flowMeshCylinder.getFGuid(),
                                     std::vector<Graphics::RenderableId>{verticesId, coneId});
}

void FlowMeshPresenter::onAdd(const FlowMeshSegments& flowMeshSegments)
{
    auto segmentsId =
        m_view->addRenderable(createLineRenderables(flowMeshSegments, m_presenterConfig.lineColor));
    m_fGuidRenderableMapping.emplace(flowMeshSegments.getFGuid(),
                                     std::vector<Graphics::RenderableId>{segmentsId});
}

void FlowMeshPresenter::onRemove(const FGuid& fGuid)
{
    auto iter = m_fGuidRenderableMapping.find(fGuid);
    if (iter != m_fGuidRenderableMapping.end())
        for (const Graphics::RenderableId id: iter->second)
            m_view->removeRenderable(id);
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

void FlowMeshPresenter::segmentFilAppVertices(
    const Geometry::HalfedgeMesh<double_t>& heMesh,
    const std::vector<Geometry::SegmentIndices>& segIndices,
    std::vector<Graphics::Vertex>& vertices) const

{
    for (const auto& segmentIndices: segIndices)
    {
        auto sPoint = heMesh.getVertex(segmentIndices.source).getPoint();
        auto tPoint = heMesh.getVertex(segmentIndices.target).getPoint();
        vertices.push_back(Graphics::Vertex{{static_cast<float_t>(sPoint[0]),
                                             static_cast<float_t>(sPoint[1]),
                                             static_cast<float_t>(sPoint[2])},
                                            m_presenterConfig.lineColor});
        vertices.push_back(Graphics::Vertex{{static_cast<float_t>(tPoint[0]),
                                             static_cast<float_t>(tPoint[1]),
                                             static_cast<float_t>(tPoint[2])},
                                            m_presenterConfig.lineColor});
    }
}

} // namespace FlowMesh