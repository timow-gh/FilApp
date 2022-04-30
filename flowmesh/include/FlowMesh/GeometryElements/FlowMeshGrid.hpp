#ifndef FILAPP_FLOWMESHGRID_HPP
#define FILAPP_FLOWMESHGRID_HPP

#include <Core/Types/TVector.hpp>
#include <FlowMesh/FlowMeshGuid.hpp>
#include <FlowMesh/GeometryElements/GeometryElementBase.hpp>
#include <Geometry/Segment.hpp>
#include <LinAl/LinearAlgebra.hpp>

namespace FlowMesh
{

class FlowMeshGrid : public GeometryElementBase<FlowMeshGrid> {
    LinAl::Vec3d m_origin{-10, -10, 0};
    LinAl::Vec3d m_widthVec{20, 0, 0};
    LinAl::Vec3d m_heightVec{0, 20, 0};
    double_t m_stepWidth{1.0};
    LinAl::Vec3dVector m_intersectionPoints;
    Core::TVector<Geometry::Segment3d> m_segments;

  public:
    FlowMeshGrid();
    FlowMeshGrid(const FGuid& guid,
                 const LinAl::Vec3d& origin,
                 const LinAl::Vec3d& widthVec,
                 const LinAl::Vec3d& heightVec,
                 double_t stepWidth);

    [[nodiscard]] const LinAl::Vec3d& getSource() const { return m_widthVec; }
    [[nodiscard]] const LinAl::Vec3d& getTarget() const { return m_heightVec; }

    void setSource(const LinAl::Vec3d& source);
    void setTarget(const LinAl::Vec3d& target);
    void setStepWidth(double_t stepWidth);

    [[nodiscard]] const LinAl::Vec3dVector& getIntersectionPoints() const;
    [[nodiscard]] const Core::TVector<Geometry::Segment3d>& getSegments() const
    {
        return m_segments;
    }

  private:
    void updateSegments();
};

} // namespace FlowMesh

#endif // FILAPP_FLOWMESHGRID_HPP
