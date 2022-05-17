#ifndef FILAPP_VIEWCONFIG_HPP
#define FILAPP_VIEWCONFIG_HPP

#include <Graphics/RGBAColor.hpp>
#include <Graphics/Vec.hpp>
#include <Graphics/Viewport.hpp>
#include <Graphics/WindowConfig.hpp>
#include <string>

namespace Graphics
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
    uint8_t fxaaSampleCount{4};

    RGBAColor<float_t> skyBoxColor = RGBAColor<float_t>(0.19, 0.19, 0.19, 0.55);

    Viewport viewport;
    Vec3 eye = Vec3(10.0f, 10.0f, 7.0f);
    Vec3 center = Vec3(0.0f, 0.0f, 0.0f);
    Vec3 up = Vec3(0.0f, 0.0f, 1.0f);
    float_t fieldOfViewInDegree{60.0f};
    float_t near{0.1f};
    float_t far{5000.0f};
    float_t orthogonalCameraZoom{10.0f};
    CameraMode cameraMode = CameraMode::ORBIT;
    CameraProjection cameraProjection = CameraProjection::PERSPECTIVE;
    float_t scrollMultiplierOrthographic{0.1};
    float_t scrollMultiplierPerspective{50};
    FieldOfViewDirection fovDirection = FieldOfViewDirection::HORIZONTAL;
};
} // namespace Graphics

#endif // FILAPP_VIEWCONFIG_HPP
