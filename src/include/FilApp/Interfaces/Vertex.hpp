#ifndef FILAPP_VERTEX_HPP
#define FILAPP_VERTEX_HPP

#include <filapp_export.h>
#include <math/vec3.h>

namespace FilApp
{
struct FILAPP_EXPORT Vertex
{
    filament::math::float3 position;
    uint32_t color;
};
} // namespace FilApp

#endif // FILAPP_VERTEX_HPP
