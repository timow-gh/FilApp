#ifndef FILAPP_VIEWCONFIG_HPP
#define FILAPP_VIEWCONFIG_HPP

#include <FilAppInterfaces/Vec.hpp>
#include <FilAppInterfaces/Viewport.hpp>
#include <FilAppInterfaces/WindowConfig.hpp>
#include <string>

namespace FilApp
{
struct ViewConfig
{
    enum class CameraMode
    {
        ORBIT
    };

    enum class CameraProjection
    {
        ORTHOGRAPHIC,
        PERSPECTIVE
    };

    enum class FieldOfViewDirection
    {
        HORIZONTAL,
        VERTICAL
    };

    std::string name{};
    bool useFXAA = true;
    uint8_t fxaaSampleCount{8};

    Vec4 skyBoxColor = Vec4(0.1f, 0.125f, 0.25f, 1.0f);

    Viewport viewport;
    Vec3 eye = Vec3(15.0f, 15.0f, 15.0f);
    Vec3 center = Vec3(0.0f, 0.0f, 0.0f);
    Vec3 up = Vec3(0.0f, 0.0f, 1.0f);
    float_t fieldOfViewInDegree{90.0f};
    float_t near{0.1f};
    float_t far{5000.0f};
    float_t orthogonalCameraZoom{10.0f};
    CameraMode cameraMode = CameraMode::ORBIT;
    CameraProjection cameraProjection = CameraProjection::PERSPECTIVE;
    float_t scrollMultiplierOrthographic{0.1};
    float_t scrollMultiplierPerspective{50};
    FieldOfViewDirection fovDirection = FieldOfViewDirection::HORIZONTAL;
};
} // namespace FilApp

#endif // FILAPP_VIEWCONFIG_HPP
