#ifndef FILAPP_WINDOWCONFIG_HPP
#define FILAPP_WINDOWCONFIG_HPP

#include <camutils/Manipulator.h>
#include <filament/Engine.h>
#include <filapp_export.h>
#include <string>

namespace FilApp
{
struct FILAPP_EXPORT WindowConfig
{
    std::string title = "MainWindow";
    bool isHeadless = false;
    bool isResizable = true;
    std::int32_t width = 1024;
    std::int32_t height = 640;
    filament::camutils::Mode cameraMode = filament::camutils::Mode::ORBIT;
};
} // namespace FilApp

#endif // FILAPP_WINDOWCONFIG_HPP
