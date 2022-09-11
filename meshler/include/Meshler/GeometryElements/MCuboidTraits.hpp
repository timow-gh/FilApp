#ifndef MESHLER_MCUBOIDTRAITS_HPP
#define MESHLER_MCUBOIDTRAITS_HPP

#include <Core/Utils/Compiler.hpp>
#include <LinAl/LinearAlgebra.hpp>
#include <Meshler/GeometryElements/MCuboid.hpp>
#include <Meshler/GeometryElements/MGeometryConfigBase.hpp>
#include <Meshler/GeometryElements/MGeometryTraits.hpp>

namespace Meshler
{

template <typename T>
struct CuboidTraitsConfig
{
  LinAl::Vec3<T> cuboidOrigin{0, 0, 0};
  LinAl::Vec3<T> cuboidDiagonal{1, 1, 1};
  MGeometryConfigBase baseConfig;
};

template <typename T>
struct MGeometryTraits<MCuboid, CuboidTraitsConfig, T>
{
  CORE_NODISCARD static MCuboid create(const CuboidTraitsConfig<T>& config)
  {
    return MCuboid{Geometry::Cuboid<double_t>{config.cuboidOrigin, config.cuboidDiagonal}, newFGuid(), config.baseConfig};
  }
};

} // namespace Meshler

#endif // MESHLER_MCUBOIDTRAITS_HPP
