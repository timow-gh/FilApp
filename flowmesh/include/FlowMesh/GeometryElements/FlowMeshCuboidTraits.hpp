#ifndef FILAPP_FLOWMESHCUBOIDTRAITS_HPP
#define FILAPP_FLOWMESHCUBOIDTRAITS_HPP

#include <Core/Utils/Compiler.hpp>
#include <FlowMesh/GeometryElements/FlowMeshCuboid.hpp>
#include <FlowMesh/GeometryElements/FlowMeshGeometryTraits.hpp>
#include <FlowMesh/GeometryElements/FlowMeshGeometryConfigBase.hpp>
#include <LinAl/LinearAlgebra.hpp>

namespace FlowMesh
{

template <typename T>
struct CuboidTraitsConfig
{
    LinAl::Vec3<T> cuboidOrigin{0, 0, 0};
    LinAl::Vec3<T> cuboidDiagonal{1, 1, 1};
    FlowMeshGeometryConfigBase baseConfig;
};

template <typename T>
struct FlowMeshGeometryTraits<FlowMeshCuboid, CuboidTraitsConfig<T>>
{
    CORE_NODISCARD static FlowMeshCuboid create(const CuboidTraitsConfig<T>& config)
    {
        return FlowMeshCuboid{
            Geometry::Cuboid<double_t>{config.cuboidOrigin, config.cuboidDiagonal},
            newFGuid(),
            config.baseConfig};
    }
};

} // namespace FlowMesh

#endif // FILAPP_FLOWMESHCUBOIDTRAITS_HPP
