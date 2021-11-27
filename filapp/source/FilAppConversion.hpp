#ifndef FILAPP_FILAPPCONVERSION_HPP
#define FILAPP_FILAPPCONVERSION_HPP

#include "FilAppInterfaces/AppConfig.hpp"
#include "FilAppInterfaces/WindowConfig.hpp"
#include <camutils/Bookmark.h>
#include <filament/Engine.h>

namespace FilApp
{
filament::Engine::Backend calcFilamentBackend(BackendMode backendMode);
filament::camutils::Mode calcCameraMode(CameraMode cameraMode);
} // namespace FilApp

#endif // FILAPP_FILAPPCONVERSION_HPP
