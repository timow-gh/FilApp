#ifndef GRAPHICS_WINDOWCONFIG_HPP
#define GRAPHICS_WINDOWCONFIG_HPP

#include <string>

namespace Graphics
{
struct WindowConfig
{
  std::string windowName = "MainWindow";
  bool isHeadless = false;
  bool isResizable = true;
  uint32_t width = 2048;
  uint32_t height = 1280;
};
} // namespace Graphics

#endif // GRAPHICS_WINDOWCONFIG_HPP
