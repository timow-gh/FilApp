#include <Core/Utils/Assert.hpp>
#include <Geometry/HalfedgeMeshBuilder/ConeMeshBuilder.hpp>
#include <Geometry/HalfedgeMeshBuilder/CuboidMeshBuilder.hpp>
#include <Geometry/HalfedgeMeshBuilder/CylinderMeshBuilder.hpp>
#include <Geometry/HalfedgeMeshBuilder/SphereMeshBuilder.hpp>
#include <Graphics/Vec.hpp>
#include <Graphics/Vertex.hpp>
#include <Meshler/GeometryElements/MCylinder.hpp>
#include <Meshler/MPresenter.hpp>
#include <Meshler/PresenterUtils.hpp>

namespace Meshler
{
MPresenter::MPresenter(Graphics::View* mainView) : m_view(mainView)
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
    m_view->getInputEventDispatcher().registerInputEventListener(inputEventListener);
}

void MPresenter::removeInputEventListener(Graphics::InputEventListener* inputEventListener)
{
    m_view->getInputEventDispatcher().removeInputEventListener(inputEventListener);
}

void MPresenter::registerRayPickEventListener(Graphics::RayPickEventListener* rayPickEventListener)
{
    m_view->getRayPickEventDispatcher().registerRayPickEventListener(rayPickEventListener);
}

void MPresenter::removeRayPickEventListener(Graphics::RayPickEventListener* rayPickEventListener)
{
    m_view->getRayPickEventDispatcher().removeRayPickEventListener(rayPickEventListener);
}

Graphics::TriangleRenderable
MPresenter::createTriangleRenderable(const Geometry::HalfedgeMesh<double_t>& halfedgeMesh,
                                     std::uint32_t faceColor)
{
    Core::TVector<Graphics::Vertex> vertices;
    for (const auto& vec: halfedgeMesh.getVertexPoints())
        vertices.push_back(vecToVertex(vec, faceColor));

    return {std::move(vertices),
            Geometry::calcTriangleIndices<double_t, uint16_t>(halfedgeMesh.getFacets())};
}

Graphics::LineRenderable
MPresenter::createLineRenderables(const Core::TVector<Geometry::Segment3d>& segments,
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

void MPresenter::onAdd(const MSphere& meshlerSphere)
{
    std::unique_ptr<Geometry::HalfedgeMesh<double_t>> sphereMesh =
        Geometry::SphereMeshBuilder<double_t>()
            .setPolarCount(m_presenterConfig.spherePolarCount)
            .setAzimuthCount(m_presenterConfig.sphereAzimuthCount)
            .setSphere(meshlerSphere.getGeometryElement())
            .build();

    const auto& segIndices = Geometry::calcMeshSegmentIndices(*sphereMesh);
    Core::TVector<Graphics::Vertex> graphicsVertices;
    graphicsVertices.reserve(segIndices.size());
    segmentGraphicsVertices(*sphereMesh, segIndices, graphicsVertices);

    auto verticesId = m_view->addRenderable(Graphics::LineRenderable::create(graphicsVertices));
    auto sphereId =
        m_view->addRenderable(createTriangleRenderable(*sphereMesh, m_presenterConfig.faceColor));

    m_fGuidRenderableMapping.emplace(meshlerSphere.getFGuid(),
                                     Core::TVector<Graphics::RenderableId>{verticesId, sphereId});
}

void MPresenter::onAdd(const MCone& meshlerCone)
{
    auto coneMesh = Geometry::ConeMeshBuilder<double_t>()
                        .setCone((meshlerCone.getGeometryElement()))
                        .setAzimuthCount(m_presenterConfig.coneAzimuthCount)
                        .build();

    const auto& segIndices = Geometry::calcMeshSegmentIndices(*coneMesh);
    Core::TVector<Graphics::Vertex> graphicsVertices;
    graphicsVertices.reserve(segIndices.size());
    segmentGraphicsVertices(*coneMesh, segIndices, graphicsVertices);

    auto verticesId = m_view->addRenderable(Graphics::LineRenderable::create(graphicsVertices));
    auto coneId =
        m_view->addRenderable(createTriangleRenderable(*coneMesh, m_presenterConfig.faceColor));

    m_fGuidRenderableMapping.emplace(meshlerCone.getFGuid(),
                                     Core::TVector<Graphics::RenderableId>{verticesId, coneId});
}

void MPresenter::onAdd(const MCylinder& meshlerCylinder)
{
    auto cylinderMesh = Geometry::CylinderMeshBuilder<double_t>()
                            .setCylinder(meshlerCylinder.getGeometryElement())
                            .setAzimuthCount(m_presenterConfig.cylinderAzimuthCount)
                            .build();

    const auto& segIndices = Geometry::calcMeshSegmentIndices(*cylinderMesh);
    Core::TVector<Graphics::Vertex> graphicsVertices;
    graphicsVertices.reserve(segIndices.size());
    segmentGraphicsVertices(*cylinderMesh, segIndices, graphicsVertices);

    auto verticesId = m_view->addRenderable(Graphics::LineRenderable::create(graphicsVertices));
    auto coneId =
        m_view->addRenderable(createTriangleRenderable(*cylinderMesh, m_presenterConfig.faceColor));

    m_fGuidRenderableMapping.emplace(meshlerCylinder.getFGuid(),
                                     Core::TVector<Graphics::RenderableId>{verticesId, coneId});
}

void MPresenter::onAdd(const MSegments& meshlerSegments)
{
    auto segmentsId = m_view->addRenderable(
        createLineRenderables(meshlerSegments.getSegments(), m_presenterConfig.lineColor));
    m_fGuidRenderableMapping.emplace(meshlerSegments.getFGuid(),
                                     Core::TVector<Graphics::RenderableId>{segmentsId});
}

void MPresenter::onAdd(const MCuboid& meshlerCuboid)
{
    auto cuboidMesh = Geometry::CuboidMeshBuilder<double_t>()
                          .setCuboid(meshlerCuboid.getGeometryElement())
                          .build();

    const auto& segIndices = Geometry::calcMeshSegmentIndices(*cuboidMesh);

    Core::TVector<Graphics::Vertex> graphicsVertices;
    graphicsVertices.reserve(segIndices.size());
    segmentGraphicsVertices(*cuboidMesh, segIndices, graphicsVertices);

    auto verticesId = m_view->addRenderable(Graphics::LineRenderable::create(graphicsVertices));
    auto cuboidId =
        m_view->addRenderable(createTriangleRenderable(*cuboidMesh, m_presenterConfig.faceColor));

    m_fGuidRenderableMapping.emplace(meshlerCuboid.getFGuid(),
                                     Core::TVector<Graphics::RenderableId>{verticesId, cuboidId});
}

void MPresenter::onAdd(const MGrid& meshlerGrid)
{
    auto segmentsId = m_view->addRenderable(
        createLineRenderables(meshlerGrid.getSegments(), m_presenterConfig.lineColor));

    auto result =
        m_fGuidRenderableMapping.emplace(meshlerGrid.getFGuid(),
                                         Core::TVector<Graphics::RenderableId>{segmentsId});
    CORE_POSTCONDITION_DEBUG_ASSERT(result.second, "GeometryElement already exists.");
}

void MPresenter::onRemove(const FGuid& fGuid)
{
    auto iter = m_fGuidRenderableMapping.find(fGuid);
    if (iter != m_fGuidRenderableMapping.end())
    {
        for (const Graphics::RenderableId id: iter->second)
            m_view->removeRenderable(id);
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
            m_view->updatePosition(id,
                                   Graphics::Vec3(static_cast<float_t>(positionEvent.position[0]),
                                                  static_cast<float_t>(positionEvent.position[1]),
                                                  static_cast<float_t>(positionEvent.position[2])));
}

void MPresenter::setIdleAnimation(const Graphics::Vec3& rotationAxis)
{
    for (const auto id: m_view->getRenderableIdentifiers())
        m_view->addRotationAnimation(id, rotationAxis);
}

void MPresenter::segmentGraphicsVertices(const Geometry::HalfedgeMesh<double_t>& heMesh,
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

} // namespace Meshler