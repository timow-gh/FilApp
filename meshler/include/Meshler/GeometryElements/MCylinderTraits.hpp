#ifndef MESHLER_MCYLINDERTRAITS_HPP
#define MESHLER_MCYLINDERTRAITS_HPP

#include <Core/Utils/Compiler.hpp>
#include <LinAl/LinearAlgebra.hpp>
#include <Meshler/GeometryElements/MCylinder.hpp>
#include <Meshler/GeometryElements/MGeometryConfigBase.hpp>
#include <Meshler/GeometryElements/MGeometryTraits.hpp>

namespace Meshler
{

template <typename T>
struct CylinderTraitsConfig
{
    T radius{1.0};
    LinAl::Vec3<T> start{0, 0, 0};
    LinAl::Vec3<T> end{0, 0, 1.0};
    MGeometryConfigBase baseConfig;
};

template <typename T>
struct MGeometryTraits<MCylinder, CylinderTraitsConfig, T>
{
    CORE_NODISCARD static MCylinder create(const CylinderTraitsConfig<T>& config)
    {
        return MCylinder{
            Geometry::Cylinder<T>{Geometry::Segment3<T>{config.start, config.end}, config.radius},
            newFGuid(),
            config.baseConfig};
    }
};

} // namespace Meshler
#endif // MESHLER_MCYLINDERTRAITS_HPP
