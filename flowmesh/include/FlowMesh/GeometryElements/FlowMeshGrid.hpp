#ifndef FILAPP_FLOWMESHGRID_HPP
#define FILAPP_FLOWMESHGRID_HPP

#include <Core/Types/TVector.hpp>
#include <Core/Utils/Compiler.hpp>
#include <FlowMesh/FlowMeshGuid.hpp>
#include <FlowMesh/GeometryElements/FlowMeshGeometryConfigBase.hpp>
#include <FlowMesh/GeometryElements/GeometryElementBase.hpp>
#include <Geometry/Segment.hpp>
#include <LinAl/LinearAlgebra.hpp>

namespace FlowMesh
{

class FlowMeshGrid : public GeometryElementBase<FlowMeshGrid> {
    double_t m_minXLength{-10.0};
    double_t m_minYLength{-10.0};
    double_t m_maxXLength{10.0};
    double_t m_maxYLength{10.0};
    double_t m_stepWidth{5.0};
    double_t m_maxLength{1000.0};
    LinAl::Vec3dVector m_intersectionPoints;
    Core::TVector<Geometry::Segment3d> m_segments;

  public:
    FlowMeshGrid();
    FlowMeshGrid(const FGuid& guid,
                 double_t minXLength,
                 double_t minYLength,
                 double_t maxXLength,
                 double_t maxYLength,
                 double_t stepWidth,
                 FlowMeshGeometryConfigBase baseConfig);

    // clang-format off
    CORE_CONSTEXPR void setMinXLength(double_t minXLength) { m_minXLength = minXLength; }
    CORE_CONSTEXPR void setMinYLength(double_t minYLength) { m_minYLength = minYLength; }
    CORE_CONSTEXPR void setMaxXLength(double_t maxXLength) { m_maxXLength = maxXLength; }
    CORE_CONSTEXPR void setMaxYLength(double_t maxYLength) { m_maxYLength = maxYLength; }
    CORE_CONSTEXPR void setStepWidth(double_t stepWidth) { m_stepWidth = stepWidth; }
    CORE_CONSTEXPR void setMaxLength(double_t maxLength) { m_maxLength = maxLength; }
    // clang-format on

    void updateSegments();

    CORE_NODISCARD CORE_CONSTEXPR double_t getMinXLength() const { return m_minXLength; }
    CORE_NODISCARD CORE_CONSTEXPR double_t getMinYLength() const { return m_minYLength; }
    CORE_NODISCARD CORE_CONSTEXPR double_t getMaxXLength() const { return m_maxXLength; }
    CORE_NODISCARD CORE_CONSTEXPR double_t getMaxYLength() const { return m_maxYLength; }
    CORE_NODISCARD CORE_CONSTEXPR double_t getStepWidth() const { return m_stepWidth; }
    CORE_NODISCARD CORE_CONSTEXPR double_t getMaxLength() const { return m_maxLength; }

    CORE_NODISCARD CORE_CONSTEXPR const LinAl::Vec3dVector& getIntersectionPoints() const
    {
        return m_intersectionPoints;
    }

    CORE_NODISCARD CORE_CONSTEXPR const Core::TVector<Geometry::Segment3d>& getSegments() const
    {
        return m_segments;
    }

  private:
    CORE_NODISCARD double_t floorCoordAsMultipleOfStep(double_t coord, double_t stepWidth) const;
};

} // namespace FlowMesh

#endif // FILAPP_FLOWMESHGRID_HPP
