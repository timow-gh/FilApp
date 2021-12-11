#include "FilAppConversion.hpp"
#include <FilApp/FilamentCoordinateSystem.hpp>
#include <utils/Panic.h>

namespace FilApp
{
filament::Engine::Backend calcFilamentBackend(BackendMode backendMode)
{
    switch (backendMode)
    {
    case BackendMode::VULKAN: return filament::Engine::Backend::VULKAN;
    case BackendMode::OPENGL: return filament::Engine::Backend ::OPENGL;
    default:
        PANIC_LOG("BackendMode not implemented.");
        return filament::Engine::Backend::DEFAULT;
    }
}
filament::camutils::Mode calcCameraMode(CameraMode cameraMode)
{
    switch (cameraMode)
    {
    case CameraMode::ORBIT: return filament::camutils::Mode::ORBIT;
    default:
        PANIC_LOG("CameraMode not implemented.");
        return filament::camutils::Mode::FREE_FLIGHT;
    }
}
filament::Viewport calcViewport(const Viewport& viewport)
{
    return {viewport.left, viewport.bottom, viewport.width, viewport.height};
}
filament::math::float4 toFilamentVec(const Vec4& vec4)
{
    return {vec4[0], vec4[1], vec4[2], vec4[3]};
}
filament::math::float3 toFilamentVec(const Vec3& vec3)
{
    return {vec3[0], vec3[1], vec3[2]};
}
filament::math::float4 transformToFilamentVec(const Vec4& vec4)
{
    return globalCSToFilCS4() *
           filament::math::float4{vec4[0], vec4[1], vec4[2], vec4[3]};
}
filament::math::float3 transformToFilamentVec(const Vec3& vec3)
{
    return globalCSToFilCS3() *
           filament::math::float3{vec3[0], vec3[1], vec3[2]};
}
} // namespace FilApp