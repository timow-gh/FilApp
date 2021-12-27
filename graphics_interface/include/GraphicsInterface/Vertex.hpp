#ifndef FILAPP_VERTEX_HPP
#define FILAPP_VERTEX_HPP

#include <cmath>
#include <cstdint>

namespace FilApp
{
struct Vertex
{
    float_t position[3];
    uint32_t color;
};
} // namespace FilApp

#endif // FILAPP_VERTEX_HPP
