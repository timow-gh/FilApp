#ifndef FILAPP_FLOWMESHGEOMETRYTRAITS_HPP
#define FILAPP_FLOWMESHGEOMETRYTRAITS_HPP

#include <FlowMesh/GeometryElements/FlowMeshGeometryConfigBase.hpp>

namespace FlowMesh
{

template <typename TFlowMeshGeometry, template<typename> typename TGeomConfig, typename T>
struct FlowMeshGeometryTraits
{
    CORE_NODISCARD static TFlowMeshGeometry create(const TGeomConfig<T>& config)
    {
        static_assert(sizeof(0) && "create not implemented.");
    }
};

} // namespace FlowMesh

#endif // FILAPP_FLOWMESHGEOMETRYTRAITS_HPP
