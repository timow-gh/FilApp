#ifndef FILAPP_FILAPPCONVERSION_H
#define FILAPP_FILAPPCONVERSION_H

#include "BackendMode.h"
#include "CameraMode.h"
#include <camutils/Bookmark.h>
#include <filament/Engine.h>

namespace FilApp
{
filament::Engine::Backend calcFilamentBackend(BackendMode backendMode);
filament::camutils::Mode calcCameraMode(CameraMode cameraMode);

} // namespace FilApp

#endif // FILAPP_FILAPPCONVERSION_H
