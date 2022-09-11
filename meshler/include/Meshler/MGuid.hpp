#ifndef MESHLER_MGUID_HPP
#define MESHLER_MGUID_HPP

#include <CrossGuid/Guid.hpp>

namespace Meshler
{

using FGuid = xg::Guid;

inline FGuid newFGuid()
{
  return xg::newGuid();
}

} // namespace Meshler

#endif // MESHLER_MGUID_HPP
