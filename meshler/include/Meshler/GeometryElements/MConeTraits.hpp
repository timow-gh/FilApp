#ifndef MESHLER_MCONETRAITS_HPP
#define MESHLER_MCONETRAITS_HPP

#include <Core/Utils/Compiler.hpp>
#include <Meshler/GeometryElements/MCone.hpp>
#include <Meshler/GeometryElements/MGeometryConfigBase.hpp>
#include <Meshler/GeometryElements/MGeometryTraits.hpp>
#include <LinAl/LinearAlgebra.hpp>

namespace FlowMesh
{

template <typename T>
struct ConeTraitsConfig
{
    LinAl::Vec3<T> circleMidPoint{0, 0, 0};
    T radius{1.0};
    LinAl::Vec3<T> peak{0, 0, 2};
    MGeometryConfigBase baseConfig;
};

template <typename T>
struct MGeometryTraits<MCone, ConeTraitsConfig, T>
{
    CORE_NODISCARD static MCone create(const ConeTraitsConfig<T>& config)
    {
        return MCone{Geometry::Cone<T>{config.circleMidPoint, config.peak, config.radius},
                            newFGuid(),
                            config.baseConfig};
    }
};

} // namespace FlowMesh

#endif // MESHLER_MCONETRAITS_HPP
