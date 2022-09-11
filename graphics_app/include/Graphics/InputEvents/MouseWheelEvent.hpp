#ifndef GRAPHICS_MOUSEWHEELEVENT_HPP
#define GRAPHICS_MOUSEWHEELEVENT_HPP

#include <cmath>

namespace Graphics
{
struct MouseWheelEvent
{
  float_t x;
  double_t time;

  MouseWheelEvent(float_t x, double_t time)
      : x(x)
      , time(time)
  {
  }
};
} // namespace Graphics

#endif // GRAPHICS_MOUSEWHEELEVENT_HPP
