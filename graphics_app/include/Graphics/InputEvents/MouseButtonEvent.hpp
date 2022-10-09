#ifndef GRAPHICS_MOUSEBUTTONEVENT_HPP
#define GRAPHICS_MOUSEBUTTONEVENT_HPP

#include <cmath>
#include <cstdint>

namespace Graphics
{

struct MouseButtonEvent
{
  enum class Type
  {
    PUSH,
    REPEAT,
    RELEASE
  };

  Type type;
  // buttonIndex is 1 for left, 3 for right mouse button
  std::uint32_t buttonIndex;
  std::uint32_t timestamp; // in milliseconds
  std::uint32_t windowId;
  std::uint32_t clicks; // 1: single-click, 2: double-click
  std::uint32_t x;
  std::uint32_t y;
  double_t deltaT;
};

} // namespace Graphics

#endif // GRAPHICS_MOUSEBUTTONEVENT_HPP
