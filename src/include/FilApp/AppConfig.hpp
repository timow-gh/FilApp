#ifndef FILAPP_APPCONFIG_HPP
#define FILAPP_APPCONFIG_HPP

#include <filapp_export.h>

namespace FilApp
{
enum class BackendMode
{
    VULKAN,
    OPENGL
};

struct FILAPP_EXPORT AppConfig
{
    BackendMode backendMode = BackendMode::VULKAN;
};
} // namespace FilApp

#endif // FILAPP_APPCONFIG_HPP
