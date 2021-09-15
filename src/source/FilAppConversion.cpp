#include "FilApp/FilAppConversion.hpp"
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
} // namespace FilApp