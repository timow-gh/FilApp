#ifndef GRAPHICS_APPCONFIG_HPP
#define GRAPHICS_APPCONFIG_HPP

namespace Graphics
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

struct AppConfig
{
  BackendMode backendMode = BackendMode::VULKAN;
  EventPollingMode eventPollingMode = EventPollingMode::WAIT_EVENTS;
};

} // namespace Graphics

#endif // GRAPHICS_APPCONFIG_HPP
