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
    uint32_t width = 1024;
    uint32_t height = 640;
};
} // namespace Graphics

#endif // GRAPHICS_WINDOWCONFIG_HPP
