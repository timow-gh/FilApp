#ifndef FILAPP_FLOWMESHSPHERETRAITS_HPP
#define FILAPP_FLOWMESHSPHERETRAITS_HPP

#include <Core/Utils/Compiler.hpp>
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
        return FlowMeshSphere{Geometry::Sphere<T>{config.origin, config.radius}, newFGuid()};
    }
};

} // namespace FlowMesh

#endif // FILAPP_FLOWMESHSPHERETRAITS_HPP
