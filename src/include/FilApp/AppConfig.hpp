#ifndef FILAPP_APPCONFIG_HPP
#define FILAPP_APPCONFIG_HPP

#include <filament/Engine.h>
#include <filapp_export.h>

namespace FilApp
{
struct FILAPP_EXPORT AppConfig
{
    filament::Engine::Backend backend = filament::Engine::Backend::DEFAULT;
};
} // namespace FilApp

#endif // FILAPP_APPCONFIG_HPP
