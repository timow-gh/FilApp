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

enum class EventPollingMode
{
    POLL_EVENTS,
    WAIT_EVENTS
};

struct FILAPP_EXPORT AppConfig
{
    BackendMode backendMode = BackendMode::VULKAN;
    EventPollingMode eventPollingMode = EventPollingMode::WAIT_EVENTS;
};
} // namespace FilApp

#endif // FILAPP_APPCONFIG_HPP
