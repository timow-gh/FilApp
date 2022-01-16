#include <Core/Utils/Assert.hpp>
#include <FilApp/FilAppConversion.hpp>
#include <FilApp/FilamentCoordinateSystem.hpp>
#include <utils/Panic.h>

namespace Graphics
{
filament::Engine::Backend toFilamentBackend(BackendMode backendMode)
{
    switch (backendMode)
    {
    case BackendMode::VULKAN: return filament::Engine::Backend::VULKAN;
    case BackendMode::OPENGL: return filament::Engine::Backend ::OPENGL;
    default: PANIC_LOG("BackendMode not implemented."); return filament::Engine::Backend::DEFAULT;
    }
}

filament::camutils::Mode toFilamentCameraMode(ViewConfig::CameraMode cameraMode)
{
    switch (cameraMode)
    {
    case ViewConfig::CameraMode::ORBIT: return filament::camutils::Mode::ORBIT;
    default: PANIC_LOG("CameraMode not implemented."); return filament::camutils::Mode::FREE_FLIGHT;
    }
}

filament::Camera::Projection toFilamentProjection(ViewConfig::CameraProjection cameraProjection)
{
    switch (cameraProjection)
    {
    case ViewConfig::CameraProjection::ORTHOGRAPHIC: return filament::Camera::Projection::ORTHO;
    case ViewConfig::CameraProjection::PERSPECTIVE:
        return filament::Camera::Projection::PERSPECTIVE;
    }
    return filament::Camera::Projection::ORTHO;
}

filament::camutils::Fov
toFilamentFovDirection(ViewConfig::FieldOfViewDirection fieldOfViewDirection, FilamentCamUtilsTag)
{
    switch (fieldOfViewDirection)
    {
    case ViewConfig::FieldOfViewDirection::HORIZONTAL: return filament::camutils::Fov::HORIZONTAL;
    case ViewConfig::FieldOfViewDirection::VERTICAL: return filament::camutils::Fov::VERTICAL;
    }
}

filament::Camera::Fov toFilamentFovDirection(ViewConfig::FieldOfViewDirection fieldOfViewDirection,
                                             FilamentCameraTag)
{
    switch (fieldOfViewDirection)
    {
    case ViewConfig::FieldOfViewDirection::HORIZONTAL: return filament::Camera::Fov::HORIZONTAL;
    case ViewConfig::FieldOfViewDirection::VERTICAL: return filament::Camera::Fov::VERTICAL;
    }
}

filament::Viewport toFilamentViewport(const Viewport& viewport)
{
    return {viewport.left, viewport.bottom, viewport.width, viewport.height};
}

filament::math::float4 vec4ToFloat4(const Vec4& vec4)
{
    return {vec4[0], vec4[1], vec4[2], vec4[3]};
}

filament::math::float3 vec3ToFloat3(const Vec3& vec3)
{
    return {vec3[0], vec3[1], vec3[2]};
}

Vec3 float3ToVec3(const filament::math::float3& float3Vec)
{
    return {float3Vec[0], float3Vec[1], float3Vec[2]};
}

Vec4 float4ToVec4(const filament::math::float4& float4Vec)
{
    return {float4Vec[0], float4Vec[1], float4Vec[2], float4Vec[3]};
}

filament::math::float3 toFilamentCS(const Vec3& vec3)
{
    return globalCSToFilCS3() * vec3ToFloat3(vec3);
}
filament::math::float4 toFilamentCS(const Vec4& vec4)
{
    return globalCSToFilCS4() * vec4ToFloat4(vec4);
}

Vec3 toGlobalCS(const filament::math::float3& floatVec)
{
    return float3ToVec3(filCSToGlobalCS3() * floatVec);
}

Vec4 toGlobalCS(const filament::math::float4& floatVec)
{
    return float4ToVec4(filCSToGlobalCS4() * floatVec);
}

SDL_Scancode toSDLScancode(KeyScancode scancode)
{
    switch (scancode)
    {
    case KeyScancode::SCANCODE_UNKNOWN: return SDL_SCANCODE_UNKNOWN;
    case KeyScancode::SCANCODE_A: return SDL_SCANCODE_A;
    case KeyScancode::SCANCODE_B: return SDL_SCANCODE_B;
    case KeyScancode::SCANCODE_C: return SDL_SCANCODE_C;
    case KeyScancode::SCANCODE_D: return SDL_SCANCODE_D;
    case KeyScancode::SCANCODE_E: return SDL_SCANCODE_E;
    case KeyScancode::SCANCODE_F: return SDL_SCANCODE_F;
    case KeyScancode::SCANCODE_G: return SDL_SCANCODE_G;
    case KeyScancode::SCANCODE_H: return SDL_SCANCODE_H;
    case KeyScancode::SCANCODE_I: return SDL_SCANCODE_I;
    case KeyScancode::SCANCODE_J: return SDL_SCANCODE_J;
    case KeyScancode::SCANCODE_K: return SDL_SCANCODE_K;
    case KeyScancode::SCANCODE_L: return SDL_SCANCODE_L;
    case KeyScancode::SCANCODE_M: return SDL_SCANCODE_M;
    case KeyScancode::SCANCODE_N: return SDL_SCANCODE_N;
    case KeyScancode::SCANCODE_O: return SDL_SCANCODE_O;
    case KeyScancode::SCANCODE_P: return SDL_SCANCODE_P;
    case KeyScancode::SCANCODE_Q: return SDL_SCANCODE_Q;
    case KeyScancode::SCANCODE_R: return SDL_SCANCODE_R;
    case KeyScancode::SCANCODE_S: return SDL_SCANCODE_S;
    case KeyScancode::SCANCODE_T: return SDL_SCANCODE_T;
    case KeyScancode::SCANCODE_U: return SDL_SCANCODE_U;
    case KeyScancode::SCANCODE_V: return SDL_SCANCODE_V;
    case KeyScancode::SCANCODE_W: return SDL_SCANCODE_W;
    case KeyScancode::SCANCODE_X: return SDL_SCANCODE_X;
    case KeyScancode::SCANCODE_Y: return SDL_SCANCODE_Y;
    case KeyScancode::SCANCODE_1: return SDL_SCANCODE_1;
    case KeyScancode::SCANCODE_2: return SDL_SCANCODE_2;
    case KeyScancode::SCANCODE_3: return SDL_SCANCODE_3;
    case KeyScancode::SCANCODE_4: return SDL_SCANCODE_4;
    case KeyScancode::SCANCODE_5: return SDL_SCANCODE_5;
    case KeyScancode::SCANCODE_6: return SDL_SCANCODE_6;
    case KeyScancode::SCANCODE_7: return SDL_SCANCODE_7;
    case KeyScancode::SCANCODE_8: return SDL_SCANCODE_8;
    case KeyScancode::SCANCODE_9: return SDL_SCANCODE_9;
    case KeyScancode::SCANCODE_0: return SDL_SCANCODE_0;
    default:
        CORE_POSTCONDITION_DEBUG_ASSERT(false, "KeyScancode not known.");
        return SDL_SCANCODE_UNKNOWN;
    }
}
KeyScancode toKeyScancode(SDL_Scancode sdlScancode)
{
    switch (sdlScancode)
    {
    case SDL_SCANCODE_UNKNOWN: return KeyScancode::SCANCODE_UNKNOWN;
    case SDL_SCANCODE_A: return KeyScancode::SCANCODE_A;
    case SDL_SCANCODE_B: return KeyScancode::SCANCODE_B;
    case SDL_SCANCODE_C: return KeyScancode::SCANCODE_C;
    case SDL_SCANCODE_D: return KeyScancode::SCANCODE_D;
    case SDL_SCANCODE_E: return KeyScancode::SCANCODE_E;
    case SDL_SCANCODE_F: return KeyScancode::SCANCODE_F;
    case SDL_SCANCODE_G: return KeyScancode::SCANCODE_G;
    case SDL_SCANCODE_H: return KeyScancode::SCANCODE_H;
    case SDL_SCANCODE_I: return KeyScancode::SCANCODE_I;
    case SDL_SCANCODE_J: return KeyScancode::SCANCODE_J;
    case SDL_SCANCODE_K: return KeyScancode::SCANCODE_K;
    case SDL_SCANCODE_L: return KeyScancode::SCANCODE_L;
    case SDL_SCANCODE_M: return KeyScancode::SCANCODE_M;
    case SDL_SCANCODE_N: return KeyScancode::SCANCODE_N;
    case SDL_SCANCODE_O: return KeyScancode::SCANCODE_O;
    case SDL_SCANCODE_P: return KeyScancode::SCANCODE_P;
    case SDL_SCANCODE_Q: return KeyScancode::SCANCODE_Q;
    case SDL_SCANCODE_R: return KeyScancode::SCANCODE_R;
    case SDL_SCANCODE_S: return KeyScancode::SCANCODE_S;
    case SDL_SCANCODE_T: return KeyScancode::SCANCODE_T;
    case SDL_SCANCODE_U: return KeyScancode::SCANCODE_U;
    case SDL_SCANCODE_V: return KeyScancode::SCANCODE_V;
    case SDL_SCANCODE_W: return KeyScancode::SCANCODE_W;
    case SDL_SCANCODE_X: return KeyScancode::SCANCODE_X;
    case SDL_SCANCODE_Y: return KeyScancode::SCANCODE_Y;
    case SDL_SCANCODE_Z: return KeyScancode::SCANCODE_Z;
    case SDL_SCANCODE_1: return KeyScancode::SCANCODE_1;
    case SDL_SCANCODE_2: return KeyScancode::SCANCODE_2;
    case SDL_SCANCODE_3: return KeyScancode::SCANCODE_3;
    case SDL_SCANCODE_4: return KeyScancode::SCANCODE_4;
    case SDL_SCANCODE_5: return KeyScancode::SCANCODE_5;
    case SDL_SCANCODE_6: return KeyScancode::SCANCODE_6;
    case SDL_SCANCODE_7: return KeyScancode::SCANCODE_7;
    case SDL_SCANCODE_8: return KeyScancode::SCANCODE_8;
    case SDL_SCANCODE_9: return KeyScancode::SCANCODE_9;
    case SDL_SCANCODE_0: return KeyScancode::SCANCODE_0;
    default:
        CORE_POSTCONDITION_DEBUG_ASSERT(false, "SDL_Scancode not known.");
        return KeyScancode::SCANCODE_UNKNOWN;
    }
}

} // namespace Graphics