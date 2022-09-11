#ifndef GRAPHICS_VERTEX_HPP
#define GRAPHICS_VERTEX_HPP

#include <cmath>
#include <cstdint>

namespace Graphics
{
struct Vertex
{
  float_t position[3];
  std::uint32_t color;
};
} // namespace Graphics

#endif // GRAPHICS_VERTEX_HPP
