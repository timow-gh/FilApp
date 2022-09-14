#ifndef MESHLER_RENDERABLEBUILDER_H
#define MESHLER_RENDERABLEBUILDER_H

#include <Core/Types/TVector.hpp>
#include <Core/Utils/Compiler.hpp>
#include <Geometry/Fwd/FwdHalfedgeMesh.hpp>
#include <Graphics/Renderables/RendereableId.hpp>
#include <Meshler/GeometryElements/GeomElementContainer.hpp>
#include <functional>

namespace Graphics
{
class View;
class PointRenderable;
class LineRenderable;
class TriangleRenderable;
struct Vertex;
} // namespace Graphics

namespace Meshler
{
struct PresenterConfig;

class RenderableBuilder {
  std::reference_wrapper<Graphics::View> m_view;
  Core::TVector<Graphics::RenderableId> m_renderableIds;

  Core::TVector<std::reference_wrapper<const MSphere>> m_spheres;
  Core::TVector<std::reference_wrapper<const MCone>> m_cones;
  Core::TVector<std::reference_wrapper<const MCylinder>> m_cylinders;
  Core::TVector<std::reference_wrapper<const MSegments>> m_segments;
  Core::TVector<std::reference_wrapper<const MCuboid>> m_cuboids;
  Core::TVector<std::reference_wrapper<const MGrid>> m_grids;

  std::reference_wrapper<const PresenterConfig> m_presenterConfig;

public:
  RenderableBuilder(Graphics::View& view, const PresenterConfig& presenterConfig)
      : m_view(view)
      , m_presenterConfig(presenterConfig)
  {
  }

  void add(const MSphere& sphere);
  void add(const MCone& cone);
  void add(const MCylinder& cylinder);
  void add(const MSegments& segments);
  void add(const MCuboid& cuboid);
  void add(const MGrid& grid);

  void setPresenterConfig(const PresenterConfig& presenterConfig);

  CORE_NODISCARD Core::TVector<Graphics::RenderableId> build();

private:
  template <typename TRenderable>
  void addRenderable(TRenderable&& renderable);

  template <typename TGeomElem>
  void buildMesh(const TGeomElem& geomElem);

  void buildRenderable(const Geometry::HalfedgeMesh<double_t, std::size_t>& mesh);
  void buildLineRenderable(const Geometry::HalfedgeMesh<double_t, std::size_t>& mesh);
  void buildTriableRenderable(const Geometry::HalfedgeMesh<double_t, std::size_t>& mesh);

  CORE_NODISCARD Core::TVector<Graphics::Vertex> buildSegmentVertices(const Core::TVector<Geometry::Segment<double_t, 3>>& segments) const;

  CORE_NODISCARD Graphics::LineRenderable createLineRenderables(const Core::TVector<Geometry::Segment<double_t, 3>>& segments) const;

  CORE_NODISCARD Graphics::TriangleRenderable
  createTriangleRenderable(const Geometry::HalfedgeMesh<double_t, std::size_t>& halfedgeMesh) const;

  CORE_NODISCARD Core::TVector<Graphics::Vertex> segmentGraphicsVertices(const Geometry::HalfedgeMesh<double_t, std::size_t>& heMesh) const;
};
} // namespace Meshler

#endif // MESHLER_RENDERABLEBUILDER_H
