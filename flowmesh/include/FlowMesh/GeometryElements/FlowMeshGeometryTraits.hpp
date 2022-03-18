#ifndef FILAPP_FLOWMESHGEOMETRYTRAITS_HPP
#define FILAPP_FLOWMESHGEOMETRYTRAITS_HPP

#include <Core/Utils/Compiler.hpp>
#include <FlowMesh/GeometryElements/FlowMeshSphere.hpp>

namespace FlowMesh
{

template <typename TFlowMeshGeometry, typename TGeomConfig>
struct FlowMeshGeometryTraits
{
    static TFlowMeshGeometry create()
    {
        static_assert(sizeof(TFlowMeshGeometry) < 0,
                      "TFlowMeshGeometry is not specialized for this type");
    }
};

} // namespace FlowMesh

#endif // FILAPP_FLOWMESHGEOMETRYTRAITS_HPP
