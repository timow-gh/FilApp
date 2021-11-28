#ifndef FILAPP_VIEWCONFIG_HPP
#define FILAPP_VIEWCONFIG_HPP

#include <FilAppInterfaces/Vec.hpp>
#include <FilAppInterfaces/ViewPort.hpp>
#include <FilAppInterfaces/WindowConfig.hpp>
#include <string>

namespace FilApp
{
struct ViewConfig
{
    std::string name{};
    bool useFXAA = true;
    uint8_t fxaaSampleCount{8};

    Vec4 skyBoxColor = Vec4(0.1f, 0.125f, 0.25f, 1.0f);

    Vec3 eye = Vec3(15.0f, 15.0f, 15.0f);
    Vec3 center = Vec3(0.0f, 0.0f, 0.0f);
    Vec3 up = Vec3(0.0f, 0.0f, 1.0f);

    CameraMode cameraMode = CameraMode::ORBIT;
    Viewport viewport;
};
} // namespace FilApp

#endif // FILAPP_VIEWCONFIG_HPP
