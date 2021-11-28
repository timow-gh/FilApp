#ifndef FILAPP_FILAPPCONVERSION_HPP
#define FILAPP_FILAPPCONVERSION_HPP

#include <FilAppInterfaces/AppConfig.hpp>
#include <FilAppInterfaces/Vec.hpp>
#include <FilAppInterfaces/Viewport.hpp>
#include <FilAppInterfaces/WindowConfig.hpp>
#include <camutils/Bookmark.h>
#include <filament/Engine.h>
#include <filament/Viewport.h>
#include <math/vec3.h>
#include <math/vec4.h>

namespace FilApp
{
filament::Engine::Backend calcFilamentBackend(BackendMode backendMode);
filament::camutils::Mode calcCameraMode(CameraMode cameraMode);
filament::Viewport calcViewport(const Viewport& viewport);

filament::math::float4 toFilamentVec(const Vec4& vec4);
filament::math::float3 toFilamentVec(const Vec3& vec3);
filament::math::float4 transformToFilamentVec(const Vec4& vec4);
filament::math::float3 transformToFilamentVec(const Vec3& vec3);
} // namespace FilApp

#endif // FILAPP_FILAPPCONVERSION_HPP
