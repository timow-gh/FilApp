#ifndef FILAPP_GLOBALCS_HPP
#define FILAPP_GLOBALCS_HPP

#include <math/mat4.h>
#include <math/vec4.h>

namespace FilApp
{
inline filament::math::mat4f filamentCSToGlobalCS()
{
    constexpr float_t rotAngle = -filament::math::F_PI_2; //-1.57079632679
    //    return rotY * rotX;
    return filament::math::mat4f::rotation(rotAngle,
                                           filament::math::float4{0, 1, 0, 1}) *
           filament::math::mat4f::rotation(rotAngle,
                                           filament::math::float4{1, 0, 0, 1});
}

inline filament::math::mat4f globalCSToFilamentCS()
{
    constexpr float_t rotAngle = filament::math::F_PI_2; //-1.57079632679
    //    return rotX * rotY;
    return filament::math::mat4f::rotation(rotAngle,
                                           filament::math::float4{1, 0, 0, 1}) *
           filament::math::mat4f::rotation(rotAngle,
                                           filament::math::float4{0, 1, 0, 1});
}
} // namespace FilApp

#endif // FILAPP_GLOBALCS_HPP
