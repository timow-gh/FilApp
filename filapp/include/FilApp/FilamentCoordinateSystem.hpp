#ifndef FILAPP_FILAMENTCOORDINATESYSTEM_HPP
#define FILAPP_FILAMENTCOORDINATESYSTEM_HPP

#include <Core/Utils/Warnings.h>
DISABLE_ALL_WARNINGS
#include <math/mat4.h>
#include <math/vec4.h>
ENABLE_ALL_WARNINGS

namespace FilApp
{
/*
 * The global filament coordinate system his defined with an y-Axis that points
 * upwards.
 *
 * The following functions provide transformations to and from the global
 * coordinate system, with the z-Axis pointing updward.
 */

// Rotationmatrix that transforms a vector given in the filament coordinates
// into a vector given in global coordiantes
inline filament::math::mat3f filCSToGlobalCS3()
{
    return {filament::math::float3{0, 1, 0},
            filament::math::float3{0, 0, 1},
            filament::math::float3{1, 0, 0}};
}

// Rotationmatrix that transforms a vector given in global coordinates into a
// vector given in filament coordinates
inline filament::math::mat3f globalCSToFilCS3()
{
    return inverse(filCSToGlobalCS3());
}

// Rotationmatrix that transforms a vector given in the filament coordinates
// into a vector given in global coordiantes
inline filament::math::mat4f filCSToGlobalCS4()
{
    return {filament::math::float4{0, 0, 1, 0},
            filament::math::float4{1, 0, 0, 0},
            filament::math::float4{0, 1, 0, 0},
            filament::math::float4{0, 0, 0, 1}};
}

// Rotationmatrix that transforms a vector given in global coordinates into a
// vector given in filament coordinates
inline filament::math::mat4f globalCSToFilCS4()
{
    return {filament::math::float4{0, 1, 0, 0},
            filament::math::float4{0, 0, 1, 0},
            filament::math::float4{1, 0, 0, 0},
            filament::math::float4{0, 0, 0, 1}};
}
} // namespace FilApp

#endif // FILAPP_FILAMENTCOORDINATESYSTEM_HPP
