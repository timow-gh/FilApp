#ifndef FILAPP_FLOWMESHCYLINDERTRAITS_HPP
#define FILAPP_FLOWMESHCYLINDERTRAITS_HPP

#include <Core/Utils/Compiler.hpp>
#include <FlowMesh/GeometryElements/FlowMeshCylinder.hpp>
#include <FlowMesh/GeometryElements/FlowMeshGeometryConfigBase.hpp>
#include <FlowMesh/GeometryElements/FlowMeshGeometryTraits.hpp>
#include <LinAl/LinearAlgebra.hpp>

namespace FlowMesh
{

template <typename T>
struct CylinderTraitsConfig
{
    T radius{1.0};
    LinAl::Vec3<T> start{0, 0, 0};
    LinAl::Vec3<T> end{0, 0, 1.0};
    FlowMeshGeometryConfigBase baseConfig;
};

template <typename T>
struct FlowMeshGeometryTraits<FlowMeshCylinder, CylinderTraitsConfig, T>
{
    CORE_NODISCARD static FlowMeshCylinder create(const CylinderTraitsConfig<T>& config)
    {
        return FlowMeshCylinder{
            Geometry::Cylinder<T>{Geometry::Segment3<T>{config.start, config.end}, config.radius},
            newFGuid(),
            config.baseConfig};
    }
};

} // namespace FlowMesh
#endif // FILAPP_FLOWMESHCYLINDERTRAITS_HPP
