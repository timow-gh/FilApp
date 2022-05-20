#ifndef MESHLER_MCONE_HPP
#define MESHLER_MCONE_HPP

#include <Meshler/MGuid.hpp>
#include <Meshler/GeometryElements/MGeometryConfigBase.hpp>
#include <Meshler/GeometryElements/GeometryElementBase.hpp>
#include <Geometry/Cone.hpp>

namespace FlowMesh
{

class MCone : public GeometryElementBase<MCone> {
    Geometry::Cone<double_t> m_cone;

  public:
    MCone();
    MCone(const Geometry::Cone<double_t>& cone,
                 const FGuid& fGuid, MGeometryConfigBase baseConfig);

    [[nodiscard]] const Geometry::Cone<double_t>& getGeometryElement() const;
};

} // namespace FlowMesh

#endif // MESHLER_MCONE_HPP
