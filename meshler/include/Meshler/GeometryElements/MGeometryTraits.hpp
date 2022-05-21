#ifndef MESHLER_MGEOMETRYTRAITS_HPP
#define MESHLER_MGEOMETRYTRAITS_HPP

#include <Meshler/GeometryElements/MGeometryConfigBase.hpp>

namespace Meshler
{

template <typename TMeshlerGeometry, template <typename> typename TGeomConfig, typename T>
struct MGeometryTraits
{
    CORE_NODISCARD static TMeshlerGeometry create(const TGeomConfig<T>& config)
    {
        static_assert(sizeof(0) && "create not implemented.");
    }
};

} // namespace Meshler

#endif // MESHLER_MGEOMETRYTRAITS_HPP
