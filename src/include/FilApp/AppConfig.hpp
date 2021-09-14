#ifndef FILAPP_APPCONFIG_HPP
#define FILAPP_APPCONFIG_HPP

#include "FilApp/BackendMode.h"
#include <filapp_export.h>

namespace FilApp
{
struct FILAPP_EXPORT AppConfig
{
    BackendMode backendMode = BackendMode::VULKAN;
};
} // namespace FilApp

#endif // FILAPP_APPCONFIG_HPP
