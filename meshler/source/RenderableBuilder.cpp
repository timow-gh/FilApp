#include <Geometry/HalfedgeMesh/HalfedgeIndices.hpp>
#include <Geometry/HalfedgeMesh/HalfedgeMesh.hpp>
#include <Geometry/HalfedgeMesh/TriangleIndices.hpp>
#include <Geometry/HalfedgeMeshBuilder/MeshBuilder.hpp>
#include <Graphics/Renderables/LineRenderable.hpp>
#include <Graphics/Renderables/PointRenderable.hpp>
#include <Graphics/Renderables/TriangleRenderable.hpp>
#include <Graphics/Vertex.hpp>
#include <Graphics/View.hpp>
#include <Meshler/GeometryElements/GeometryElements.hpp>
#include <Meshler/GeometryElements/MCone.hpp>
#include <Meshler/GeometryElements/MCuboid.hpp>
#include <Meshler/GeometryElements/MCylinder.hpp>
#include <Meshler/GeometryElements/MGrid.hpp>
#include <Meshler/GeometryElements/MSegments.hpp>
#include <Meshler/GeometryElements/MSphere.hpp>
#include <Meshler/PresenterConfig.hpp>
#include <Meshler/PresenterUtils.hpp>
#include <Meshler/RenderableBuilder.hpp>

namespace Meshler
{
void RenderableBuilder::add(const MSphere& sphere)
{
  m_spheres.push_back(sphere);
}
void RenderableBuilder::add(const MCone& cone)
{
  m_cones.push_back(cone);
}
void RenderableBuilder::add(const MCylinder& cylinder)
{
  m_cylinders.push_back(cylinder);
}
void RenderableBuilder::add(const MSegments& segments)
{
  m_segments.push_back(segments);
}
void RenderableBuilder::add(const MCuboid& cuboid)
{
  m_cuboids.push_back(cuboid);
}
void RenderableBuilder::add(const MGrid& grid)
{
  m_grids.push_back(grid);
}
void RenderableBuilder::setPresenterConfig(const PresenterConfig& presenterConfig)
{
  m_presenterConfig = presenterConfig;
}
template <typename TRenderable>
void RenderableBuilder::addRenderable(TRenderable&& renderable)
{
  auto& view = m_view.get();
  auto triangleRenderableId = view.addRenderable(std::forward<TRenderable>(renderable));
  m_renderableIds.push_back(triangleRenderableId);
}
template <typename TGeomElem>
void RenderableBuilder::buildMesh(const TGeomElem& geomElem)
{
  auto presenterConfig = m_presenterConfig.get();

  Geometry::MeshBuilder meshBuilder{Geometry::MeshBuilderConfig{presenterConfig.polarCount, presenterConfig.azimuthCount}};
  auto mesh = meshBuilder.build(geomElem.getGeometryElement());

  buildRenderable(*mesh);
}
template <>
void RenderableBuilder::buildMesh(const MSegments& geomElem)
{
  auto presenterConfig = m_presenterConfig.get();
  addRenderable(Graphics::LineRenderable::create(buildSegmentVertices(geomElem.getSegments())));
}
template <>
void RenderableBuilder::buildMesh(const MGrid& geomElem)
{
  auto presenterConfig = m_presenterConfig.get();
  addRenderable(Graphics::LineRenderable::create(buildSegmentVertices(geomElem.calcGridSegments())));
}
Core::TVector<Graphics::RenderableId> RenderableBuilder::build()
{
  for (const MSphere& geomElem: m_spheres)
    buildMesh(geomElem);
  for (const MCone& geomElem: m_cones)
    buildMesh(geomElem);
  for (const MCylinder& geomElem: m_cylinders)
    buildMesh(geomElem);
  for (const MSegments& geomElem: m_segments)
    buildMesh(geomElem);
  for (const MCuboid& geomElem: m_cuboids)
    buildMesh(geomElem);
  for (const MGrid& geomElem: m_grids)
    buildMesh(geomElem);

  return m_renderableIds;
}
void RenderableBuilder::buildRenderable(const Geometry::HalfedgeMesh<double_t, std::size_t>& mesh)
{
  buildLineRenderable(mesh);
  buildTriableRenderable(mesh);
}
void RenderableBuilder::buildLineRenderable(const Geometry::HalfedgeMesh<double_t, std::size_t>& mesh)
{
  auto presenterConfig = m_presenterConfig.get();

  if (presenterConfig.meshDrawType == MeshDrawType::WIRED || presenterConfig.meshDrawType == MeshDrawType::SURFACE_WIRED)
    addRenderable(Graphics::LineRenderable::create(segmentGraphicsVertices(mesh)));
}
void RenderableBuilder::buildTriableRenderable(const Geometry::HalfedgeMesh<double_t, std::size_t>& mesh)
{
  auto presenterConfig = m_presenterConfig.get();

  if (presenterConfig.meshDrawType == MeshDrawType::WIRED)
    return;

  if (presenterConfig.meshDrawType == MeshDrawType::SURFACE_WIRED || presenterConfig.meshDrawType == MeshDrawType::SURFACE)
    addRenderable(createTriangleRenderable(mesh));
}
Core::TVector<Graphics::Vertex> RenderableBuilder::buildSegmentVertices(const Core::TVector<Geometry::Segment3d>& segments) const
{
  auto& presenterConfig = m_presenterConfig.get();
  Core::TVector<Graphics::Vertex> vertices;
  for (const auto& segment: segments)
  {
    vertices.push_back(vecToVertex(segment.getSource(), presenterConfig.lineColor));
    vertices.push_back(vecToVertex(segment.getTarget(), presenterConfig.lineColor));
  }
  return vertices;
}
Core::TVector<Graphics::Vertex> RenderableBuilder::segmentGraphicsVertices(const Geometry::HalfedgeMesh<double_t>& heMesh) const
{
  auto& presenterConfig = m_presenterConfig.get();

  const auto segIndices = Geometry::calcMeshSegmentIndices(heMesh);
  Core::TVector<Graphics::Vertex> result;
  result.reserve(segIndices.size());

  using VertexIndex_t = Geometry::HalfedgeMesh<double_t>::VertexIndex_t;
  for (const auto& segmentIndices: segIndices)
  {
    result.push_back(vecToVertex(heMesh.getVertex(VertexIndex_t(static_cast<std::size_t>(segmentIndices.source))).getVector(),
                                 presenterConfig.lineColor));
    result.push_back(vecToVertex(heMesh.getVertex(VertexIndex_t(static_cast<std::size_t>(segmentIndices.target))).getVector(),
                                 presenterConfig.lineColor));
  }
  return result;
}
Graphics::LineRenderable RenderableBuilder::createLineRenderables(const Core::TVector<Geometry::Segment3d>& segments) const
{
  std::uint32_t lineColor = m_presenterConfig.get().lineColor;
  Core::TVector<Graphics::Vertex> vertices;
  for (const auto& segment: segments)
  {
    vertices.push_back(vecToVertex(segment.getSource(), lineColor));
    vertices.push_back(vecToVertex(segment.getTarget(), lineColor));
  }

  return Graphics::LineRenderable::create(std::move(vertices));
}
Graphics::TriangleRenderable RenderableBuilder::createTriangleRenderable(const Geometry::HalfedgeMesh<double_t>& halfedgeMesh) const
{
  std::uint32_t faceColor = m_presenterConfig.get().faceColor;

  Core::TVector<Graphics::Vertex> vertices;
  for (const auto& vec: halfedgeMesh.meshPoints.getPoints())
    vertices.push_back(vecToVertex(vec, faceColor));

  return {std::move(vertices), Geometry::calcTriangleIndices<double_t, std::size_t, uint16_t>(halfedgeMesh.facets)};
}
} // namespace Meshler