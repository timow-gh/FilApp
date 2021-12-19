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
/*
 * Convenience functions to convert from filament data types to the interface
 * data types.
 */

filament::Engine::Backend calcFilamentBackend(BackendMode backendMode);
filament::camutils::Mode calcCameraMode(CameraMode cameraMode);
filament::Viewport calcViewport(const Viewport& viewport);

filament::math::float4 vec4ToFloat4(const Vec4& vec4);
filament::math::float3 vec3ToFloat3(const Vec3& vec3);
Vec3 float3ToVec3(const filament::math::float3& float3Vec);
Vec4 float4ToVec4(const filament::math::float4& float4Vec);

filament::math::float3 toFilamentCS(const Vec3& vec3);
filament::math::float4 toFilamentCS(const Vec4& vec4);
Vec3 toGlobalCS(const filament::math::float3& floatVec);
Vec4 toGlobalCS(const filament::math::float4& floatVec);

} // namespace FilApp

#endif // FILAPP_FILAPPCONVERSION_HPP
