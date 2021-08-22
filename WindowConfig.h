#ifndef FILAPP_WINDOWCONFIG_H
#define FILAPP_WINDOWCONFIG_H

#include <camutils/Manipulator.h>
#include <filament/Engine.h>
#include <string>

namespace FilApp
{
struct WindowConfig
{
    std::string title = "MainWindow";
    bool isHeadless = false;
    bool isResizable = true;
    std::int32_t width = 1024;
    std::int32_t height = 640;
    filament::camutils::Mode cameraMode = filament::camutils::Mode::FREE_FLIGHT;
};
} // namespace FilApp

#endif // FILAPP_WINDOWCONFIG_H
