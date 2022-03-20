#ifndef FILAPP_FLOWMESHCYLINDERTRAITS_HPP
#define FILAPP_FLOWMESHCYLINDERTRAITS_HPP

#include <FlowMesh/GeometryElements/FlowMeshCylinder.hpp>
#include <FlowMesh/GeometryElements/FlowMeshGeometryTraits.hpp>

namespace FlowMesh
{

template <typename T>
struct CylinderTraitsConfig
{
    T radius{0.5};
    LinAl::Vec3<T> start{0, 0, 0};
    LinAl::Vec3<T> end{0, 0, 1.0};
};

template <typename T>
struct FlowMeshGeometryTraits<FlowMeshCylinder, CylinderTraitsConfig<T>>
{
    CORE_NODISCARD static FlowMeshCylinder create(const CylinderTraitsConfig<T>& config)
    {
        return FlowMeshCylinder{
            Geometry::Cylinder<T>{Geometry::Segment3<T>{config.start, config.end}, config.radius},
            newFGuid()};
    }
};

} // namespace FlowMesh
#endif // FILAPP_FLOWMESHCYLINDERTRAITS_HPP
