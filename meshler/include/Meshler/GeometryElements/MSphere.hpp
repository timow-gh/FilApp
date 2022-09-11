#ifndef MESHLER_MSPHERE_HPP
#define MESHLER_MSPHERE_HPP

#include <Core/Utils/Compiler.hpp>
#include <Geometry/Sphere.hpp>
#include <LinAl/LinearAlgebra.hpp>
#include <Meshler/GeometryElements/GeometryElementBase.hpp>
#include <Meshler/GeometryElements/MGeometryConfigBase.hpp>
#include <Meshler/MGuid.hpp>

namespace Meshler
{
class MSphere : public GeometryElementBase<MSphere> {
  Geometry::Sphere<double_t> m_sphere;

public:
  MSphere();
  MSphere(Geometry::Sphere<double_t> sphere, const FGuid& guid, MGeometryConfigBase baseConfig);

  CORE_NODISCARD const Geometry::Sphere<double_t>& getGeometryElement() const;
  void setGeometryElement(const Geometry::Sphere<double_t>& sphere);
};
} // namespace Meshler

#endif // MESHLER_MSPHERE_HPP
