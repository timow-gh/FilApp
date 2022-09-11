#ifndef FILAPP_IOHELPER_HPP
#define FILAPP_IOHELPER_HPP

#include <iostream>
#include <math/vec3.h>

namespace FilApp
{
inline std::ostream& operator<<(std::ostream& os, const filament::math::float3& vec)
{
  return os << vec[0] << ", " << vec[1] << ", " << vec[2];
}
} // namespace FilApp
#endif // FILAPP_IOHELPER_HPP
