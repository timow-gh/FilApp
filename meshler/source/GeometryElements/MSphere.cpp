#include <Meshler/GeometryElements/MSphere.hpp>

namespace Meshler
{

MSphere::MSphere()
    : GeometryElementBase<MSphere>(FGuid(), MGeometryConfigBase{})
    , m_sphere(Geometry::Sphere<double_t>(LinAl::ZERO_VEC3D, 1.0))
{
}

MSphere::MSphere(Geometry::Sphere<double_t> sphere,
                 const FGuid& guid,
                 MGeometryConfigBase baseConfig)
    : GeometryElementBase<MSphere>(guid, baseConfig), m_sphere(std::move(sphere))
{
}

const Geometry::Sphere<double_t>& MSphere::getGeometryElement() const
{
    return m_sphere;
}

void MSphere::setGeometryElement(const Geometry::Sphere<double_t>& sphere)
{
    m_sphere = sphere;
}

} // namespace Meshler