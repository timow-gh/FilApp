#ifndef FILAPP_FILAPPCONVERSION_HPP
#define FILAPP_FILAPPCONVERSION_HPP

#include <Graphics/AppConfig.hpp>
#include <Graphics/InputEvents/KeyScancode.hpp>
#include <Graphics/Vec.hpp>
#include <Graphics/ViewConfig.hpp>
#include <Graphics/Viewport.hpp>
#include <Graphics/WindowConfig.hpp>
#include <SDL_scancode.h>
#include <camutils/Bookmark.h>
#include <camutils/Manipulator.h>
#include <filament/Camera.h>
#include <filament/Engine.h>
#include <filament/Viewport.h>
#include <math/vec3.h>
#include <math/vec4.h>

namespace Graphics
{
/*
 * Convenience functions to convert from filament data types to the interface
 * data types.
 */

filament::Engine::Backend toFilamentBackend(BackendMode backendMode);
filament::camutils::Mode toFilamentCameraMode(ViewConfig::CameraMode cameraMode);
filament::Camera::Projection toFilamentProjection(ViewConfig::CameraProjection cameraProjection);

/*
 * Fov is declared in filament::Camera and filament::camutils.
 * Use tag dispatch to differentiate the two conversion functions.
 */
// clang-format off
struct FilamentCameraTag{};
struct FilamentCamUtilsTag{};
// clang-format on

filament::camutils::Fov
toFilamentFovDirection(ViewConfig::FieldOfViewDirection fieldOfViewDirection, FilamentCamUtilsTag);
filament::Camera::Fov toFilamentFovDirection(ViewConfig::FieldOfViewDirection fieldOfViewDirection,
                                             FilamentCameraTag);

filament::Viewport toFilamentViewport(const Viewport& viewport);

filament::math::float4 vec4ToFloat4(const Vec4& vec4);
filament::math::float3 vec3ToFloat3(const Vec3& vec3);
Vec3 float3ToVec3(const filament::math::float3& float3Vec);
Vec4 float4ToVec4(const filament::math::float4& float4Vec);

filament::math::float3 toFilamentCS(const Vec3& vec3);
filament::math::float4 toFilamentCS(const Vec4& vec4);
Vec3 toGlobalCS(const filament::math::float3& floatVec);
Vec4 toGlobalCS(const filament::math::float4& floatVec);

SDL_Scancode toSDLScancode(KeyScancode keyScancode);
KeyScancode toKeyScancode(SDL_Scancode sdlScancode);

} // namespace Graphics

#endif // FILAPP_FILAPPCONVERSION_HPP
