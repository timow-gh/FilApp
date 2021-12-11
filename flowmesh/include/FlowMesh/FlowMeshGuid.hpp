#ifndef FILAPP_FLOWMESHGUID_HPP
#define FILAPP_FLOWMESHGUID_HPP

#include <CrossGuid/Guid.hpp>

namespace FlowMesh
{

using FGuid = xg::Guid;

inline FGuid newFGuid()
{
    return xg::newGuid();
}

} // namespace FlowMesh

#endif // FILAPP_FLOWMESHGUID_HPP
