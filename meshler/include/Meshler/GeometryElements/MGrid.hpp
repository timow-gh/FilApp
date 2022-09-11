#ifndef MESHLER_MGRID_HPP
#define MESHLER_MGRID_HPP

#include <Core/Types/TVector.hpp>
#include <Core/Utils/Assert.hpp>
#include <Core/Utils/Compiler.hpp>
#include <Geometry/Plane.hpp>
#include <Geometry/Segment.hpp>
#include <LinAl/LinearAlgebra.hpp>
#include <Meshler/GeometryElements/GeometryElementBase.hpp>
#include <Meshler/GeometryElements/MGeometryConfigBase.hpp>
#include <Meshler/MGuid.hpp>

namespace Meshler
{

struct GridCalcParameters;

class MGrid final : public GeometryElementBase<MGrid> {
  LinAl::Vec3d m_origin{0, 0, 0};
  double_t m_xMin{4};
  double_t m_yMin{4};
  double_t m_xMax{4};
  double_t m_yMax{4};
  double_t m_stepWidth{1};
  double_t m_maxDistValue{100};

public:
  MGrid() = default;

  CORE_NODISCARD CORE_CONSTEXPR double_t getStepWidth() const { return m_stepWidth; }
  void setStepWidth(double_t stepWidth);

  CORE_NODISCARD CORE_CONSTEXPR LinAl::Vec3d getOrigin() const { return m_origin; }
  CORE_CONSTEXPR void setOrigin(LinAl::Vec3d origin) { m_origin = origin; }

  CORE_NODISCARD CORE_CONSTEXPR double_t getXMin() const { return m_xMin; }
  void setXMin(double_t xMin);

  CORE_NODISCARD CORE_CONSTEXPR double_t getYMin() const { return m_yMin; }
  void setYMin(double_t yMin);

  CORE_NODISCARD CORE_CONSTEXPR double_t getXMax() const { return m_xMax; }
  void setXMax(double_t xMax);

  CORE_NODISCARD CORE_CONSTEXPR double_t getYMax() const { return m_yMax; }
  void setYMax(double_t yMax);

  CORE_NODISCARD CORE_CONSTEXPR double_t getMaxDistValue() const { return m_maxDistValue; }
  void setMaxDistValue(double_t maxDistValue);

  CORE_NODISCARD Geometry::Plane<double_t> calcPlane() const;
  CORE_NODISCARD Core::TVector<Geometry::Segment3d> calcGridSegments() const;
  CORE_NODISCARD LinAl::Vec3dVector calcIntersectionPoints() const;

private:
  CORE_NODISCARD GridCalcParameters calcGridCalcParameters() const;
  void calcGridSegments(Core::TVector<Geometry::Segment3d>& segments, LinAl::Vec3d dir, std::int64_t numberOfSteps) const;
};

} // namespace Meshler

#endif // MESHLER_MGRID_HPP
