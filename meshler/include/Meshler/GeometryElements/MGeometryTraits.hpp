#ifndef MESHLER_MGEOMETRYTRAITS_HPP
#define MESHLER_MGEOMETRYTRAITS_HPP

#include <Meshler/GeometryElements/MGeometryConfigBase.hpp>

namespace FlowMesh
{

template <typename TFlowMeshGeometry, template<typename> typename TGeomConfig, typename T>
struct MGeometryTraits
{
    CORE_NODISCARD static TFlowMeshGeometry create(const TGeomConfig<T>& config)
    {
        static_assert(sizeof(0) && "create not implemented.");
    }
};

} // namespace FlowMesh

#endif // MESHLER_MGEOMETRYTRAITS_HPP
