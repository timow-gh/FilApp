#ifndef FILAPP_TYPEID_HPP
#define FILAPP_TYPEID_HPP

#include <CrossGuid/Guid.hpp>

namespace FlowMesh
{

using TypeId = xg::Guid;

inline TypeId newTypeId()
{
    return xg::newGuid();
}

} // namespace FlowMesh

#endif // FILAPP_TYPEID_HPP
