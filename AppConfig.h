#ifndef FILAPP_APPCONFIG_H
#define FILAPP_APPCONFIG_H

#include <filament/Engine.h>

namespace FilApp
{
struct AppConfig
{
    filament::Engine::Backend backend = filament::Engine::Backend::VULKAN;
};
} // namespace FilApp

#endif // FILAPP_APPCONFIG_H
