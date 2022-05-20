#ifndef MESHLER_MGUID_HPP
#define MESHLER_MGUID_HPP

#include <CrossGuid/Guid.hpp>

namespace FlowMesh
{

using FGuid = xg::Guid;

inline FGuid newFGuid()
{
    return xg::newGuid();
}

} // namespace FlowMesh

#endif // MESHLER_MGUID_HPP
