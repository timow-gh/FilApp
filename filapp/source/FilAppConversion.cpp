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
filament::math::float4 vec4ToFilamentVec4(const Vec4& vec4)
{
    return {vec4[0], vec4[1], vec4[2], vec4[3]};
}
filament::math::float3 vec3ToFilamentVec3(const Vec3& vec3)
{
    return {vec3[0], vec3[1], vec3[2]};
}
Vec3 filamentVec3ToVec3(const filament::math::float3& float3Vec)
{
    return {float3Vec[0], float3Vec[1], float3Vec[2]};
}
Vec4 filamentVec4ToVec4(const filament::math::float4& float4Vec)
{
    return {float4Vec[0], float4Vec[1], float4Vec[2], float4Vec[3]};
}
filament::math::float3 transformToFilamentCS(const Vec3& vec3)
{
    return globalCSToFilCS3() * vec3ToFilamentVec3(vec3);
}
filament::math::float4 transformToFilamentCS(const Vec4& vec4)
{
    return globalCSToFilCS4() * vec4ToFilamentVec4(vec4);
}
Vec3 transformToGlobalCS(const filament::math::float3& floatVec)
{
    return filamentVec3ToVec3(filCSToGlobalCS3() * floatVec);
}
Vec4 transformToGlobalCS(const filament::math::float4& floatVec)
{
    return filamentVec4ToVec4(filCSToGlobalCS4() * floatVec);
}
} // namespace FilApp