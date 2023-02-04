#ifndef FILAPP_FILAPPCONVERSION_HPP
#define FILAPP_FILAPPCONVERSION_HPP

#include <Core/Utils/Warnings.hpp>
#include <Graphics/AppConfig.hpp>
#include <Graphics/InputEvents/KeyScancode.hpp>
#include <Graphics/Vec.hpp>
#include <Graphics/ViewConfig.hpp>
#include <Graphics/Viewport.hpp>
#include <Graphics/WindowConfig.hpp>
DISABLE_ALL_WARNINGS
#include <SDL_scancode.h>
#include <camutils/Bookmark.h>
#include <camutils/Manipulator.h>
#include <filament/Camera.h>
#include <filament/Engine.h>
#include <filament/Viewport.h>
#include <math/vec3.h>
#include <math/vec4.h>
#include <utils/Entity.h>
ENABLE_ALL_WARNINGS

namespace FilApp
{
/*
 * Convenience functions to convert from filament data types to the interface
 * data types.
 */

filament::backend::Backend toFilamentBackend(Graphics::BackendMode backendMode);
filament::camutils::Mode toFilamentCameraMode(Graphics::ViewConfig::CameraMode cameraMode);
filament::Camera::Projection toFilamentProjection(Graphics::ViewConfig::CameraProjection cameraProjection);

/*
 * Fov is declared in filament::Camera and filament::camutils.
 * Use tag dispatch to differentiate the two conversion functions.
 */
// clang-format off
struct FilamentCameraTag{};
struct FilamentCamUtilsTag{};
// clang-format on

filament::camutils::Fov toFilamentFovDirection(Graphics::ViewConfig::FieldOfViewDirection fieldOfViewDirection, FilamentCamUtilsTag);
filament::Camera::Fov toFilamentFovDirection(Graphics::ViewConfig::FieldOfViewDirection fieldOfViewDirection, FilamentCameraTag);

filament::Viewport toFilamentViewport(const Graphics::Viewport& viewport);

filament::math::float4 vec4ToFloat4(const Graphics::Vec4& vec4);
filament::math::float3 vec3ToFloat3(const Graphics::Vec3& vec3);
Graphics::Vec3 float3ToVec3(const filament::math::float3& float3Vec);
Graphics::Vec4 float4ToVec4(const filament::math::float4& float4Vec);

filament::math::float3 toFilamentCS(const Graphics::Vec3& vec3);
filament::math::float4 toFilamentCS(const Graphics::Vec4& vec4);
Graphics::Vec3 toGlobalCS(const filament::math::float3& floatVec);
Graphics::Vec4 toGlobalCS(const filament::math::float4& floatVec);

SDL_Scancode toSDLScancode(Graphics::KeyScancode keyScancode);
Graphics::KeyScancode toKeyScancode(SDL_Scancode sdlScancode);

utils::Entity createGlobalTrafoComponent(filament::Engine& engine);
} // namespace FilApp

#endif // FILAPP_FILAPPCONVERSION_HPP
