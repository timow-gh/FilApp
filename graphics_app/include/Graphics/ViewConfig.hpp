#ifndef GRAPHICS_VIEWCONFIG_HPP
#define GRAPHICS_VIEWCONFIG_HPP

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

    std::string name{"DefaultViewName"};
    bool useFXAA = true;

    RGBAColor<float_t> skyBoxColor = RGBAColor<float_t>(0.19f, 0.19f, 0.19f, 0.55f);

    Viewport viewport;
    Vec3 eye = Vec3(10.0f, 10.0f, 7.0f);
    Vec3 center = Vec3(0.0f, 0.0f, 0.0f);
    Vec3 up = Vec3(0.0f, 0.0f, 1.0f);
    double_t fieldOfViewInDegree{60.0};
    double_t near{5.0};
    double_t far{1000.0};
    double_t orthogonalCameraZoom{10.0};
    CameraMode cameraMode = CameraMode::ORBIT;
    CameraProjection cameraProjection = CameraProjection::PERSPECTIVE;
    float_t scrollMultiplierOrthographic{0.1f};
    float_t scrollMultiplierPerspective{100.0f};
    FieldOfViewDirection fovDirection = FieldOfViewDirection::HORIZONTAL;
};

} // namespace Graphics

#endif // GRAPHICS_VIEWCONFIG_HPP
