#ifndef FILAPP_FLOWMESHSPHERETRAITS_HPP
#define FILAPP_FLOWMESHSPHERETRAITS_HPP

#include <FlowMesh/GeometryElements/FlowMeshGeometryTraits.hpp>
#include <FlowMesh/GeometryElements/FlowMeshSphere.hpp>

namespace FlowMesh
{

template <typename T>
struct SphereTraitsConfig
{
    T radius{1.0};
    LinAl::Vec3<T> origin{LinAl::Vec3<T>{0.0, 0.0, 0.0}};
};

template <typename T>
struct FlowMeshGeometryTraits<FlowMeshSphere, SphereTraitsConfig<T>>
{
    CORE_NODISCARD static FlowMeshSphere create(const SphereTraitsConfig<T>& config)
    {
        auto sphere = Geometry::Sphere<double_t>{config.origin, config.radius};
        return FlowMeshSphere{sphere, newFGuid()};
    }
};

} // namespace FlowMesh

#endif // FILAPP_FLOWMESHSPHERETRAITS_HPP
