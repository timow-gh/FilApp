#ifndef FILAPP_FLOWMESHCONETRAITS_HPP
#define FILAPP_FLOWMESHCONETRAITS_HPP

#include <Core/Utils/Compiler.hpp>
#include <FlowMesh/GeometryElements/FlowMeshCone.hpp>
#include <FlowMesh/GeometryElements/FlowMeshGeometryConfigBase.hpp>
#include <FlowMesh/GeometryElements/FlowMeshGeometryTraits.hpp>
#include <LinAl/LinearAlgebra.hpp>

namespace FlowMesh
{

template <typename T>
struct ConeTraitsConfig
{
    LinAl::Vec3<T> circleMidPoint{0, 0, 0};
    T radius{1.0};
    LinAl::Vec3<T> peak{0, 0, 2};
    FlowMeshGeometryConfigBase baseConfig;
};

template <typename T>
struct FlowMeshGeometryTraits<FlowMeshCone, ConeTraitsConfig<T>>
{
    CORE_NODISCARD static FlowMeshCone create(const ConeTraitsConfig<T>& config)
    {
        return FlowMeshCone{Geometry::Cone<T>{config.circleMidPoint, config.peak, config.radius},
                            newFGuid(),
                            config.baseConfig};
    }
};

} // namespace FlowMesh

#endif // FILAPP_FLOWMESHCONETRAITS_HPP
