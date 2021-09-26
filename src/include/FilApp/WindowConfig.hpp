#ifndef FILAPP_WINDOWCONFIG_HPP
#define FILAPP_WINDOWCONFIG_HPP

#include <filapp_export.h>
#include <string>

namespace FilApp
{
enum class CameraMode
{
    ORBIT
};

struct FILAPP_EXPORT WindowConfig
{
    std::string title = "MainWindow";
    bool isHeadless = false;
    bool isResizable = true;
    uint32_t width = 1024;
    uint32_t height = 640;
    CameraMode cameraMode = CameraMode::ORBIT;
};
} // namespace FilApp

#endif // FILAPP_WINDOWCONFIG_HPP
