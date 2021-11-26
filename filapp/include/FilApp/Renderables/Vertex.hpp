#ifndef FILAPP_VERTEX_HPP
#define FILAPP_VERTEX_HPP

#include <cmath>
#include <cstdint>
#include <filapp_export.h>

namespace FilApp
{
struct FILAPP_EXPORT Vertex
{
    float_t position[3];
    uint32_t color;
};
} // namespace FilApp

#endif // FILAPP_VERTEX_HPP
