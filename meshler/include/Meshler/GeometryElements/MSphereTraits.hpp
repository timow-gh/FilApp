#ifndef MESHLER_MSPHERETRAITS_HPP
#define MESHLER_MSPHERETRAITS_HPP

#include <Core/Utils/Compiler.hpp>
#include <Meshler/GeometryElements/MGeometryConfigBase.hpp>
#include <Meshler/GeometryElements/MGeometryTraits.hpp>
#include <Meshler/GeometryElements/MSphere.hpp>
#include <LinAl/LinearAlgebra.hpp>

namespace Meshler
{

template <typename T>
struct SphereTraitsConfig
{
    T radius{1.0};
    LinAl::Vec3<T> origin{LinAl::Vec3<T>{0.0, 0.0, 0.0}};
    MGeometryConfigBase baseConfig;
};

template <typename T>
struct MGeometryTraits<MSphere, SphereTraitsConfig, T>
{
    CORE_NODISCARD static MSphere create(const SphereTraitsConfig<T>& config)
    {
        return MSphere{Geometry::Sphere<T>{config.origin, config.radius},
                              newFGuid(),
                              config.baseConfig};
    }
};

} // namespace Meshler

#endif // MESHLER_MSPHERETRAITS_HPP
