#ifndef GRAPHICS_MOUSEMOVEEVENT_HPP
#define GRAPHICS_MOUSEMOVEEVENT_HPP

#include <cmath>

namespace Graphics
{

struct MouseMoveEvent
{
  std::uint32_t timestamp; // in milliseconds
  std::uint32_t windowId;
  std::uint32_t x;
  std::uint32_t y;
  double_t deltaT;

  MouseMoveEvent(uint32_t timestamp, uint32_t windowId, uint32_t x, uint32_t y, double_t deltaT)
      : timestamp(timestamp)
      , windowId(windowId)
      , x(x)
      , y(y)
      , deltaT(deltaT)
  {
  }
};

} // namespace Graphics

#endif // GRAPHICS_MOUSEMOVEEVENT_HPP
