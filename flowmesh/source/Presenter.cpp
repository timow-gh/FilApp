#include <Core/Utils/Assert.hpp>
#include <FlowMesh/GeometryElements/FlowMeshCylinder.hpp>
#include <FlowMesh/Presenter.hpp>
#include <FlowMesh/PresenterConfig.hpp>
#include <Geometry/HalfedgeMeshBuilder/ConeMeshBuilder.hpp>
#include <Geometry/HalfedgeMeshBuilder/CylinderMeshBuilder.hpp>
#include <Geometry/HalfedgeMeshBuilder/SphereMeshBuilder.hpp>
#include <GraphicsInterface/Vec.hpp>
#include <GraphicsInterface/Vertex.hpp>

namespace FlowMesh
{
Graphics::TriangleRenderable
Presenter::createTriangleRenderable(const Geometry::HalfedgeMesh<double_t>& halfedgeMesh,
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

Graphics::LineRenderable Presenter::createLineRenderables(const FlowMeshSegments& flowMeshSegments,
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

Presenter::Presenter(Graphics::View* mainView) : m_mainView(mainView)
{
}

void Presenter::add(const FlowMeshSphere& flowMeshSphere)
{
    std::unique_ptr<Geometry::HalfedgeMesh<double_t>> sphereMesh =
        Geometry::SphereMeshBuilder<double_t>()
            .setPolarCount(m_presenterConfig.spherePolarCount)
            .setAzimuthCount(m_presenterConfig.spherePolarCount)
            .setSphere(flowMeshSphere.getGeometryElement())
            .build();

    const auto& segIndices = Geometry::calcMeshSegmentIndices(*sphereMesh);
    std::vector<Graphics::Vertex> filAppVertices;
    filAppVertices.reserve(segIndices.size());
    segmentFilAppVertices(*sphereMesh, segIndices, filAppVertices);

    auto verticesId = m_mainView->addRenderable(Graphics::LineRenderable::create(filAppVertices));
    auto sphereId = m_mainView->addRenderable(
        createTriangleRenderable(*sphereMesh, m_presenterConfig.faceColor));

    m_fGuidRenderableMapping.emplace(flowMeshSphere.getFGuid(),
                                     std::vector<Graphics::RenderableId>{verticesId, sphereId});
}

void Presenter::add(const FlowMeshCone& flowMeshCone)
{
    auto coneMesh = Geometry::ConeMeshBuilder<double_t>()
                        .setCone((flowMeshCone.getCone()))
                        .setAzimuthCount(m_presenterConfig.coneAzimuthCount)
                        .build();

    const auto& segIndices = Geometry::calcMeshSegmentIndices(*coneMesh);
    std::vector<Graphics::Vertex> filAppVertices;
    filAppVertices.reserve(segIndices.size());
    segmentFilAppVertices(*coneMesh, segIndices, filAppVertices);

    auto verticesId = m_mainView->addRenderable(Graphics::LineRenderable::create(filAppVertices));
    auto coneId =
        m_mainView->addRenderable(createTriangleRenderable(*coneMesh, m_presenterConfig.faceColor));

    m_fGuidRenderableMapping.emplace(flowMeshCone.getFGuid(),
                                     std::vector<Graphics::RenderableId>{verticesId, coneId});
}

void Presenter::add(const FlowMeshCylinder& flowMeshCylinder)
{
    auto cylinderMesh = Geometry::CylinderMeshBuilder<double_t>()
                            .setCylinder(flowMeshCylinder.getCylinder())
                            .setAzimuthCount(m_presenterConfig.cylinderAzimuthCount)
                            .build();

    const auto& segIndices = Geometry::calcMeshSegmentIndices(*cylinderMesh);
    std::vector<Graphics::Vertex> filAppVertices;
    filAppVertices.reserve(segIndices.size());
    segmentFilAppVertices(*cylinderMesh, segIndices, filAppVertices);

    auto verticesId = m_mainView->addRenderable(Graphics::LineRenderable::create(filAppVertices));
    auto coneId = m_mainView->addRenderable(
        createTriangleRenderable(*cylinderMesh, m_presenterConfig.lineColor));

    m_fGuidRenderableMapping.emplace(flowMeshCylinder.getFGuid(),
                                     std::vector<Graphics::RenderableId>{verticesId, coneId});
}

void Presenter::add(const FlowMeshSegments& flowMeshSegments)
{
    auto segmentsId = m_mainView->addRenderable(
        createLineRenderables(flowMeshSegments, m_presenterConfig.lineColor));
    m_fGuidRenderableMapping.emplace(flowMeshSegments.getFGuid(),
                                     std::vector<Graphics::RenderableId>{segmentsId});
}

void Presenter::updatePosition(const FGuid& fGuid, const LinAl::Vec3d& position)
{
    auto iter = m_fGuidRenderableMapping.find(fGuid);
    CORE_POSTCONDITION_DEBUG_ASSERT((iter != m_fGuidRenderableMapping.end()),
                                    "Renderable not found.");
    CORE_POSTCONDITION_DEBUG_ASSERT(!iter->second.empty(), "Renderable mapping is empty.");

    if (iter != m_fGuidRenderableMapping.cend())
        for (const Graphics::RenderableId& id: iter->second)
            m_mainView->updatePosition(id,
                                       Graphics::Vec3(static_cast<float_t>(position[0]),
                                                      static_cast<float_t>(position[1]),
                                                      static_cast<float_t>(position[2])));
}

void Presenter::remove(const FGuid& fGuid)
{
    auto iter = m_fGuidRenderableMapping.find(fGuid);
    if (iter != m_fGuidRenderableMapping.end())
        for (const Graphics::RenderableId id: iter->second)
            m_mainView->removeRenderable(id);
}

void Presenter::setIdleAnimation(const Graphics::Vec3& rotationAxis)
{
    for (const auto id: m_mainView->getRenderableIdentifiers())
        m_mainView->addRotationAnimation(id, rotationAxis);
}

void Presenter::segmentFilAppVertices(const Geometry::HalfedgeMesh<double_t>& heMesh,
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