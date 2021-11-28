#ifndef FILAPP_FILAMENTCOORDINATESYSTEM_HPP
#define FILAPP_FILAMENTCOORDINATESYSTEM_HPP

#include <math/mat4.h>
#include <math/vec4.h>

namespace FilApp
{
// Rotationmatrix that transforms a vector given in the filament coordinates
// into a vector given in global coordiantes
inline filament::math::mat3f filCSToGlobalCS3()
{
    constexpr float_t rotAngle = -filament::math::F_PI_2; //-1.57079632679
    //    return rotY * rotX;
    return filament::math::mat3f::rotation(rotAngle,
                                           filament::math::float3{0, 1, 0}) *
           filament::math::mat3f::rotation(rotAngle,
                                           filament::math::float3{1, 0, 0});
}

// Rotationmatrix that transforms a vector given in global coordinates into a
// vector given in filament coordinates
inline filament::math::mat3f globalCSToFilCS3()
{
    constexpr float_t rotAngle =
        filament::math::F_PI_2; // 1.57079632679
                                //    return rotZ * rotY;
    return filament::math::mat3f::rotation(rotAngle,
                                           filament::math::float3{0, 0, 1}) *
           filament::math::mat3f::rotation(rotAngle,
                                           filament::math::float3{0, 1, 0});
}

// Rotationmatrix that transforms a vector given in the filament coordinates
// into a vector given in global coordiantes
inline filament::math::mat4f filCSToGlobalCS4()
{
    constexpr float_t rotAngle = -filament::math::F_PI_2; //-1.57079632679
    //    return rotY * rotX;
    return filament::math::mat4f::rotation(rotAngle,
                                           filament::math::float4{0, 1, 0, 1}) *
           filament::math::mat4f::rotation(rotAngle,
                                           filament::math::float4{1, 0, 0, 1});
}

// Rotationmatrix that transforms a vector given in global coordinates into a
// vector given in filament coordinates
inline filament::math::mat4f globalCSToFilCS4()
{
    constexpr float_t rotAngle = filament::math::F_PI_2; // 1.57079632679
    //    return rotZ * rotY;
    return filament::math::mat4f::rotation(rotAngle,
                                           filament::math::float4{0, 0, 1, 1}) *
           filament::math::mat4f::rotation(rotAngle,
                                           filament::math::float4{0, 1, 0, 1});
}
} // namespace FilApp

#endif // FILAPP_FILAMENTCOORDINATESYSTEM_HPP
